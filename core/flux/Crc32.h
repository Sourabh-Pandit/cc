/*
 * Copyright (C) 2007-2013 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef FLUX_CRC32_H
#define FLUX_CRC32_H

#include "types.h"
#include "strings.h"
#include "ByteArray.h"

namespace flux
{

class Crc32
{
public:
	Crc32(uint32_t seed = ~uint32_t(0))
		: crc_(seed)
	{}

	void feed(const void *buf, int bufFill);
	inline uint32_t sum() const { return crc_; }

private:
	uint32_t crc_;
};

inline uint32_t crc32(const void *buf, int bufSize) {
	Crc32 crc;
	crc.feed(buf, bufSize);
	return crc.sum();
}

inline uint32_t crc32(const char *s) {
	Crc32 crc;
	crc.feed(s, strlen(s));
	return crc.sum();
}

inline uint32_t crc32(ByteArray *buf) {
	Crc32 crc;
	crc.feed(buf->bytes(), buf->count());
	return crc.sum();
}

} // namespace flux

#endif // FLUX_CRC32_H
