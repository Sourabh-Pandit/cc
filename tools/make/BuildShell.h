/*
 * Copyright (C) 2007-2013 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef FLUXMAKE_BUILDSHELL_H
#define FLUXMAKE_BUILDSHELL_H

#include <flux/String.h>

namespace flux { class FileStatus; }

namespace fluxmake
{

using namespace flux;

class BuildPlan;

class BuildShell
{
public:
	BuildShell(BuildPlan *plan);
	inline BuildPlan *plan() const { return plan_; }

	String beautify(String command);
	bool run(String command);

	Ref<FileStatus> fileStatus(String path);

	void mkdir(String path);
	void rmdir(String path);
	void symlink(String path, String newPath);

	bool install(String sourcePath, String destPath);
	bool unlink(String path);

private:
	BuildPlan *plan_;
};

} // namespace fluxmake

#endif // FLUXMAKE_BUILDSHELL_H
