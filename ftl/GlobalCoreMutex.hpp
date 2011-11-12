/*
 * GlobalCoreMutex.hpp -- process-vide spin mutex
 *
 * Copyright (c) 2007-2011, Frank Mertens
 *
 * See ../COPYING for the license.
 */
#ifndef FTL_GLOBALCOREMUTEX_HPP
#define FTL_GLOBALCOREMUTEX_HPP

#include "Instance.hpp"
#include "SpinLock.hpp"
#include "Ref.hpp"

namespace ftl
{

class GlobalCoreMutex;

class GlobalCoreMutexInitializer
{
public:
	GlobalCoreMutexInitializer();
private:
	static int count_;
};

namespace { GlobalCoreMutexInitializer globalCoreMutexInitializer; }

class GlobalCoreMutex: public SpinLock
{
public:
	static GlobalCoreMutex* instance();
	
private:
	GlobalCoreMutex() {}
};

inline GlobalCoreMutex* globalCoreMutex() { return GlobalCoreMutex::instance(); }

} // namespace ftl

#endif // FTL_GLOBALCOREMUTEX_HPP
