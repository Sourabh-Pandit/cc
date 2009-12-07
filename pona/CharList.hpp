/*
 * CharList.hpp -- Unicode character list
 *
 * Copyright (c) 2007-2009, Frank Mertens
 *
 * See ../LICENSE for the license.
 */
#ifndef PONA_CHARLIST_HPP
#define PONA_CHARLIST_HPP

#include "atoms"
#include "List.hpp"
#include "CString.hpp"

namespace pona
{

class CharList: public List<Char>
{
public:
	typedef List<Char> Super;
	
	CharList() {}
	
	int toInt(bool* ok = 0);
	double toFloat(bool* ok = 0);
	int64_t toInt64(bool* ok = 0);
	uint64_t toUInt64(bool* ok = 0);
	float64_t toFloat64(bool* ok = 0);
	
	Ref<CharList, Owner> toLower() const;
	Ref<CharList, Owner> toUpper() const;
	Ref<CharList, Owner> stripLeadingSpace() const;
	Ref<CharList, Owner> stripTrailingSpace() const;
	
	CString utf8() const;
	uint32_t crc32() const;
	
	char* strdup() const;
	
private:
	CharList(Ref<Super> parent, int i, int n);
	virtual Ref<Super, Owner> newList() const;
	virtual Ref<Super, Owner> newChildList(Ref<Super> parent, int i, int n) const;
};

} // namespace pona

#endif // PONA_CHARLIST_HPP