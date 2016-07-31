/*
 * Copyright (C) 2007-2016 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <cc/Object>

namespace cc {
namespace net {
    class SocketAddress;
}}

namespace ccnode {

using namespace cc;
using namespace cc::net;

class ConnectionManager;

class ConnectionInfo: public Object
{
public:
    static Ref<ConnectionInfo> create(const SocketAddress *remoteAddress);

    inline const SocketAddress *remoteAddress() const { return remoteAddress_; }
    inline int priority() const { return priority_; }

    inline uint64_t originAddress() const { return originAddress_; }
    inline double arrivalTime() const { return arrivalTime_; }
    inline double departureTime() const { return departureTime_; }

    void updateDepartureTime();

private:
    friend class ConnectionManager;

    ConnectionInfo(const SocketAddress *remoteAddress);
    inline void setPriority(int newPriority) { priority_ = newPriority; }

    Ref<const SocketAddress> remoteAddress_;
    int priority_;
    uint64_t originAddress_;
    double arrivalTime_;
    double departureTime_;
};

} // namespace ccnode