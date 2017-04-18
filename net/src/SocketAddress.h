/*
 * Copyright (C) 2007-2016 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <arpa/inet.h>
#include <netinet/in.h> // sockaddr_in, etc.
#include <netdb.h> // addrinfo
#include <sys/socket.h> // connect
#include <sys/un.h> // sockaddr_un

#include <cc/exceptions>
#include <cc/String>
#include <cc/List>

namespace cc {

class SystemStream;
template<class> class Singleton;

namespace net {

class SocketAddress;

typedef List< Ref<SocketAddress> > SocketAddressList;

class LocationSyntaxError: public UsageError
{
public:
    LocationSyntaxError(String message): UsageError(message) {}
};

class HostNameResolutionError: public UsageError
{
public:
    HostNameResolutionError(String message): UsageError(message) {}
};

/** \class SocketAddress SocketAddress.h cc/net/SocketAddress
  * \brief Socket address
  */
class SocketAddress: public Object
{
public:
    /** Create an invalid socket address
      * \return new object instance
      */
    inline static Ref<SocketAddress> create() {
        return new SocketAddress;
    }

    /** Create a socket address by given protocol family and numerical address.
      * Use the wildcard "*" to address all interfaces of the local host system.
      *
      * \param family protocol family (AF_UNSPEC, AF_INET, AF_INET6 or AF_LOCAL)
      * \param address numerical host address, wildcard ("*") or file path
      * \param port service port
      * \return new object instance
      */
    inline static Ref<SocketAddress> create(int family, String address = String(), int port = 0) {
        return new SocketAddress(family, address, port);
    }

    /** Create an IPv4 broadcast address
      * \return new object instance
     */
    static Ref<SocketAddress> createBroadcast(int port);

    /** Create a socket address from a low-level IPv4 socket address
      * \return new object instance
      */
    inline static Ref<SocketAddress> create(struct sockaddr_in *addr) {
        return new SocketAddress(addr);
    }

    /** Create a socket address from a low-level IPv6 socket address
      * \return new object instance
      */
    inline static Ref<SocketAddress> create(struct sockaddr_in6 *addr) {
        return new SocketAddress(addr);
    }

    /** Create a socket address from a low-level address resolution result
      * \return new object instance
      */
    inline static Ref<SocketAddress> create(addrinfo *info) {
        return new SocketAddress(info);
    }

    /** Read a location string in form of an Uniform Resource Indentifier
      * \return new object instance
      */
    static Ref<SocketAddress> read(String location);

    /** Create a deep copy of another socket address
      * \return new object instance
      */
    static Ref<SocketAddress> copy(const SocketAddress *other);

    /// Check if this address is a valid address
    bool isValid() const;

    int family() const; ///< Socket address family
    int socketType() const; ///< Socket type (if this address is a result of name resolution)
    int protocol() const;  ///< Socket protocol (if this address is a result of name resolution)
    int port() const; ///< Service port
    void setPort(int port); ///< Change the service port

    String networkAddress() const; ///< Convert the network address to a string (sans port number)
    String toString() const; ///< Convert the full address to a string (with port number)

    int scope() const; ///< IPv6 scope of this address
    void setScope(int scope); ///< Change the IPv6 scope

    /** Query the complete connection information for given host name, service name and
      * protocol family. The call blocks until the local resolver has resolved the
      * host name. This may take several seconds.
      *   Depending on supported protocol stacks and service availability in
      * different protocols (UDP/TCP) and number of network addresses of the
      * queried host multiple SocketAddress objects will be returned.
      *   An empty list is returned, if the host name is unknown, service is
      * not available or protocol family is not supported by the host.
      *   The host name can be a short name relative to the local domain.
      * The fully qualified domain name (aka canonical name) can be optionally retrieved.
      */
    static Ref<SocketAddressList> resolve(String hostName, String serviceName = String(), int family = AF_UNSPEC, int socketType = 0, String *canonicalName = 0);

    /** Lookup the host name of given address. Usually a reverse DNS
      * lookup will be issued, which may take several seconds.
      */
    String lookupHostName(bool *failed = 0) const;

    /** Lookup the service name. In most setups the service name will be looked up
      * in a local file (/etc/services) and therefore the call returns immediately.
      */
    String lookupServiceName() const;

    /** Returns the network prefix of an IPv6 address (the first 64 bits).
      * For IPv4 addresses the entire address is returned.
      */
    uint64_t networkPrefix() const;

    /** See if this address equals address b
      */
    bool equals(const SocketAddress *b) const;

    /** Size of the address in bits
      */
    inline int length() const { return 8 * addrLen(); }

    struct sockaddr *addr(); ///< Provide access to the underlying low-level address structure
    const struct sockaddr *addr() const; ///< Provide access to the underlying low-level address structure (read-only)
    int addrLen() const; ///< Size of the underlying low-level address structure in bytes

protected:
    friend class Singleton<SocketAddress>;

    SocketAddress();
    SocketAddress(int family, String address, int port);
    SocketAddress(struct sockaddr_in *addr);
    SocketAddress(struct sockaddr_in6 *addr);
    SocketAddress(addrinfo *info);
    SocketAddress(const SocketAddress *other);

    union {
        struct sockaddr addr_;
        struct sockaddr_in inet4Address_;
        struct sockaddr_in6 inet6Address_;
        struct sockaddr_un localAddress_;
    };

    int socketType_;
    int protocol_;
};

}} // namespace cc::net
