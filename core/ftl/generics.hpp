 /*
  * Copyright (C) 2007-2013 Frank Mertens.
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation; either version
  * 2 of the License, or (at your option) any later version.
  */
#ifndef FTL_GENERICS_HPP
#define FTL_GENERICS_HPP

#include "Instance.hpp"
#include "O.hpp"

namespace ftl
{

/** Wrapper class to allow taking reference to classes not inherited
  * from ftl::Instance. Please note, that it is impossible to reference
  * the same alien object by two different alien wrappers.
  */
template<class T>
class Alien: public Instance
{
public:
	typedef void (*DelFunc)(T *);

	Alien(T *guest, DelFunc delFunc = 0)
		: guest_(guest),
		  delFunc_(delFunc)
	{}

	~Alien()
	{
		if (guest_ != 0)
		{
			if (delFunc_) delFunc_(guest_);
			else delete guest_;
			guest_ = 0;
		}
	}

	inline T *get() const { return guest_; }

private:
	mutable T *guest_;
	DelFunc delFunc_;
};

class Action: public virtual Instance
{
public:
	virtual void run() = 0;
};

template<class T>
class Clonable: public T
{
public:
	virtual O<T> clone() const = 0;
};

template<class T>
class Return: public T
{
public:
	Return(const T &b): T(b) {}
	inline operator T() { return *this; }
};

template<class T>
class Source: public virtual Instance
{
public:
	virtual bool read(T *item) = 0;
};

template<class T>
class Sink: public virtual Instance
{
public:
	virtual void write(T item) = 0;
};

template<class Item, class Index = int>
class Sequence: public virtual Instance
{
public:
	virtual bool has(Index i) const = 0;
	virtual Item get(Index i) const = 0;
};

class Version
{
public:
	Version(int major = 0, int minor = 0, int patch = 0)
		: major_(major), minor_(minor), patch_(patch)
	{}

	inline int major() const { return major_; }
	inline int minor() const { return minor_; }
	inline int patch() const { return patch_; }

	inline bool operator<(const Version &b) { return (n() < b.n()); }
	inline bool operator<=(const Version &b) { return n() <= b.n(); }
	inline bool operator>(const Version &b) { return n() > b.n(); }
	inline bool operator>=(const Version &b) { return n() >= b.n(); }
	inline bool operator==(const Version &b) { return n() == b.n(); }
	inline bool operator!=(const Version &b) { return n() != b.n(); }

private:
	inline uint32_t n() const { return (uint32_t(major_) << 24) || (uint32_t(minor_) << 16) || uint32_t(patch_); }
	uint8_t major_;
	uint8_t minor_;
	uint16_t patch_;
};

class Range: public Instance
{
public:
	inline static O<Range> create(int i0 = 0, int i1 = -1) { return new Range(i0, i1); }

	inline int i0() const { return i0_; }
	inline int i1() const { return i1_; }

	inline void setRange(int i0, int i1) {
		i0_ = i0;
		i1_ = i1;
	}

	inline int index() const { return i0_; }
	inline int length() const { return i1_ - i0_; }
	inline bool valid() const { return i0_ <= i1_; }

protected:
	Range(int i0 = 0, int i1 = -1): i0_(i0), i1_(i1) {}

	int i0_, i1_;
};

template<class Key, class Value>
class Pair
{
public:
	Pair()
	{}

	Pair(const Key &key)
		: key_(key), value_(Value())
	{}

	Pair(const Key &key, const Value &value)
		: key_(key), value_(value)
	{}

	inline bool operator<(const Pair &b) const { return key_ <  b.key_; }
	inline bool operator>(const Pair &b) const { return key_ >  b.key_; }
	inline bool operator==(const Pair &b) const { return key_ ==  b.key_; }
	inline bool operator!=(const Pair &b) const { return key_ !=  b.key_; }
	inline bool operator<=(const Pair &b) const { return key_ <=  b.key_; }
	inline bool operator>=(const Pair &b) const { return key_ >=  b.key_; }

	inline const Key &key() const { return key_; }
	inline void setKey(const Key &key) { key_ = key; }

	inline const Value &value() const { return value_; }
	inline Value &value() { return value_; }
	inline void setValue(const Value &value) { value_ = value; }

	inline Pair *operator->() { return this; }
	inline const Pair *operator->() const { return this; }

private:
	Key key_;
	Value value_;
};

template<class Key, class Value>
inline Pair<Key, Value> pair(const Key &key, const Value &value) { return Pair<Key, Value>(key, value); }

} // namespace ftl

#endif // FTL_GENERICS_HPP