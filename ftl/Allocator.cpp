/*
 * Allocator.cpp -- dynamic memory allocation
 *
 * Copyright (c) 2007-2011, Frank Mertens
 *
 * See ../COPYING for the license.
 */

#include <sys/mman.h>
#include <unistd.h>
#include <new>
#include "debug.hpp"
#include "types.hpp"
#include "Mutex.hpp"
#include "Allocator.hpp"

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

namespace ftl
{

#define WORD_ALIGN(x) (((x) / sizeof(int) + ((x) % sizeof(int) != 0)) * sizeof(int))

void* Allocator::operator new(size_t size)
{
	long pageSize = ::sysconf(_SC_PAGE_SIZE);
	check(pageSize > 0);
	check(size <= (unsigned long)pageSize);
	void* data = ::mmap(0, ::sysconf(_SC_PAGE_SIZE), PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	check(data != MAP_FAILED);
	return data;
}

void Allocator::operator delete(void* data, size_t size)
{
	check(::munmap(data, ::sysconf(_SC_PAGE_SIZE)) == 0);
}

struct Allocator::BucketHeader
{
	Mutex mutex_;
	uint32_t bytesDirty_;
	uint32_t objectCount_;
	bool open_;
};

Allocator::Allocator()
	: pageSize_(::sysconf(_SC_PAGE_SIZE)),
	  bucket_(0)
{}

void* Allocator::allocate(size_t size)
{
	Ref<Allocator> allocator = instance();
	BucketHeader* bucket = allocator->bucket_;
	size_t pageSize = allocator->pageSize_;
	
	size = WORD_ALIGN(size);
	if (!bucket) {
		if (size > pageSize - WORD_ALIGN(sizeof(BucketHeader))) {
			size += sizeof(uint32_t);
			uint32_t pageCount = size / pageSize + ((size % pageSize) > 0);
			void* pageStart = ::mmap(0, pageCount * pageSize, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
			check(pageStart != MAP_FAILED);
			*(uint32_t*)pageStart = pageCount;
			return (void*)((uint32_t*)pageStart + 1);
		}
		else {
			void* pageStart = ::mmap(0, pageSize, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
			check(pageStart != MAP_FAILED);
			bucket = new(pageStart)BucketHeader;
			bucket->bytesDirty_ = WORD_ALIGN(sizeof(BucketHeader)) + size;
			bucket->objectCount_ = 1;
			bucket->open_ = true;
			allocator->bucket_ = bucket;
			return (void*)((char*)pageStart + WORD_ALIGN(sizeof(BucketHeader)));
		}
	}
	else {
		bucket->mutex_.acquire();
		if (size <= pageSize - bucket->bytesDirty_) {
			void* data = (void*)(((char*)bucket) + bucket->bytesDirty_);
			bucket->bytesDirty_ += size;
			++bucket->objectCount_;
			bucket->mutex_.release();
			return data;
		}
		else {
			bucket->open_ = false;
			bucket->mutex_.release();
			allocator->bucket_ = 0;
			return allocate(size);
		}
	}
}

void Allocator::free(void* data)
{
	Ref<Allocator> allocator = instance();
	size_t pageSize = allocator ? allocator->pageSize_ : size_t(::sysconf(_SC_PAGE_SIZE));
	
	uint32_t offset = ((char*)data - (char*)0) % pageSize;
	if (offset == sizeof(uint32_t)) {
		void* pageStart = (void*)((char*)data - sizeof(uint32_t));
		uint32_t pageCount = *(uint32_t*)pageStart;
		check(::munmap(pageStart, pageCount * pageSize) == 0);
	}
	else {
		BucketHeader* bucket = (BucketHeader*)((char*)data - offset);
		bucket->mutex_.acquire();
		bool dispose = ((--bucket->objectCount_) == 0) && (!bucket->open_);
		bucket->mutex_.release();
		if (dispose) {
			bucket->~BucketHeader();
			check(::munmap((void*)((char*)data - offset), pageSize) == 0);
		}
	}
}

} // namespace ftl
