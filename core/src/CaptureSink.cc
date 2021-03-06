/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/CaptureSink>

namespace cc {

Ref<CaptureSink> CaptureSink::open()
{
    return new CaptureSink;
}

CaptureSink::CaptureSink():
    parts_{StringList::create()}
{}

void CaptureSink::write(const CharArray *data)
{
    parts_->append(data);
}

String CaptureSink::collect() const
{
    return parts_->join();
}

} // namespace cc
