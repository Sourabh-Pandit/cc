/*
 * Copyright (C) 2013 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef FNODE_LOGPROTOTYPE_H
#define FNODE_LOGPROTOTYPE_H

#include <fkit/Yason.h>
#include <fkit/Date.h>

namespace fnode
{

using namespace fkit;

class LogPrototype: public YasonObject
{
public:
	static Ref<LogPrototype> create() { return new LogPrototype; }

private:
	LogPrototype()
		: YasonObject("Log")
	{
		insert("path", "");
		insert("level", "");
		insert("retention", days(30));
		insert("rotation", days(1));
	}
};

} // namespace fnode

#endif // FNODE_LOGPROTOTYPE_H
