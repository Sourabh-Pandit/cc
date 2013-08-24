/*
 * Copyright (C) 2013 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include <fkit/Memory.h>
#include <fkit/Format.h>
#include <fkit/RefGuard.h>
#include <fkit/System.h>
#include <fkit/TimeoutLimiter.h>
#include "exceptions.h"
#include "ErrorLog.h"
#include "AccessLog.h"
#include "NodeConfig.h"
#include "ServiceDefinition.h"
#include "ServiceDelegate.h"
#include "Response.h"
#include "ServiceWorker.h"

namespace fnode
{

Ref<ServiceWorker> ServiceWorker::create(ServiceInstance *serviceInstance, ClosedConnections *closedConnections)
{
	Ref<ServiceWorker> worker = new ServiceWorker(serviceInstance, closedConnections);
	worker->serviceDelegate_ = serviceInstance->createDelegate(worker);
	return worker;
}

ServiceWorker::ServiceWorker(ServiceInstance *serviceInstance, ClosedConnections *closedConnections)
	: serviceInstance_(serviceInstance),
	  pendingConnections_(PendingConnections::create()),
	  closedConnections_(closedConnections)
{}

ServiceWorker::~ServiceWorker()
{
	pendingConnections_->push(Ref<ClientConnection>());
	wait();
}

void ServiceWorker::logDelivery(ClientConnection *client, int statusCode)
{
	Stream *stream = accessLog()->noticeStream();
	if (400 <= statusCode && statusCode <= 499) stream = accessLog()->warningStream();
	else if (500 <= statusCode) stream = accessLog()->errorStream();

	Request *request = client->request_;
	String requestLine = request ? request->requestLine() : "INVALID";
	double requestTime = request ? request->requestTime() : System::now();
	String userAgent =   request ? request->value("User-Agent") : "";

	Format(stream)
		<< client->address()->networkAddress() << " "
		<< Date::localTime(requestTime)->toString() << " "
		<< "\"" << requestLine << "\" "
		<< statusCode << " "
		<< "\"" << userAgent << "\" "
		<< nl;
}

void ServiceWorker::run()
{
	errorLog()->open(serviceInstance_->errorLogConfig());
	accessLog()->open(serviceInstance_->accessLogConfig());

	while (pendingConnections_->pop(&client_)) {
		try {
			if (serviceInstance_->connectionTimeout() > 0) {
				client_->stream_ = TimeoutLimiter::open(client_->stream_, System::now() + serviceInstance_->connectionTimeout());
				debug() << "Established connection timeout of " << serviceInstance_->connectionTimeout() << "s" << nl;
			}
			while (client_) {
				if (!client_->request_) {
					debug() << "Reading request header..." << nl;
					client_->request_ = Request::parse(client_);
					if ( (client_->request_->method() != "GET") &&
					     (client_->request_->method() != "HEAD") ) throw NotImplemented();
				}
				{
					RefGuard<Response> guard(&response_);
					response_ = Response::create(client_);
					serviceDelegate_->process(client_->request_);
					response_->end();
					if (response_->delivered())
						logDelivery(client_, response_->statusCode());
				}
				if (client_) {
					if (client_->request_->value("Connection") == "close")
						close();
					else
						client_->request_ = 0;
				}
			}
		}
		catch (ProtocolException &ex) {
			Format("HTTP/1.1 %% %%\r\n\r\n", client_->stream_) << ex.statusCode() << " " << ex.message();
			logDelivery(client_, ex.statusCode());
		}
		#ifdef NDEBUG
		catch (Exception &ex) {
			error() << ex.message() << nl;
			Format("HTTP/1.1 500 Internal Server Error: %%\r\n\r\n", client_->stream_) << ex.message();
			logDelivery(client_, 500);
		}
		#endif
		catch (TimeoutExceeded &) { debug() << "Connection timed out (" << client_->address() << ")" << nl; }
		catch (CloseRequest &) {}
		close();
		// closedConnections_->push(clientAddress); // TODO
	}
}

Response *ServiceWorker::response() const
{
	return response_;
}

void ServiceWorker::close()
{
	if (client_) {
		debug() << "Closing connection to " << client_->address() << nl;
		client_ = 0;
	}
}

} // namespace fnode
