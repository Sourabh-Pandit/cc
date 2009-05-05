/*
 * MemoryMapping.hpp -- file backed / virtual memory mappings
 *
 * Copyright (c) 2007-2009, Frank Mertens
 *
 * See ../LICENSE for the license.
 */
#ifndef PONA_MEMORYMAPPING_HPP
#define PONA_MEMORYMAPPING_HPP

#include <sys/mman.h>
#include "atom"
#include "File.hpp"

namespace pona
{

class MemoryMapping: public Instance
{
public:
	enum Type {
		Shared  = MAP_SHARED,
		Private = MAP_PRIVATE
	};
	
	enum ProtectionFlags {
		Read    = PROT_READ,
		Write   = PROT_WRITE,
		Execute = PROT_EXEC
	};
	
	MemoryMapping(Ref<File> file, off_t offset, size_t length, int type = Shared);
	MemoryMapping(size_t length, int protection = Read|Write, int type = Shared);
	~MemoryMapping();
	
	inline void* start() const { return start_; }
	inline int length() const { return length_; }
	
private:
	void* start_;
	int length_;
};

} // namespace pona

#endif // PONA_MEMORYMAPPING_HPP
