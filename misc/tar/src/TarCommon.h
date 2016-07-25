/*
 * Copyright (C) 2007-2016 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <cc/ByteArray>

namespace cc {
namespace tar {

unsigned tarHeaderSum(ByteArray *data);

}} // namespace cc::tar

