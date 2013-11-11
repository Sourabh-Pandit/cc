/*
 * Copyright (C) 2013 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef FLUX_ARCHIVEENTRY_H
#define FLUX_ARCHIVEENTRY_H

#include <sys/types.h>
#include <flux/String.h>

namespace flux {

class Archive;

class ArchiveEntry: public Object
{
public:
	enum Type {
		Regular     = '0',
		Link        = '1',
		Symlink     = '2',
		CharDevice  = '3',
		BlockDevive = '4',
		Directory   = '5',
		Fifo        = '6'
	};

	inline int type() const { return type_; }
	inline String path() const { return path_; }
	inline String linkPath() const { return linkPath_; }
	inline double lastModified() const { return lastModified_; }
	inline uid_t userId() const { return userId_; }
	inline gid_t groupId() const { return groupId_; }
	inline String userName() const { return userName_; }
	inline String groupName() const { return groupName_; }
	inline int mode() const { return mode_; }
	inline off_t offset() const { return offset_; }
	inline off_t size() const { return size_; }

protected:
	friend class Archive;

	static Ref<ArchiveEntry> create() {
		return new ArchiveEntry();
	}

	ArchiveEntry()
		: type_('0')
	{}

	int type_;
	String path_;
	String linkPath_;
	double lastModified_;
	uid_t userId_;
	gid_t groupId_;
	String userName_;
	String groupName_;
	int mode_;
	off_t offset_;
	off_t size_;
};

} // namespace flux

#endif // FLUX_ARCHIVEENTRY_H