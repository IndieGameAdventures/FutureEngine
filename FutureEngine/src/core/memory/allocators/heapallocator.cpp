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
*	Implementation of FutureHeapAllocator
*/

#include <future/core/debug/debug.h>
#include <future/core/memory/allocators/heapallocator.h>
#include <future/core/memory/memory.h>
#include <future/core/memory/tracker/memorytracker.h>

/*******************************************************************/
// Heap Allocator

FutureHeapAllocator::FutureHeapAllocator(u8 align, u32 heapSize, bool usingHeaders)
	: m_align(align),
	  m_heapSize(heapSize),
	  m_heaps(NULL),
	  m_usingHeaders(usingHeaders)
{
	FUTURE_ASSERT(m_heapSize > 0);
	
	// round to nearest multiple of align
	if(align > 0)
	{
		if(!m_usingHeaders)
		{
			m_heapSize += align;
		}
		u32 r = m_heapSize % m_align;
		if(r != 0)
		{
			m_heapSize = m_heapSize + m_align - r;
		}
	}

	m_poolAllocator = new FuturePoolAllocator(4, sizeof(Block), 1024, false);
	AddHeap();
}

void * FutureHeapAllocator::Alloc(u32 bytes)
{
	if(!m_usingHeaders)
	{
		bytes += 4;
	}
	FUTURE_ASSERT_CRIT(bytes <= m_heapSize, 9875);
	// keep the heap aligned	
	u32 r = bytes % m_align;
	if(r != 0)
	{
		bytes = bytes + m_align - r;
	}

	Block * block = NULL;
	Block * blockPrev = NULL;
	Heap * heap = NULL;
	u32 dif = m_heapSize;

	m_criticalSection.Lock();

	// Loop through all current blocks and find the smallest block with enough room
	// for our object
	for(heap = m_heaps; heap; heap = heap->m_next)
	{
		blockPrev = NULL;
		Block * last = NULL;
		for(Block * checkBlock = heap->m_freeBlocks; checkBlock; checkBlock = checkBlock->m_next)
		{
			if(checkBlock->m_size >= bytes)
			{
				u32 d = checkBlock->m_size - bytes;
				if(d < dif)
				{
					block = checkBlock;
					blockPrev = last;
					dif = d;
					if(dif == 0)
					{
						break;
					}
				}
			}
			last = block;
		}
		if(block)
		{
			break;
		}
	}

	if(!heap || !block)
	{
		FUTURE_LOG_INFO(L"Heap is full, expanding");
		AddHeap();
		heap = m_heaps;
		block = heap->m_freeBlocks;
		blockPrev = NULL;
	}

	FUTURE_ASSERT(heap && block && block->m_size >= bytes);

	void * data = block->m_data;
	
	if(block->m_size == bytes)
	{
		if(blockPrev)
		{
			blockPrev->m_next = block->m_next;
		}
		if(block == heap->m_freeBlocks)
		{
			heap->m_freeBlocks = heap->m_freeBlocks->m_next;
		}
		m_poolAllocator->Free(block);
	}
	else
	{
		block->m_size -= bytes;
		block->m_data = (void*)((u32)block->m_data + bytes);
	}

	m_criticalSection.Unlock();

	
	if(m_usingHeaders)
	{
		FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(data);
		header->m_allocatorData = bytes;
		return data;
	}
	else
	{
		u32 * header = (u32*)data;
		*header = bytes;
		return (void*)(header + 1);
	}
}

void FutureHeapAllocator::Free(void * p)
{
	m_criticalSection.Lock();
	Heap * heap = m_heaps;
	for( ;heap; heap = heap->m_next)
	{
		if((u32)p >= (u32)heap->m_data && (u32)p < (u32)heap->m_data + m_heapSize)
		{
			break;
		}
	}
	FUTURE_ASSERT_MSG(heap, L"Attempting to free a block that does not belong to this heap");
	
	u32 size = 0;
	if(m_usingHeaders)
	{
		FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(p);
		size = header->m_allocatorData;
	}
	else
	{
		u32 * header = ((u32*)p) - 1;
		size = *header;
		p = (void*)header;
	}
	FUTURE_ASSERT(size > 0 && size <= m_heapSize);

	bool found = false;
	if(heap->m_freeBlocks != NULL)
	{
		// check to see if this block is next to another block
		for(Block * checkBlock = heap->m_freeBlocks; checkBlock && !found; checkBlock = checkBlock->m_next)
		{
			// checkBlock is before this one
			if((u32)checkBlock->m_data + checkBlock->m_size == (u32)p)
			{
				checkBlock->m_size += size;
				found = true;
			}
			// checkBlock is directly after this block
			else if((u32)p + size == (u32)checkBlock->m_data)
			{
				checkBlock->m_size += size;
				checkBlock->m_data = p;
				found = true;
			}
		}
	}

	if(!found)
	{
		// we couldn't add this to another block so make a new one
		Block * block = (Block*)m_poolAllocator->Alloc(sizeof(Block));
		block->m_data = p;
		block->m_size = size;
		block->m_next = heap->m_freeBlocks;
		heap->m_freeBlocks = block;
	}
	
	m_criticalSection.Unlock();
}

u8 FutureHeapAllocator::Priority()
{
	return 200;
}

bool FutureHeapAllocator::ShouldAllocate(FutureMemoryParam memParam)
{
	return (memParam.m_bytes + FutureMemory::HeaderSize() < m_heapSize / 4);
}

void FutureHeapAllocator::Release()
{
	for(Heap * heap = m_heaps; heap; )
	{
		for(Block * block = heap->m_freeBlocks; block;)
		{
			Block * nextBlock = block->m_next;
			m_poolAllocator->Free(block);
			block = nextBlock;
		}
		if(heap->m_data)
		{
			if(!m_usingHeaders && m_align >= 4)
			{
				heap->m_data = (void*)((u32)heap->m_data - (m_align - 4));
			}
			_aligned_free(heap->m_data);
		}
		Heap * next = heap->m_next;
		m_poolAllocator->Free(heap);
		heap = next;
	}
	m_heaps = NULL;
	m_poolAllocator->Release();
	delete m_poolAllocator;
	m_poolAllocator = NULL;
}

void FutureHeapAllocator::AddHeap()
{
	Heap * heap = (Heap*)m_poolAllocator->Alloc(sizeof(Heap));
	heap->m_data = _aligned_malloc(m_heapSize, m_align);
	heap->m_next = m_heaps;
	m_heaps = heap;

	if(!m_usingHeaders && m_align >= 4)
	{
		heap->m_data = (void*)((u32)heap->m_data + (m_align - 4));
	}

	Block * block = (Block*)m_poolAllocator->Alloc(sizeof(Block));
	block->m_data = heap->m_data;
	block->m_next = NULL;
	block->m_size = m_heapSize;
	heap->m_freeBlocks = block;
}