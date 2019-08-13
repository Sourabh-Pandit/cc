/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/Singleton>
#include <cc/Process>
#include "SecurityPrototype.h"
#include "LogPrototype.h"
#include "NodeConfigProtocol.h"

namespace ccnode {

class NodePrototype: public MetaObject
{
public:
    static Ref<NodePrototype> create(MetaProtocol *protocol = nullptr, const String &className = "Node")
    {
        return new NodePrototype{className, protocol};
    }

protected:
    NodePrototype(const String &className, MetaProtocol *protocol):
        MetaObject{className, protocol}
    {
        bool superUser = Process::isSuperUser();
        establish("address", "*");
        establish("port",
            superUser ?
            (List<int>::create() << 80 << 443) :
            (List<int>::create() << 8080 << 4443)
        );
        establish("protocol-family", "");
        establish("user", "");
        establish("group", "");
        establish("version", "ccnode");
        establish("daemon", false);
        establish("daemon-name", "ccnode");
        establish("concurrency",
            #ifdef NDEBUG
            256
            #else
            16
            #endif
        );
        establish("service-window", 30);
        establish("connection-limit", 32);
        establish("connection-timeout", 10.);
        establish("security", SecurityPrototype::create());
        establish("error-log", LogPrototype::create());
        establish("access-log", LogPrototype::create());
    }
};

NodeConfigProtocol *NodeConfigProtocol::instance()
{
    return Singleton<NodeConfigProtocol>::instance();
}

NodeConfigProtocol::NodeConfigProtocol():
    nodeProtocol_{MetaProtocol::create()},
    nodePrototype_{NodePrototype::create(nodeProtocol_)}
{
    define(nodePrototype_);
}

void NodeConfigProtocol::registerService(MetaObject *configPrototype)
{
    nodeProtocol_->define(configPrototype);
}

} // namespace ccnode
