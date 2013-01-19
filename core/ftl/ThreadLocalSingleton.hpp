 /*
  * Copyright (C) 2007-2013 Frank Mertens.
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation; either version
  * 2 of the License, or (at your option) any later version.
  */
#ifndef FTL_THREADLOCALSINGLETON_HPP
#define FTL_THREADLOCALSINGLETON_HPP

#include "Instance.hpp"
#include "Ref.hpp"
#include "ThreadLocalOwner.hpp"
#include "LocalStatic.hpp"

namespace ftl
{

template<class SubClass>
class ThreadLocalSingleton
{
public:
	static Ref<SubClass> instance()
	{
		Ref<SubClass, ThreadLocalOwner> &instance_ = localStatic< Ref<SubClass, ThreadLocalOwner>, ThreadLocalSingleton<SubClass> >();
		if (!instance_)
			instance_ = new SubClass;
		return instance_;
	}
};

} // namespace ftl

#endif // FTL_THREADLOCALSINGLETON_HPP
