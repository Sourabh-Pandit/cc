/*
 * Copyright (C) 2007-2019 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/node/HttpServerSocket>
#include <cc/node/HttpServerSecurity>
#include <cc/node/DeliveryInstance>
#include <cc/node/NodeConfig>
#include <cc/node/SecurityCache>
#include <cc/node/exceptions>
#include <cc/node/debug>
#include <cc/assert>
#include <cc/ThreadLocalSingleton>
#include <cc/System>
#include <cc/NullStream>
#include <stddef.h>
#include <unistd.h>

namespace cc {
namespace node {

Ref<HttpServerSocket> HttpServerSocket::accept(StreamSocket *listeningSocket, const NodeConfig *nodeConfig, SecurityCache *securityCache)
{
    Ref<HttpServerSocket> client =
        new HttpServerSocket{
            SocketAddress::create(listeningSocket->address()->family()),
            (listeningSocket->address()->port() % 80 == 0) ? 0 : Secure,
            nodeConfig,
            securityCache
        };
    client->fd_ = StreamSocket::accept(listeningSocket, client->address_);
    client->connected_ = true;
    client->mode_ |= Connected | ((client->mode_ & Secure) ? 0 : Open);
    client->initSession();
    return client;
}

HttpServerSocket::HttpServerSocket(const SocketAddress *address, int mode, const NodeConfig *nodeConfig, SecurityCache *securityCache):
    HttpSocket{address, mode},
    nodeConfig_{nodeConfig},
    securityCache_{securityCache}
{}

HttpServerSocket::~HttpServerSocket()
{
    if (mode_ & Secure)
    {
        if (mode_ & Open) {
            int ret = gnutls_bye(session_, GNUTLS_SHUT_WR);
            if (ret != GNUTLS_E_SUCCESS)
                CCNODE_ERROR() << gnutls_strerror(ret) << nl;
        }

        if (mode_ & Connected)
            gnutls_deinit(session_);
    }
}

const LoggingInstance *HttpServerSocket::errorLoggingInstance() const
{
    return nodeConfig_->errorLoggingInstance();
}

class ClientHelloContext: public Object
{
public:
    static ClientHelloContext *instance()
    {
        return ThreadLocalSingleton<ClientHelloContext>::instance();
    }

    void init(const NodeConfig *nodeConfig)
    {
        nodeConfig_ = nodeConfig;
    }

    void selectService(gnutls_session_t session)
    {
        try {
            size_t size = 0;
            unsigned type = 0;
            int ret = gnutls_server_name_get(session, NULL, &size, &type, 0);
            if (type == GNUTLS_NAME_DNS) {
                CC_ASSERT(ret == GNUTLS_E_SHORT_MEMORY_BUFFER);
                serverName_ = String(size);
                ret = gnutls_server_name_get(session, mutate(serverName_)->bytes(), &size, &type, 0);
                if (ret != GNUTLS_E_SUCCESS) {
                    CCNODE_ERROR() << peerAddress_ << ": " << gnutls_strerror(ret) << nl;
                    serverName_ = "";
                }
                if (serverName_->count() > 0) {
                    if (serverName_->at(serverName_->count() - 1) == 0)
                        mutate(serverName_)->truncate(serverName_->count() - 1);
                    if (errorLoggingInstance()->infoStream() != NullStream::instance())
                        CCNODE_INFO() << "TLS client hello: SNI=\"" << serverName_ << "\"" << nl;
                    deliveryInstance_ = nodeConfig_->selectService(serverName_);
                    if (deliveryInstance_)
                        deliveryInstance_->security()->establish(session, peerAddress_);
                }
            }
        }
        catch (Exception &ex) {
            CCNODE_ERROR() << peerAddress_ << ": " << ex << nl;
        }
    }

    void reset(const SocketAddress *peerAddress)
    {
        peerAddress_ = peerAddress;
        serverName_ = "";
        deliveryInstance_ = nullptr;
    }

    String serverName() const { return serverName_; }
    const DeliveryInstance *deliveryInstance() const { return deliveryInstance_; }

private:
    friend class ThreadLocalSingleton<ClientHelloContext>;

    ClientHelloContext() {}

    const LoggingInstance *errorLoggingInstance() const { return nodeConfig_->errorLoggingInstance(); }

    Ref<const SocketAddress> peerAddress_;
    String serverName_;
    const NodeConfig *nodeConfig_ { nullptr };
    const DeliveryInstance *deliveryInstance_ { nullptr };
};

void HttpServerSocket::initSession()
{
    CC_ASSERT(mode_ & Connected);

    t0_ = System::now();
    te_ = t0_ + nodeConfig()->connectionTimeout();

    if (!(mode_ & Secure)) return;

    CC_ASSERT(!(mode_ & Open));

    gnuTlsCheckSuccess(gnutls_init(&session_, GNUTLS_SERVER));

    gnuTlsCheckSuccess(gnutls_set_default_priority(session_));

    nodeConfig()->security()->establish(session_);

    ClientHelloContext::instance()->init(nodeConfig());

    gnutls_handshake_set_post_client_hello_function(session_, onClientHello);
    HttpSocket::initTransport();

    securityCache_->prepareSessionResumption(session_);
}

int HttpServerSocket::onClientHello(gnutls_session_t session)
{
    ClientHelloContext::instance()->selectService(session);
    return 0;
}

const DeliveryInstance *HttpServerSocket::handshake()
{
    CC_ASSERT(mode_ & Connected);

    if (!(mode_ & Secure)) return 0;

    CC_ASSERT(!(mode_ & Open));

    ClientHelloContext::instance()->reset(address());

    while (true) {
        int ret = gnutls_handshake(session_);
        if (ret == GNUTLS_E_SUCCESS) break;
        if (ret < 0) {
            if (gnutls_error_is_fatal(ret))
                gnuTlsCheckSuccess(ret);
        }
    }

    mode_ |= Open;

    if (errorLoggingInstance()->infoStream() != NullStream::instance()) {
        double t1 = System::now();
        CCNODE_INFO() << "TLS handshake took " << int(1000 * (t1 - t0_)) << "ms" << nl;
    }

    const DeliveryInstance *deliveryInstance = ClientHelloContext::instance()->deliveryInstance();
    if (!deliveryInstance) {
        if (nodeConfig()->deliveryInstances()->count() == 1)
            deliveryInstance = nodeConfig()->deliveryInstances()->at(0);
        if (ClientHelloContext::instance()->serverName() == "")
            deliveryInstance = nodeConfig()->selectService("");
    }

    return deliveryInstance;
}

void HttpServerSocket::upgradeToSecureTransport()
{
    CC_ASSERT(mode_ & Connected);
    CC_ASSERT(!(mode_ & Secure));

    mode_ = mode_ & ~Open;
    mode_ |= Secure;
    initSession();
}

bool HttpServerSocket::waitInput()
{
    double d = te_ - System::now();
    if (d <= 0) throw RequestTimeout{};
    return waitFor(IoReady::Read, d * 1000);
}

void HttpServerSocket::ioException(Exception &ex) const
{
    CCNODE_ERROR() << "!" << ex << nl;
}

}} // namespace cc::node
