/*
 * Copyright (C) 2007-2015 Frank Mertens.
 *
 * Use of this source is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 */

#ifndef FLUX_YASON_H
#define FLUX_YASON_H

#include <flux/exceptions>
#include <flux/MetaObject>
#include <flux/MetaProtocol>

namespace flux {
namespace yason {

Variant parse(const ByteArray *text, const MetaProtocol *protocol = 0);
String stringify(Variant value);

}} // namespace flux::yason

#endif // FLUX_YASON_H
