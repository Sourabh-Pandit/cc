/*
 * Utf8Decoder.hpp -- UTF-8 decoder and validator
 *
 * Copyright (c) 2007-2012, Frank Mertens
 *
 * This file is part of the a free software library. You can redistribute
 * it and/or modify it under the terms of FTL's 2-clause BSD license.
 *
 * See the LICENSE.txt file for details at the top-level of FTL's sources.
 */
#ifndef FTL_UTF8DECODER_HPP
#define FTL_UTF8DECODER_HPP

#include "ByteDecoder.hpp"

namespace ftl
{

class Utf8Decoder: public Source<uchar_t>
{
public:
	inline static Ref<Utf8Decoder, Owner> newInstance(Ref<Stream> stream, int bufCapa = FTL_DEFAULT_BUF_CAPA) {
		return new Utf8Decoder(stream, bufCapa);
	}
	inline static Ref<Utf8Decoder, Owner> newInstance(const void *buf, int bufCapa = FTL_DEFAULT_BUF_CAPA) {
		return new Utf8Decoder(buf, bufCapa);
	}

	inline bool read(uchar_t *ch)
	{
		bool more = byteDecoder_->hasMore();
		if (more) {
			*ch = byteDecoder_->readUInt8();
			if ((*ch & 0x80) != 0) // distinguish 7 bit ASCII from multibyte sequence
				*ch = readMultiByte(*ch);
		}
		return more;
	}

	inline Ref<ByteDecoder> byteDecoder() const { return byteDecoder_; }

private:
	Utf8Decoder(Ref<Stream> stream, int bufCapa)
		: byteDecoder_(ByteDecoder::newInstance(stream, bufCapa))
	{}

	Utf8Decoder(const void *buf, int bufCapa)
		: byteDecoder_(ByteDecoder::newInstance(buf, bufCapa))
	{}

	uchar_t readMultiByte(uchar_t ch);

	Ref<ByteDecoder, Owner> byteDecoder_;
};

inline uchar_t Utf8Decoder::readMultiByte(uchar_t ch)
{
	int n = -1; // number of additional bytes

	// translate prefix to code length (n is the number of successive bytes)
	if ((ch >> 5) == 6) { // code prefix: 6 = (110)2
		ch = ch & 0x1F;
		n = 1;
	}
	else if ((ch >> 4) == 14) { // code prefix: 14 = (1110)2
		ch = ch & 0x0F;
		n = 2;
	}
	else if ((ch >> 3) == 30) { // code prefix: 30 = (11110)2
		ch = ch & 0x07;
		n = 3;
	}

	int n2 = n;

	// read n successive characters (chs), which carry the code prefix (10)2
	while (n > 0) {
		uint8_t chs = byteDecoder_->readUInt8();
		if ((chs >> 6) == 2) // 2 = (10)2
			ch = (ch << 6) | (chs & 0x3F);
		else
			break;
		--n;
	}

	// enforce minimum code length
	if (n == 0) {
		if (n2 == 1) {
			if (ch < 0x80) n = -1;
		}
		else if (n2 == 2) {
			if (ch < 0x800) n = -1;
		}
		else if (n2 == 3) {
			if (ch < 0x10000) n = -1;
		}
	}

	if (n < 0)
		FTL_THROW(EncodingException, "Input data is not conforming to UTF-8 encoding");

	return ch;
}

} // namespace ftl

#endif // FTL_UTF8DECODER_HPP
