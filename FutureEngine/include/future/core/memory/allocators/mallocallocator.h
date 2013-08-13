/*
 *	Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */


#ifndef FUTURE_CORE_MEMORY_ALLOCATOR_MALLOC_H
#define FUTURE_CORE_MEMORY_ALLOCATOR_MALLOC_H

#include <future/core/memory/allocators/allocator.h>

/*!
 *	\brief		The most basic of allocators that simply passes all requests to the operating system
 *
 *	\details 	Malloc Allocator uses aligned_malloc and aligned_free and get memory chunks from the operating
 *				system. This is the base for all other allocators as they will use a Malloc Allocator to get
 *				the memory chunks that they split up and distribute as needed. All memory returned from this
 *				allocator is gaurenteed to be 16 bit or higher aligned. This allows the other allocators to
 *				run slighlty faster by not needing to ensure memory alignment. All allocations are rounded
 *				to the next highest multiple of 16 before being passed to the operating system.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */
class FutureMallocAllocator : public IFutureAllocator
{
public:	

	//! FutureMallocAllocator Constructor
	FutureMallocAllocator();

	//! FutureMallocAllocator Destructor
	virtual ~FutureMallocAllocator();

	//! Returns a 16 bit sligned memory block by passing the request to the operating system
	virtual void *	Alloc(u32 bytes);
	//! Takes a block of memory allocated by this allocator and requests that the OS free that memory block
	virtual void	Free(void * p);

	//! Gets the priority of this allocator, FutureMallocAllocator always returns 255, the last possible allocator
	virtual u8		Priority() = 0;
	
	//! Always returns true
	virtual bool	ShouldAllocate(FutureMemoryParam memParam) = 0;

};

#endif