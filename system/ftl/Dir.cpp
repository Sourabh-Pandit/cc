/*
 * Dir.cpp -- file directory I/O
 *
 * Copyright (c) 2007-2012, Frank Mertens
 *
 * This file is part of the a free software library. You can redistribute
 * it and/or modify it under the terms of FTL's 2-clause BSD license.
 *
 * See the LICENSE.txt file for details at the top-level of FTL's sources.
 */

#include <sys/stat.h> // mkdir
#include <sys/types.h> // mode_t

#include "File.hpp"
#include "FileStatus.hpp"
#include "Dir.hpp"

namespace ftl
{

Dir::Dir(String path)
	: path_(path),
	  dir_(0)
{}

Dir::~Dir()
{
	if (isOpen()) close();
}

String Dir::path() const { return path_; }

bool Dir::access(int flags) { return file(path_)->access(flags); }

bool Dir::exists() const
{
	return file(path_)->exists() && (fileStatus(path_)->type() == File::Directory);
}

void Dir::create(int mode)
{
	if (::mkdir(path_, mode) == -1)
		FTL_SYSTEM_EXCEPTION;
}

void Dir::unlink()
{
	if (::rmdir(path_))
		FTL_SYSTEM_EXCEPTION;
}

void Dir::open()
{
	if (dir_) return;
	dir_ = ::opendir(path_);
	if (!dir_)
		FTL_SYSTEM_EXCEPTION;
}

void Dir::close()
{
	if (!dir_) return;
	if (::closedir(dir_) == -1)
		FTL_SYSTEM_EXCEPTION;
	dir_ = 0;
}

bool Dir::read(DirEntry *entry)
{
	if (!isOpen()) open();
	struct dirent *buf = entry;
	struct dirent *result;
	mem::clr(buf, sizeof(struct dirent)); // for paranoid reason
	int errorCode = ::readdir_r(dir_, buf, &result);
	if (errorCode)
		throw SystemException(__FILE__, __LINE__, "SystemException", str::cat("readdir_r() failed: error code = ", ftl::intToStr(errorCode)), errorCode);

	entry->path_ = String(entry->d_name)->makeAbsolutePathRelativeTo(path_);
	return result;
}

bool Dir::isOpen() const { return dir_; }

void Dir::establish(int mode)
{
	Ref<StringList, Owner> missingDirs = StringList::newInstance();
	String path = path_;
	while ((path != "") && (path != "/")) {
		if (exists()) break;
		missingDirs->push(path);
		path = path->reducePath();
	}
	while (missingDirs->length() > 0)
		Dir::newInstance(missingDirs->pop())->create(mode);
}

} // namespace ftl
