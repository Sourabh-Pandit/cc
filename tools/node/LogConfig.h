/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <cc/meta/MetaObject>

namespace ccnode {

using namespace cc;
using namespace cc::meta;

enum class LogLevel {
    Silent  = 0,
    Error   = 1,
    Warning = 2,
    Notice  = 3,
    Info    = 4,
    Debug   = 5,
#ifdef NDEBUG
    Default = Notice
#else
    Default = Debug
#endif
};

class LogConfig: public Object
{
public:
    static Ref<LogConfig> loadDefault();
    static Ref<LogConfig> load(MetaObject *config);

    String path() const { return path_; }
    LogLevel level() const { return level_; }
    double retentionPeriod() const { return retentionPeriod_; }
    double rotationInterval() const { return rotationInterval_; }

private:
    static LogLevel decodeLogLevel(const String &levelName);
    LogConfig();
    LogConfig(MetaObject *config);

    String path_;
    LogLevel level_;
    double retentionPeriod_;
    double rotationInterval_;
};

} // namespace ccnode
