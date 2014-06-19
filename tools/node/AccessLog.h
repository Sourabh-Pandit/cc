/*
 * Copyright (C) 2013 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef FLUXNODE_ACCESSLOG_H
#define FLUXNODE_ACCESSLOG_H

#include "Log.h"

namespace flux { template<class> class ThreadLocalSingleton; }

namespace fluxnode
{

class AccessLog: public Log
{
private:
	friend class ThreadLocalSingleton<AccessLog>;
};

AccessLog *accessLog();

} // namespace fluxnode

#endif // FLUXNODE_ACCESSLOG_H
