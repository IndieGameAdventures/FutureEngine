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
*	Pool allocator allocates blocks that are a set size. The block size is
*	variable to allow multiple pool allocators of different sizes.
*/


#ifndef FUTURE_CORE_MEMORY_ALLOCATOR_POOL_H
#define FUTURE_CORE_MEMORY_ALLOCATOR_POOL_H

#include <future/core/memory/allocators/allocator.h>
#include <future/core/object/threadsafeobject.h>

struct FutureMemoryParam;

class FuturePoolAllocator : public IFutureAllocator, public FutureThreadSafeObject
{
public:
	FuturePoolAllocator(u8 align, u8 poolSize, u32 startingPools = 4096, bool accountForHeaders = true);

	virtual void *	Alloc(u32 bytes);
	virtual void	Free(void * p);

	virtual u8		Priority();
	virtual bool	ShouldAllocate(FutureMemoryParam memParam);

	virtual void	Release();

private:

	struct Pool
	{
		Pool * m_next;
		void * m_data;
	};

	Pool *	m_freeList;

	u32		m_pools;
	u32		m_poolSize;
	u16		m_groupSize;
	u8		m_align;
	bool	m_usingHeaders;

	Pool *	m_groupList;

	void	AddPoolGroup();
};

#endif