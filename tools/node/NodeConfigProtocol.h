/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <cc/meta/MetaProtocol>

namespace cc { template<class> class Singleton; }

namespace ccnode {

using namespace cc;
using namespace cc::meta;

class NodeConfig;
class DeliveryRegistry;

class NodeConfigProtocol: public MetaProtocol
{
private:
    friend class Singleton<NodeConfigProtocol>;
    friend class NodeConfig;
    friend class DeliveryRegistry;

    static NodeConfigProtocol *instance();
    void registerService(MetaObject *configPrototype);

    NodeConfigProtocol();
    Ref<MetaProtocol> nodeProtocol_;
    Ref<MetaObject> nodePrototype_;
};

} // namespace ccnode
