/*
 * Copyright (C) 2007-2013 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "stdio.h"
#include "Queue.h"
#include "NullStream.h"
#include "Format.h"

namespace fkit
{

FormatSignal nl;
FormatSignal flush;

Format::Format(String pattern, Stream *stream)
	: stream_(stream),
	  isNull_(stream && nullStream() ? stream == nullStream() : false)
{
	if (isNull_) return;
	set(StringList::create());
	int i0 = 0, n = 0;
	while (true) {
		int i1 = pattern->find("%%", i0);
		if (i0 < i1)
			get()->append(pattern->copy(i0, i1));
		if (i1 == pattern->size()) break;
		int j = get()->size() + n;
		if (!placeHolder_) placeHolder_ = Queue<int>::create();
		placeHolder_->push(j);
		++n;
		i0 = i1 + 2;
	}
}

Format::Format(Stream *stream)
	: stream_(stream),
	  isNull_(stream && nullStream() ? stream == nullStream() : false)
{
	set(StringList::create());
}

Format::~Format()
{
	flush();
}

void Format::flush()
{
	if (isNull_) return;
	if (stream_ && get()->size() > 0) {
		stream_->write(get());
		get()->clear();
	}
}

Format::Format(const Format &b)
	: Super(b.get()),
	  stream_(b.stream_),
	  isNull_(b.isNull_),
	  placeHolder_(b.placeHolder_)
{}

Format &Format::operator=(const Format &b)
{
	set(b.get());
	stream_ = b.stream_;
	placeHolder_ = b.placeHolder_;
	isNull_ = b.isNull_;
	return *this;
}

Format &Format::operator<<(const String &s)
{
	if (isNull_) return *this;
	int j = get()->size();
	if (placeHolder_) {
		if (placeHolder_->size() > 0)
			j = placeHolder_->pop();
	}
	get()->insert(j, s);
	return *this;
}

Format &Format::operator<<(const FormatSignal &s)
{
	if (isNull_) return *this;
	if (&s == &fkit::nl) operator<<(String("\n"));
	else if (&s == &fkit::flush) Format::flush();
	return *this;
}

} // namespace fkit
