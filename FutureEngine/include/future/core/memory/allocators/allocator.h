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

#ifndef FUTURE_CORE_MEMORY_ALLOCATOR_H
#define FUTURE_CORE_MEMORY_ALLOCATOR_H

#include <future/core/type/type.h>

#include <stdlib.h>
#include <malloc.h>

#if FUTURE_PLATFORM_LINUX || FUTURE_PLATFORM_ANDROID
#	define _aligned_malloc(bytes, align)	memalign(align, bytes)
#	define _aligned_free(data)				free(data)
#elif FUTURE_PLATFORM_OSX || FUTURE_PLATFORM_IOS
    // Mac is already 16 bit aligned so we don't need to change it
#	define _aligned_malloc(bytes, align)	(align <= 16 ? malloc(bytes) : NULL)
#	define _aligned_free(data)				free(data)
#endif

// Forward Declares
struct FutureMemoryParam;

/*!
 *	\brief		Interface containing function declarations for memory allocation.
 *
 *	\details 	Classes implementing this class are used to allocate memory by the FutureMemory system.
 *				Allocators are added to the memory system and are a ssigned a location in the allocator
 *				list based on thier priority. Allocators with a lower priority will be checked first.
 *				ShouldAllocate is called on each allocator until one returns true. That allocator is then
 *				requested to allocate the needed memory block. If using an allocator seperately from the
 *				memory system (not recommended), be sure to call ShouldAllocate before calling Alloc to
 *				make sure that the allocator can handle the request.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */
class IFutureAllocator
{
public:
	//! Deconstructs this FutureAllocator, releasing all resources
    virtual ~IFutureAllocator(){};
    
    /*	\brief		Allocates a block of memory that is at least bytes large
     *	\details	Each allocator will implement this function differently depending on the type of allocator, 
     *				but all allocators will follow a similar pattern. First make sure they can handle the request,
     *				Then find an memory block big enough to hold the requested number of bytes, then return the 
     *				address of that block. There is no gaurentee that the block will be exactly bytes large, it
     *				might be twice that size. Even if it is larger, only the requested number of bytes should be
     *				used, just in case.
     *	\param[in]	bytes	The size, in bytes, of the requested block of memory
     *	\return		A pointer to the beginning of the requested memory block or NULL is one could not be found.
     */
	virtual void *	Alloc(u32 bytes) = 0;
    /*	\brief		Frees the previously allocator block
     *	\details	This function requires that the memory be allocator using this allocator. If the provided
     *				pointer references a block of memory that was allocated by this allocator, an assert will
     *				fire. After freeing a block, be sure to remove all pointers to that memory as it will be
     *				recycled and used to handle another Alloc request. Keeping pointers to freed memory is a
     *				really good way to cause memory corruption and destroy a lot of things.
     *	\param[in]	p	A pointer to the beginning of a memory block that was allocated by this allocator
     */
	virtual void	Free(void * p) = 0;

	//! Gets the priority of this allocator, used to determine which allocator should handle an allocation request
	virtual u8		Priority() = 0;
	//! Determines if this allocator can and should allocate the memory requested in the memParam
	//! \param[in] memParam	The FutureMemoryParam for the requested allocation
	virtual bool	ShouldAllocate(FutureMemoryParam memParam) = 0;
};

#endif