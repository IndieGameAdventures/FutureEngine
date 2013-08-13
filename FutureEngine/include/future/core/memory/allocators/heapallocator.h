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

#ifndef FUTURE_CORE_MEMORY_ALLOCATOR_HEAP_H
#define FUTURE_CORE_MEMORY_ALLOCATOR_HEAP_H

#include <future/core/type/type.h>
#include <future/core/memory/allocators/allocator.h>
#include <future/core/object/threadsafeobject.h>

struct FutureMemoryParam;
class FuturePoolAllocator;

/*!
 *	\brief		A standard heap allocator
 *
 *	\details 	This alloctor first requests a large chunk of data from the operating system then hands out variable
 *				sized blocks upon request. Requested block sizes must be less than the heap size or the allocation will
 *				fail. The allcoator will automatically request additional heaps from the operation system if a request
 *				is made that is smaller than the heap size but there are no free blocks large enough to accomidate the
 *				request. It is recommended that the initial heap size be large enough to handle all requests made during
 *				the entire game. Expanding the heap is expensive and often not needed. The default heap size is 10mb, 
 *				large enough to handle most requests. Some platforms (phones) may need to lower the heap size to handle 
 *				device memory limits.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */
class FutureHeapAllocator : public IFutureAllocator, public FutureThreadSafeObject
{
public:
	/*	\brief	FutureHeapAllocator Constructor
	 *	\param	heapSize	The size of each heap this allocator uses, defaulted to 10mb
	 *	\param	usingHeaders	True if this allocator will be used by the memory system and false if it will not
	 */
	FutureHeapAllocator(u32 heapSize = 1024 * 1024 * 10, bool usingHeaders = true);

	//! FutureHeapAllocator Destructor
	virtual ~FutureHeapAllocator();

	//! Returns a pointer to a 16 bit aligned block of memory that is at least bytes large
	virtual void *	Alloc(u32 bytes);
	//! Frees the block at p so it cna used for future allocations
	virtual void	Free(void * p);

	//! The priority when used with the memory system. This will always return 200, the last step before the malloc allocator
	virtual u8		Priority();
	//! Returns true for any allocation that is less than 1/4 of the heap size
	virtual bool	ShouldAllocate(FutureMemoryParam memParam);

private:

	//! Stucture used to keep track of free blocks within a heap in a linked list style
	struct Block
	{
		Block * m_next;	//! A pointer to the next free block
		void *	m_data; //! A pointer to the heap data contained in this block
		u32		m_size;	//! The size, in bytes, of this block
	};

	//! Structure used to keep track of all heaps in a linked list style
	struct Heap
	{
		Heap *	m_next;			//! A pointer to the next heap in the list
		Block * m_freeBlocks;	//! A linked list of free bmemory blocks within this heap
		void *	m_data;			//!	A pointer to the memory chunk allodated by this heap, used to ensure the heap is freed properly
	};

	u32		m_heapSize;			//! The size of each heap
	Heap *	m_heaps;			//! A linked list of the heaps contained in this allocator
	bool	m_usingHeaders;		//! True if the requested memory contains space for a FutureMemoryHeader and false if the heap should add it's own header

	FuturePoolAllocator * m_poolAllocator;		//! A pool allocator used to quickly allocator Block and Heap structures

	//! Allocates a new heap and sets it up to handle new allocations
	void	AddHeap();
};

#endif