/*!
*	Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
*
*	Thank you for taking a look at my code. If you like it, please click
*	the donation button at the bottom of the sidebar on my blog. Thanks!
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

/*
*	A standard heap allocator. Eventually, this will be expanded to only accept smart pointers
*	so the heap can defragment when needed.
*/


#ifndef FUTURE_CORE_MEMORY_ALLOCATOR_HEAP_H
#define FUTURE_CORE_MEMORY_ALLOCATOR_HEAP_H

#include <future/core/type/type.h>
#include <future/core/memory/allocators/allocator.h>
#include <future/core/memory/allocators/poolallocator.h>
#include <future/core/thread/criticalsection/criticalsection.h>

struct FutureMemoryParam;

class FutureHeapAllocator : public IFutureAllocator
{
public:
	FutureHeapAllocator(u8 align, u32 heapSize = 1024 * 1024, bool usingHeaders = true);
	virtual void *	Alloc(u32 bytes);
	virtual void	Free(void * p);

	// This should sit in near the bottom, at 200, 
	// before malloc but after everything else
	virtual u8		Priority();
	virtual bool	ShouldAllocate(FutureMemoryParam memParam);

	virtual void	Release();

private:

	struct Block
	{
		Block * m_next;
		void *	m_data;
		u32		m_size;
	};

	struct Heap
	{
		Heap *	m_next;
		Block * m_freeBlocks;
		void *	m_data;
	};

	u32		m_heapSize;
	u8		m_align;
	Heap *	m_heaps;
	bool	m_usingHeaders;

	FuturePoolAllocator * m_poolAllocator;
	FutureCriticalSection m_criticalSection;

	void	AddHeap();
};

#endif