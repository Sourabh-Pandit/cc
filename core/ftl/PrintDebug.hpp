 /*
  * Copyright (C) 2007-2013 Frank Mertens.
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation; either version
  * 2 of the License, or (at your option) any later version.
  */
#ifndef FTL_PRINTDEBUG_HPP
#define FTL_PRINTDEBUG_HPP

#include "atoms"
#include "String.hpp"
#include "Format.hpp"
#include "StandardStreams.hpp"

namespace ftl
{

inline void print(String text) { output()->write(text); }

template<class T1>
inline void print(String templateText, const T1 &x1)
{
	Format format(templateText);
	format << x1;
	output()->write(format);
}

template<class T1, class T2>
inline void print(String templateText, const T1 &x1, const T2 &x2)
{
	Format format(templateText);
	format << x1 << x2;
	output()->write(format);
}

template<class T1, class T2, class T3>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3)
{
	Format format(templateText);
	format << x1 << x2 << x3;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29, const T30 &x30)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29 << x30;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29, const T30 &x30, const T31 &x31)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29 << x30 << x31;
	output()->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32>
inline void print(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29, const T30 &x30, const T31 &x31, const T32 &x32)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29 << x30 << x31 << x32;
	output()->write(format);
}

inline void printTo(LineSink *sink, String text) { sink->write(text); }

template<class T1>
inline void printTo(LineSink *sink, String templateText, const T1 &x1)
{
	Format format(templateText);
	format << x1;
	sink->write(format);
}

template<class T1, class T2>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2)
{
	Format format(templateText);
	format << x1 << x2;
	sink->write(format);
}

template<class T1, class T2, class T3>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3)
{
	Format format(templateText);
	format << x1 << x2 << x3;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29, const T30 &x30)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29 << x30;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29, const T30 &x30, const T31 &x31)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29 << x30 << x31;
	sink->write(format);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32>
inline void printTo(LineSink *sink, String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29, const T30 &x30, const T31 &x31, const T32 &x32)
{
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29 << x30 << x31 << x32;
	sink->write(format);
}

inline void debug(String text) {
#ifndef NDEBUG
	output()->write(text);
#endif // NDEBUG
}

template<class T1>
inline void debug(String templateText, const T1 &x1)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2>
inline void debug(String templateText, const T1 &x1, const T2 &x2)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29, const T30 &x30)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29 << x30;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29, const T30 &x30, const T31 &x31)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29 << x30 << x31;
	output()->write(format);
#endif // NDEBUG
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32>
inline void debug(String templateText, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6, const T7 &x7, const T8 &x8, const T9 &x9, const T10 &x10, const T11 &x11, const T12 &x12, const T13 &x13, const T14 &x14, const T15 &x15, const T16 &x16, const T17 &x17, const T18 &x18, const T19 &x19, const T20 &x20, const T21 &x21, const T22 &x22, const T23 &x23, const T24 &x24, const T25 &x25, const T26 &x26, const T27 &x27, const T28 &x28, const T29 &x29, const T30 &x30, const T31 &x31, const T32 &x32)
{
#ifndef NDEBUG
	Format format(templateText);
	format << x1 << x2 << x3 << x4 << x5 << x6 << x7 << x8 << x9 << x10 << x11 << x12 << x13 << x14 << x15 << x16 << x17 << x18 << x19 << x20 << x21 << x22 << x23 << x24 << x25 << x26 << x27 << x28 << x29 << x30 << x31 << x32;
	output()->write(format);
#endif // NDEBUG
}

} // namespace ftl

#endif // FTL_PRINTDEBUG_HP
