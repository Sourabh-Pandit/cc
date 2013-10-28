/*
 * Copyright (C) 2013 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef FNODE_CLIENTCONNECTION_H
#define FNODE_CLIENTCONNECTION_H

#include <fkit/StreamSocket.h>
#include "Request.h"

namespace fnode
{

using namespace fkit;

class ServiceWorker;
class RequestStream;

class ClientConnection: public Object
{
public:
	static Ref<ClientConnection> create(StreamSocket *socket);

	inline Stream *stream() const { return stream_; }
	inline SocketAddress *address() const { return address_; }
	inline Request *request() const { return request_; }

	Ref<Request> readRequest();

	void putBack(Request *request);

	void setupTimeout(double interval);
	bool isPayloadConsumed() const;

private:
	friend class ServiceWorker;

	ClientConnection(StreamSocket *socket);

	Ref<Request> scanRequest();

	Ref<RequestStream> requestStream_;
	Ref<Stream> stream_;
	Ref<SocketAddress> address_;
	Ref<Request> request_, pendingRequest_;
};

} // namespace fnode

#endif // FNODE_CLIENTCONNECTION_H