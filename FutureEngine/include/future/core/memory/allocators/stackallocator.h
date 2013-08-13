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
*	A standard stack allocator. Pushes new allocations onto a stack for quick allocation
*	and deallocation. Only downside is allocations must be freed is the opposite order they
*	were allocated in. This allocator will only be used if specifically requested as objects
*	must be handled very carefully when using this.
*/


#ifndef FUTURE_CORE_MEMORY_ALLOCATOR_STACK_H
#define FUTURE_CORE_MEMORY_ALLOCATOR_STACK_H

#include <future/core/memory/allocators/allocator.h>
#include <future/core/memory/allocators/poolallocator.h>
#include <future/core/objects/threadsafeobject.h>

struct FutureMemoryParam;
class FuturePoolAllocator;

class FutureStackAllocator : public IFutureAllocator, public FutureThreadSafeObject
{
public:
	FutureStackAllocator(u32 stackSize = 1024 * 1024, bool usingHeaders = true);

	virtual void *	Alloc(u32 bytes);
	virtual void	Free(void * p);

	// highest priority, always returns false.
	virtual u8		Priority();
	virtual bool	ShouldAllocate(FutureMemoryParam memParam);

private:

	struct Block
	{
		Block * m_next;
		u32		m_size;
	};

	struct Stack
	{
		Stack *	m_next;
		Block * m_blocks;

		void *	m_position;
		void *	m_data;
	};

	u32		m_stackSize;
	Stack *	m_stacks;
	bool	m_usingHeaders;

	FuturePoolAllocator * m_poolAllocator;

	void	AddStack();
};

#endif