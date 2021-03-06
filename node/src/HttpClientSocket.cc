/*
 * Copyright (C) 2007-2019 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <gnutls/gnutls.h>
#include <cc/assert>
#include <cc/System>
#include <cc/IoMonitor>
#include <cc/node/HttpClientSocket>

namespace cc {
namespace node {

Ref<HttpClientSocket> HttpClientSocket::create(const SocketAddress *serverAddress, const String &serverName, const HttpClientSecurity *security)
{
    return new HttpClientSocket{serverAddress, serverName, security};
}

Ref<HttpClientSocket> HttpClientSocket::connect(const SocketAddress *serverAddress, const String &serverName, const HttpClientSecurity *security)
{
    auto socket = HttpClientSocket::create(serverAddress, serverName, security);
    socket->connect();
    return socket;
}

HttpClientSocket::HttpClientSocket(const SocketAddress *serverAddress, const String &serverName, const HttpClientSecurity *security):
    HttpSocket{serverAddress, (serverAddress->port() % 80 == 0) ? 0 : Secure},
    serverName_{serverName},
    security_{security},
    ioMonitor_{IoMonitor::create(2)},
    readyRead_{0}
{
    if ((mode_ & Secure) && !security_)
        security_ = HttpClientSecurity::createDefault();

    StreamSocket::connect(&controlMaster_, &controlSlave_);
    ioMonitor_->addEvent(IoReady::Read, controlSlave_);
}

bool HttpClientSocket::isSecure() const
{
    return mode_ & Secure;
}

bool HttpClientSocket::connect()
{
    StreamSocket::connect();
    if (StreamSocket::isConnected()) {
        mode_ |= Connected;
    }
    else {
        const IoEvent *connectionEstablished = ioMonitor_->addEvent(IoReady::Write, this);
        if (ioMonitor_->waitFor(connectionEstablished)) mode_ |= Connected;
        ioMonitor_->removeEvent(connectionEstablished);
    }
    if (mode_ & Connected) {
        readyRead_ = ioMonitor_->addEvent(IoReady::Read, this);
        initSession();
        handshake();
    }
    return mode_ & Connected;
}

void HttpClientSocket::shutdown()
{
    controlMaster_ = nullptr;
}

void HttpClientSocket::initSession()
{
    if (!(mode_ & Secure)) return;

    gnuTlsCheckSuccess(gnutls_init(&session_, GNUTLS_CLIENT));
    security_->establish(session_);
    gnuTlsCheckSuccess(gnutls_server_name_set(session_, GNUTLS_NAME_DNS, serverName_->chars(), serverName_->count()));
    initTransport();
}

void HttpClientSocket::handshake()
{
    if (!(mode_ & Secure)) return;

    while (true) {
        int ret = gnutls_handshake(session_);
        if (ret == GNUTLS_E_SUCCESS) break;
        if (ret < 0) {
            if (gnutls_error_is_fatal(ret))
                gnuTlsCheckSuccess(ret);
        }
    }

    mode_ |= Open;
}

bool HttpClientSocket::waitInput()
{
    return ioMonitor_->waitFor(readyRead_);
}

void HttpClientSocket::ioException(Exception &ex) const
{
    // FIXME: need a thread local singleton to propagate this exception
}

}} // namespace cc::node
