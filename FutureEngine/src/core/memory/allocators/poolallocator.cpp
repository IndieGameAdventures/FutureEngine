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
*	Implementation of FuturePoolAllocator
*/

#include <future/core/debug/debug.h>
#include <future/core/memory/allocators/poolallocator.h>
#include <future/core/memory/memory.h>
#include <future/core/memory/tracker/memorytracker.h>
#include <new>

#ifndef FUTURE_POOL_GROUP_SIZE
#	define FUTURE_POOL_GROUP_SIZE	1024
#endif

/*******************************************************************/
// Pool Allocator

FuturePoolAllocator::FuturePoolAllocator(u8 align, u8 poolSize, u32 numPools, bool accountForHeaders)
	: m_align(align),
	  m_poolSize(align),
	  m_freeList(NULL),
	  m_pools(0),
	  m_groupList(NULL),
	  m_usingHeaders(accountForHeaders)
{
	FUTURE_ASSERT(poolSize > 0 && numPools > 0);
	
	while(m_poolSize < poolSize + (accountForHeaders ? FutureMemory::HeaderSize() : 4))
	{
		m_poolSize += align;
	};

	while(m_pools < numPools)
	{
		AddPoolGroup();
	}
}

void * FuturePoolAllocator::Alloc(u32 bytes)
{
	FUTURE_ASSERT_CRIT(bytes <= m_poolSize, 9865);

	m_criticalSection.Lock();

	if(m_freeList == NULL)
	{
		FUTURE_LOG_INFO(L"Pool Allocator is full, expanding");
		AddPoolGroup();
	}
	FUTURE_ASSERT_CRIT(m_freeList != NULL, 9864);


	Pool * pool = m_freeList;
	m_freeList = m_freeList->m_next;
	
	m_criticalSection.Unlock();

	if(m_usingHeaders)
	{
		FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(pool->m_data);
		header->m_allocatorData = (u32)pool;
		return pool->m_data;
	}
	else
	{
		u32 * header = (u32*)pool->m_data;
		*header = (u32)pool;
		return (void*)(header + 1);
	}
}

void FuturePoolAllocator::Free(void * p)
{
	Pool * pool;
	if(m_usingHeaders)
	{
		FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(p);
		pool = (Pool*)header->m_allocatorData;
	}
	else
	{
		u32 * header = ((u32*)p) - 1;
		pool = (Pool*)(*header);
		p = (void*)header;
	}

	FUTURE_ASSERT(pool->m_data == p);

	m_criticalSection.Lock();

	if(m_freeList == NULL)
	{
		m_freeList = pool;
	}
	else
	{
		pool->m_next = m_freeList;
		m_freeList = pool;
	}

	m_criticalSection.Unlock();
}

// set to 100 + the pool size, this way smaller pool sizes are checked first
u8 FuturePoolAllocator::Priority()
{
	return 100 + (m_poolSize / 8);
}

// Make sure we have room to spare, if we do and the requested bytes is the right size, return true
bool FuturePoolAllocator::ShouldAllocate(FutureMemoryParam memParam)
{
	if(memParam.m_bytes + (m_usingHeaders ? FutureMemory::HeaderSize() : 4) < m_poolSize)
	{
		return true;
	}
	return false;
}

void FuturePoolAllocator::Release()
{
	for(Pool * group = m_groupList; group; )
	{
		if(group->m_data)
		{
			if(((Pool*)(group->m_data))->m_data)
			{
				_aligned_free(((Pool*)(group->m_data))->m_data);
			}
			_aligned_free(group->m_data);
		}
		Pool * next = group->m_next;
		delete group;
		group = next;
	}
	m_groupList = NULL;
	m_freeList = NULL;
	m_pools = 0;
}

void FuturePoolAllocator::AddPoolGroup()
{
	Pool * pools = (Pool*)_aligned_malloc((sizeof(Pool) * FUTURE_POOL_GROUP_SIZE), m_align);
	void * data = _aligned_malloc(m_poolSize * FUTURE_POOL_GROUP_SIZE, m_align);

	Pool * group = new Pool();
	group->m_data = pools;
	group->m_next = m_groupList;
	if(m_groupList == NULL)
	{
		m_groupList = group;
	}

	for(u16 i = 0; i < FUTURE_POOL_GROUP_SIZE && pools != NULL; ++i)
	{
		pools->m_next = (i < FUTURE_POOL_GROUP_SIZE - 1 ? pools + 1 : m_freeList);
		pools->m_data = data;
		++pools;
		data = (void*)((u32)data + m_poolSize);
	}
	m_freeList = (Pool*)(group->m_data);
	m_pools += FUTURE_POOL_GROUP_SIZE;
}