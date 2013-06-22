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
*	Implementation of FutureMemory
*/

#include <future/core/debug/debug.h>

#include <future/core/memory/memory.h>

#include <future/core/thread/criticalsection/criticalsection.h>
#include <future/core/memory/allocators/allocator.h>
#include <future/core/memory/allocators/mallocallocator.h>
#include <future/core/memory/allocators/heapallocator.h>
#include <future/core/memory/allocators/poolallocator.h>
#include <future/core/memory/memorystatistics.h>
#include <future/core/memory/tracker/memorytracker.h>
#include <future/core/utils/timer/timer.h>

//#include <stdlib.h>
//#include <assert.h>
//#include <new>
//#include <string>

/*******************************************************************/
// Structure to keep track of memory allocators
struct AllocatorList
{
	IFutureAllocator *	m_allocator;
	AllocatorList *		m_next;
};

	
/*******************************************************************/
// Memory System
class MemorySystem
{
public:
	MemorySystem();
	~MemorySystem();

	void *					Alloc(FutureMemoryParam memParam);
	void					Free(void * p );
	void *					ReAlloc(void * p, FutureMemoryParam memParam);

	u32						BytesForAllocation(FutureMemoryParam memParam);
	void					AddAllocator(IFutureAllocator * allocator);
	IFutureAllocator *		GetAllocator(int i);

	IFutureAllocator *		GetBestAllocator(FutureMemoryParam memParam);
	IFutureAllocator *		GetPreviousAllocator(void * p);
	
	FutureMemoryStatistics	GetStatistics();
	
	void					LogStatistics();
	void					LogAllocations();
	void					LogAllocation(void *);

	FutureCriticalSection	m_criticalsection;
	AllocatorList *			m_allocators;
	u8						m_globalAlign;
};

MemorySystem * memory;

/*******************************************************************/
// FutureMemory implementation

static u32 futureHeaderSize = 0;
void FutureMemory::CreateMemory(u8 globalAlign)
{
	FUTURE_ASSERT(memory == NULL);
	memory = new MemorySystem();
	memory->m_globalAlign = globalAlign;

	// make the header size a multiple of the global alignment for
	// easier and quicker allocations.
	futureHeaderSize = globalAlign;
	if(sizeof(FutureAllocHeader) > globalAlign)
	{
		while(futureHeaderSize < sizeof(FutureAllocHeader))
		{
			futureHeaderSize += globalAlign;
		}
	}
	((FutureMallocAllocator*)(memory->m_allocators->m_allocator))->SetAlign(globalAlign);
	FutureMemoryTracker::CreateInstance();

	memory->AddAllocator(new FuturePoolAllocator(globalAlign, 32, 1024));
	memory->AddAllocator(new FutureHeapAllocator(globalAlign));
}

void FutureMemory::DestroyMemory()
{
	FUTURE_ASSERT(memory != NULL);
	FutureMemoryTracker::DestroyInstance();
	delete memory;
	memory = NULL;
}

void * FutureMemory::Alloc(FutureMemoryParam memParam)
{
	return memory->Alloc(memParam);
}
void FutureMemory::Free(void * p)
{
	memory->Free(p);
}
void * FutureMemory::ReAlloc(void * p, FutureMemoryParam memParam)
{
	return memory->ReAlloc(p, memParam);
}
u32	FutureMemory::BytesForAllocation(FutureMemoryParam memParam)
{
	return memory->BytesForAllocation(memParam);
}
void FutureMemory::AddAllocator(IFutureAllocator * allocator)
{
	memory->AddAllocator(allocator);
}
IFutureAllocator * FutureMemory::GetAllocator(int i)
{
	return memory->GetAllocator(i);
}
FutureMemoryStatistics FutureMemory::GetStatistics()
{
	return memory->GetStatistics();
}
void FutureMemory::LogStatistics()
{
	return memory->LogStatistics();
}
void FutureMemory::LogAllocations()
{
	return memory->LogAllocations();
}
void FutureMemory::LogAllocation(void * p)
{
	return memory->LogAllocation(p);
}
u8 FutureMemory::GetGlobalAlignment()
{
	return memory->m_globalAlign;
}


inline u32 FutureMemory::HeaderSize()
{
	return futureHeaderSize; 
}

inline static void * DataFromHeader(FutureAllocHeader * header)
	{ return (void *)(reinterpret_cast< u32 >(header) + FutureMemory::HeaderSize()); }
inline static FutureAllocHeader * HeaderFromData(void * p)
	{ return reinterpret_cast<FutureAllocHeader *>(reinterpret_cast<u32>(p) - FutureMemory::HeaderSize()); }


/*******************************************************************/
// Memory System functions
void * MemorySystem::Alloc(FutureMemoryParam memParam)
{
	if(memParam.m_bytes <= 0)
	{
		return NULL;
	}
#if FUTURE_TRACK_MEMORY
	f32 time = FutureTimer::CurrentTime();
#endif
	IFutureAllocator * allocator = GetBestAllocator(memParam); // get the best allocator
	void * p = allocator->Alloc(BytesForAllocation(memParam)); // allocate enough bytes for the header
	FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(p);
	header->m_allocator = allocator;
#if FUTURE_TRACK_MEMORY
	FutureMemoryTracker::GetInstance()->Track(memParam, header, time);
#endif
	return DataFromHeader(header);
}

void MemorySystem::Free(void * p)
{
#if FUTURE_TRACK_MEMORY	
	FutureMemoryTracker::GetInstance()->Untrack(HeaderFromData(p));
#endif
	IFutureAllocator * allocator = GetPreviousAllocator(p);
	allocator->Free(HeaderFromData(p));
}

void * MemorySystem::ReAlloc(void * p, FutureMemoryParam memParam)
{
#if FUTURE_TRACK_MEMORY
	f32 time = FutureTimer::CurrentTime();
#endif
	IFutureAllocator * allocator = GetBestAllocator(memParam);
	void * data = allocator->Alloc(BytesForAllocation(memParam));
	FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(data);
	memcpy(DataFromHeader(header), p, memParam.m_bytes);
	header->m_allocator = allocator;
	Free(HeaderFromData(p));
#if FUTURE_TRACK_MEMORY
	FutureMemoryTracker::GetInstance()->Track(memParam, header, time);
#endif
	return DataFromHeader(header);
}

	
/*******************************************************************/
// Memory Tracker private functions

// Loop through all available allocators and return the first allocator
// that returns true for ShouldAllocate
IFutureAllocator * MemorySystem::GetBestAllocator(FutureMemoryParam memParam)
{
	if(!m_allocators)
	{
		return NULL;
	}
	AllocatorList* allocator = m_allocators;
	while(allocator && !allocator->m_allocator->ShouldAllocate(memParam))
	{
		allocator = allocator->m_next;
	}
	// if no allocator was found, then use the first one
	if(allocator == NULL)
	{
		return m_allocators->m_allocator;
	}
	return allocator->m_allocator;
}

// Get the allocator used to allocate this memory
IFutureAllocator * MemorySystem::GetPreviousAllocator(void * p)
{
	FutureAllocHeader * header = (FutureAllocHeader *)HeaderFromData(p);
	return header->m_allocator;
}

void MemorySystem::AddAllocator(IFutureAllocator * allocator)
{
	if(!m_allocators)
	{
		m_allocators = new AllocatorList;
		m_allocators->m_allocator = allocator;
		m_allocators->m_next = NULL;
		return;
	}
	AllocatorList * last = NULL;
	for(AllocatorList* a = m_allocators; a; a = a->m_next)
	{
		// check for duplicates
		if(a->m_allocator == allocator)
		{
			// found it, so leave the function
			return;
		}
			
		// find the first link with a higher priority than the new one
		if(a->m_allocator->Priority() > allocator->Priority())
		{
			break;
		}
		last = a;
	}

	// create the new link in the correct location
	AllocatorList * link = new AllocatorList;
	link->m_allocator = allocator;
	link->m_next = NULL;
	if(last)
	{
		link->m_next = last->m_next;
		last->m_next = link;
	}
	else
	{
		link->m_next = m_allocators;
		m_allocators = link;
	}
}

IFutureAllocator * MemorySystem::GetAllocator(int i)
{		
	int index = 0;
	for(AllocatorList* a = m_allocators; a; a = a->m_next)
	{
		if(index == i)
		{
			return a->m_allocator;
		}
		++i;
	}
	FUTURE_ASSERT_MSG(false, L"Index out of bounds exception looking for index %i", i);
	return NULL;
}
	
// Create the memory tracker
MemorySystem::MemorySystem( )
	: m_criticalsection(),
	  m_allocators(NULL)
{
	// create a default allocator 
	AddAllocator(new FutureMallocAllocator());
}

// destroy the tracker
MemorySystem::~MemorySystem()
{
	// loop through all allocators and release them
	for(AllocatorList* allocator = m_allocators; allocator; )
	{
		AllocatorList* next = allocator->m_next;
		if(allocator->m_allocator)
		{
			allocator->m_allocator->Release();
			delete allocator->m_allocator;
			allocator->m_allocator = NULL;
		}
		delete allocator;
		allocator = next;
	}
}

	
/*******************************************************************/
// Memory Tracker tracking functions

inline u32 MemorySystem::BytesForAllocation(FutureMemoryParam memParam)
{
	if (memParam.m_bytes == 0)
	{
		return 0;
	}
	return FutureMemory::HeaderSize() + memParam.m_bytes;
}

FutureMemoryStatistics MemorySystem::GetStatistics()
{
	return FutureMemoryTracker::GetInstance()->GetStatistics();
}

void MemorySystem::LogStatistics()
{
	FutureMemoryTracker::GetInstance()->LogStatistics();
}

void MemorySystem::LogAllocations()
{
	FutureMemoryTracker::GetInstance()->LogAllocations();
}

void MemorySystem::LogAllocation(void * p)
{
	FutureMemoryTracker::GetInstance()->LogAllocation(HeaderFromData(p));
}