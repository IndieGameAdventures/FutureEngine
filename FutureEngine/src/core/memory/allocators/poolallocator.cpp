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


/*
*	Implementation of FuturePoolAllocator
*/

#include <future/core/debug/debug.h>
#include <future/core/memory/allocators/poolallocator.h>
#include <future/core/memory/memory.h>
#include <future/core/memory/tracker/memorytracker.h>
#include <new>

#ifndef FUTURE_MAX_POOL_GROUP_SIZE
#	define FUTURE_MAX_POOL_GROUP_SIZE	1024
#endif

/*******************************************************************/
// Pool Allocator

FuturePoolAllocator::FuturePoolAllocator(u8 blockSize, u32 numBlocks, bool accountForHeaders)
	: m_blockSize(16),
	  m_freeList(NULL),
	  m_blocks(0),
	  m_poolList(NULL),
	  m_usingHeaders(accountForHeaders),
	  m_poolSize(numBlocks)
{
	FUTURE_ASSERT(blockSize > 0 && numPools > 0);
	
	blockSize += (accountForHeaders ? FutureMemory::HeaderSize() : sizeof(size_t));

	u32 r = blockSize % 16;
	if(r != 0)
	{
		blockSize = blockSize + 16 - r;
	}

	if(m_poolSize > FUTURE_MAX_POOL_GROUP_SIZE)
	{
		m_poolSize = FUTURE_MAX_POOL_GROUP_SIZE;
	}

	while(m_blocks < numBlocks)
	{
		AddPool();
	}
}

FuturePoolAllocator::~FuturePoolAllocator()
{
	for(Block * pool = m_poolList; pool;)
	{
		if(pool->m_data)
		{
			if(((Block*)(pool->m_data))->m_data)
			{
				if(m_usingHeaders)
				{
					_aligned_free(((Block*)(pool->m_data))->m_data);
				}
				else
				{
					void * data = ((Block*)(pool->m_data))->m_data;
					data = (void*)(((size_t*)data) - 1);
					_aligned_free(data);
				}
			}
			_aligned_free(pool->m_data);
		}
		Block * next = pool->m_next;
		delete pool;
		pool = next;
	}
	m_groupList = NULL;
	m_freeList = NULL;
	m_pools = 0;
	Unlock();
}

void * FuturePoolAllocator::Alloc(u32 bytes)
{
	FUTURE_ASSERT_CRIT(bytes <= m_blockSize, 9865);


	if(m_freeList == NULL)
	{
		FUTURE_LOG_WARNING("Pool Allocator is full, expanding");
		AddPool();
	}
	FUTURE_ASSERT_CRIT(m_freeList != NULL, 9864);

	Lock();

	Block * block = m_freeList;
	m_freeList = m_freeList->m_next;
	
	Unlock();

	return block->m_data;
}

void FuturePoolAllocator::Free(void * p)
{
	Block * block;
	if(m_usingHeaders)
	{
		FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(p);
		block = (Block*)header->m_allocatorData;
	}
	else
	{
		size_t * header = ((size_t*)p) - 1;
		block = (Block*)(*header);
	}

	FUTURE_ASSERT(pool->m_data == p);

	Lock();

	if(m_freeList == NULL)
	{
		m_freeList = block;
	}
	else
	{
		block->m_next = m_freeList;
		m_freeList = block;
	}

	Unlock();
}

// set to 100 + the block size, this way smaller block sizes are checked first
u8 FuturePoolAllocator::Priority()
{
	return 100 + (m_blockSize / 8);
}

// Make sure we have room to spare, if we do and the requested bytes is the right size, return true
bool FuturePoolAllocator::ShouldAllocate(FutureMemoryParam memParam)
{
	if(memParam.m_bytes + (m_usingHeaders ? FutureMemory::HeaderSize() : sizeof(size_t)) <= m_blockSize)
	{
		return true;
	}
	return false;
}


void FuturePoolAllocator::AddPool()
{
	Block * pools = (Block*)_aligned_malloc((sizeof(Block) * m_poolSize), 16);
	void * data = _aligned_malloc(m_blockSize * m_poolSize, 16);

	Block * group = new Block();
	group->m_data = pools;
	group->m_next = m_poolList;
	if(m_poolList == NULL)
	{
		m_poolList = group;
	}

	for(u32 i = 0; i < m_poolSize && pools != NULL; ++i)
	{
		pools->m_next = (i < m_poolSize - 1 ? pools + 1 : m_freeList);
		if(m_usingHeaders)
		{
			FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(data);
			header->m_allocatorData = (size_t)pools;
			pools->m_data = data;
		}
		else
		{
			size_t * header = (size_t*)data;
			*header = (size_t)pools;
			pools->m_data = (void*)(header + 1);
		}
		++pools;
		data = (void*)((u8*)data + m_blockSize);
	}

	Lock();

	m_freeList = (Pool*)(Block->m_data);
	m_pools += m_poolSize;

	Unlock();
}