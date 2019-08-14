/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <cc/meta/yason>
#include "ServiceDelegate.h"
#include "ServiceInstance.h"

namespace ccnode {

using namespace cc;

class ServicePrototype: public MetaObject
{
public:
    static Ref<ServicePrototype> create(const String &className, MetaProtocol *protocol = nullptr);

protected:
    ServicePrototype(const String &className, MetaProtocol *protocol);
};

class ServiceWorker;

class ServiceDefinition: public Object
{
public:
    virtual ServicePrototype *configPrototype() const = 0;
    virtual Ref<ServiceInstance> createInstance(const MetaObject *config) const = 0;
};

} // namespace ccnode
