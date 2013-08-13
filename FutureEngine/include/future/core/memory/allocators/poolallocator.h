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


#ifndef FUTURE_CORE_MEMORY_ALLOCATOR_POOL_H
#define FUTURE_CORE_MEMORY_ALLOCATOR_POOL_H

#include <future/core/memory/allocators/allocator.h>
#include <future/core/object/threadsafeobject.h>

struct FutureMemoryParam;

/*!
 *	\brief		A Pool or FreeList allocator
 *
 *	\details 	This is a very fast allocator that does not suffer from fragmenting. The only issue is that
 *				all allocations must be exactly the same size. The pool allocator creates a list of blocks
 *				that are all exactly the same size. When a request is made, the allocator simply pops the
 *				head of the free list and returns it. When a block is freed, the blocks is placed back on
 *				top of list to be used by the next allocation request. Very fast and very efficient. If
 *				a request is made for a block that is smaller than the block size, an entire block is
 *				returned. This can cause a lot of memory waste if done carelessly. If the pool allocator
 *				runs out of free blocks, it will automatically expand. This is expensive so the default
 *				starting blocks should be large enough to handle all requests.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */
class FuturePoolAllocator : public IFutureAllocator, public FutureThreadSafeObject
{
public:
	/*	\brief	FuturePoolAllocator Constructor
	 *	\param	poolSize	The size, in bytes, of each block
	 *	\param	startingBlocks	The number of blocks to allocate. Allocating additional blocks is expensive.
	 *	\param	usingHeaders	True if this allocator will be used by the memory system and false if it will not
	 */
	FuturePoolAllocator(u16 blockSize, u32 startingBlocks = 4096, bool accountForHeaders = true);
	//! FuturePoolAllocator Desctructor
	virtual ~FuturePoolAllocator();

	//! Returns a pointer to the next free block
	virtual void *	Alloc(u32 bytes);
	//! Added the used block back into the free block list
	virtual void	Free(void * p);

	//! The priority of this allocator, which is 100 + (blockSize / 16) so that smaller pools are checked first
	virtual u8		Priority();
	//! Returns true if the requested size is less than or equal to the block size
	virtual bool	ShouldAllocate(FutureMemoryParam memParam);

private:

	//! A block of memory 
	struct Block
	{
		Block * m_next;	//! A pointer to the next block of memory
		void * 	m_data;	//! The data contained within this block
	};

	Block *	m_freeList;	//! The list of the free memory blocks

	u32		m_blocks;		//! The total number of allocated blocks
	u32		m_blockSize;	//! The size of each memory block
	u16		m_poolSize;		//! The number of blocks in each pool
	bool	m_usingHeaders;	//! True if this allocator is being used by the memory system, false if it is not

	Block *	m_poolList;		//! A linked list of all active pools

	//! Allocates a new pool, splits it up into blocks, and adds the blocks to the free list
	void	AddPool();
};

#endif