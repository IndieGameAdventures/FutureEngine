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
*	Implementation of FutureStackAllocator
*/

#include <future/core/debug/debug.h>
#include <future/core/memory/allocators/stackallocator.h>
#include <future/core/memory/memory.h>
#include <future/core/memory/tracker/memorytracker.h>
#include <new>

/*******************************************************************/
// Stack Allocator

FutureStackAllocator::FutureStackAllocator(u8 align, u32 stackSize, bool usingHeaders)
	: m_align(align),
	  m_stackSize(stackSize),
	  m_stacks(NULL),
	  m_usingHeaders(usingHeaders)
{
	FUTURE_ASSERT(m_stackSize > 0);
	
	// round to nearest multiple of align
	if(align > 0)
	{
		if(!m_usingHeaders)
		{
			m_stackSize += align;
		}
		u32 r = m_stackSize % m_align;
		if(r != 0)
		{
			m_stackSize = m_stackSize + m_align - r;
		}
	}

	m_poolAllocator = new FuturePoolAllocator(4, sizeof(Block), 1024 * 64, false);
	AddStack();
}

void * FutureStackAllocator::Alloc(u32 bytes)
{
	if(!m_usingHeaders)
	{
		bytes += 4;
	}
	FUTURE_ASSERT_CRIT(bytes <= m_stackSize, 9875);
	// keep the heap aligned	
	u32 r = bytes % m_align;
	if(r != 0)
	{
		bytes = bytes + m_align - r;
	}

	m_criticalSection.Lock();

	Stack * stack = m_stacks;

	if((m_stackSize - ((u32)stack->m_position - (u32)stack->m_data)) < bytes)
	{
		FUTURE_LOG_INFO(L"Stack is full, expanding");
		AddStack();
		stack = m_stacks;
	}

	FUTURE_ASSERT(stack && (m_stackSize - ((u32)stack->m_position - (u32)stack->m_data)) >= bytes);

	void * data = stack->m_position;
	stack->m_position = (void*)((u32)stack->m_position + bytes);
	Block * block = (Block*)m_poolAllocator->Alloc(sizeof(Block));
	block->m_size = bytes;
	block->m_next = stack->m_blocks;
	stack->m_blocks = block;

	m_criticalSection.Unlock();

	if(m_usingHeaders)
	{
		FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(data);
		header->m_allocatorData = (u32)block;
		return data;
	}
	else
	{
		u32 * header = (u32*)data;
		*header = (u32)block;
		return (void*)(header + 1);
	}
}

void FutureStackAllocator::Free(void * p)
{
	Block * block;
	if(m_usingHeaders)
	{
		FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(p);
		block = (Block*)header->m_allocatorData;
	}
	else
	{
		u32 * header = ((u32*)p) - 1;
		block = (Block*)(*header);
		p = (void*)header;
	}

	FUTURE_ASSERT(block);

	if(m_stacks->m_blocks == NULL)
	{
		FUTURE_ASSERT(m_stacks->m_data == m_stacks->m_position);
		m_criticalSection.Lock();
		Stack * stack = m_stacks;
		if(stack->m_data)
		{
			if(!m_usingHeaders && m_align >= 4)
			{
				stack->m_data = (void*)((u32)stack->m_data - (m_align - 4));
			}
			_aligned_free(stack->m_data);
		}
		m_stacks = stack->m_next;
		delete stack;
		m_criticalSection.Unlock();
	}

	FUTURE_ASSERT_MSG(m_stacks->m_blocks == block, L"Freeing stack in the wrong order.");

	m_criticalSection.Lock();
	Stack * stack = m_stacks;

	stack->m_position = (void *)((u32)stack->m_position - block->m_size);
	stack->m_blocks = block->m_next;
	m_poolAllocator->Free(block);
	
	m_criticalSection.Unlock();
}

u8 FutureStackAllocator::Priority()
{
	return 255;
}

bool FutureStackAllocator::ShouldAllocate(FutureMemoryParam memParam)
{
	return false;
}

void FutureStackAllocator::Release()
{
	for(Stack * stack = m_stacks; stack; )
	{
		for(Block * block = stack->m_blocks; block;)
		{
			Block * nextBlock = block->m_next;
			m_poolAllocator->Free(block);
			block = nextBlock;
		}
		if(stack->m_data)
		{
			if(!m_usingHeaders && m_align >= 4)
			{
				stack->m_data = (void*)((u32)stack->m_data - (m_align - 4));
			}
			_aligned_free(stack->m_data);
		}
		Stack * next = stack->m_next;
		delete stack;
		stack = next;
	}
	m_stacks = NULL;
	m_poolAllocator->Release();
	delete m_poolAllocator;
	m_poolAllocator = NULL;
}

void FutureStackAllocator::AddStack()
{
	Stack * stack = new Stack();
	stack->m_data = _aligned_malloc(m_stackSize + sizeof(Stack), m_align);
	stack->m_next = m_stacks;
	m_stacks = stack;
	stack->m_blocks = NULL;

	if(!m_usingHeaders && m_align >= 4)
	{
		stack->m_data = (void*)((u32)stack->m_data + (m_align - 4));
	}
	stack->m_position = stack->m_data;
}