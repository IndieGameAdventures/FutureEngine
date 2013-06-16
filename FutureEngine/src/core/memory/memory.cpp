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
	void					EnsureAllocator(IFutureAllocator * allocator);
	IFutureAllocator *		GetAllocator(int i);

	IFutureAllocator *		GetBestAllocator(FutureMemoryParam memParam);
	IFutureAllocator *		GetPreviousAllocator(void * p);
	
	FutureMemoryStatistics	GetStatistics();
	FutureMemoryStatistics	GetStatisticsForAllocator(IFutureAllocator * allocator);
	
	void					LogAllocations();
	void					LogAllocation(void *);
	void					LogAllocator(IFutureAllocator * allocator);

	FutureCriticalSection	m_criticalsection;
	AllocatorList *			m_allocators;
};

MemorySystem * memory;

/*******************************************************************/
// FutureMemory implementation

void FutureMemory::CreateMemory()
{
	FUTURE_ASSERT(memory == NULL);
	memory = new MemorySystem();
	FutureMemoryTracker::CreateInstance();
};

void FutureMemory::DestroyMemory()
{
	FUTURE_ASSERT(memory != NULL);
	FutureMemoryTracker::DestroyInstance();
	delete memory;
	memory = NULL;
};

void * FutureMemory::Alloc(FutureMemoryParam memParam)
{
	return memory->Alloc(memParam);
};
void FutureMemory::Free(void * p)
{
	memory->Free(p);
};
void * FutureMemory::ReAlloc(void * p, FutureMemoryParam memParam)
{
	return memory->ReAlloc(p, memParam);
};
u32	FutureMemory::BytesForAllocation(FutureMemoryParam memParam)
{
	return memory->BytesForAllocation(memParam);
};
void FutureMemory::EnsureAllocator(IFutureAllocator * allocator)
{
	memory->EnsureAllocator(allocator);
};
IFutureAllocator * FutureMemory::GetAllocator(int i)
{
	return memory->GetAllocator(i);
};
FutureMemoryStatistics FutureMemory::GetStatistics()
{
	return memory->GetStatistics();
};
FutureMemoryStatistics	FutureMemory::GetStatisticsForAllocator(IFutureAllocator * allocator)
{
	return memory->GetStatisticsForAllocator(allocator);
};
void FutureMemory::LogAllocations()
{
	return memory->LogAllocations();
};
void FutureMemory::LogAllocation(void * p)
{
	return memory->LogAllocation(p);
};
void FutureMemory::LogAllocator(IFutureAllocator * allocator)
{
	return memory->LogAllocator(allocator);
};



/*******************************************************************/
// helper functions

inline u32 HeaderSize()
	{ return sizeof(FutureAllocHeader); }
inline void * DataFromHeader(FutureAllocHeader * header)
	{ return (void *)(reinterpret_cast< u32 >(header) + HeaderSize()); }
inline FutureAllocHeader * HeaderFromData(void * p)
	{ return reinterpret_cast<FutureAllocHeader *>(reinterpret_cast< u32 >(p) - HeaderSize()); }


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
	IFutureAllocator * allocator = GetPreviousAllocator(p);
#if FUTURE_TRACK_MEMORY
	f32 time = FutureTimer::CurrentTime();
	FutureMemoryTracker::GetInstance()->Untrack(HeaderFromData(p));
#endif
	void * data = allocator->ReAlloc(HeaderFromData(p), BytesForAllocation(memParam));
	FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(data);
	header->m_allocator = allocator;
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

void MemorySystem::EnsureAllocator(IFutureAllocator * allocator)
{
	if(!m_allocators)
	{
		m_allocators = new AllocatorList;
		m_allocators->m_allocator = allocator;
		m_allocators->m_next = NULL;
		return;
	}
	AllocatorList * last = m_allocators;
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
	if(last && last->m_next != NULL)
	{
		link->m_next = last->m_next;
	}
	last->m_next = link;
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
	: m_criticalsection()
{
	// create a default allocator 
	m_allocators = new AllocatorList();
	m_allocators->m_allocator = new FutureMallocAllocator();
	m_allocators->m_next = NULL;
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
			allocator->m_allocator = NULL;
		}
		::free(allocator);
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
	return sizeof(FutureAllocHeader) + memParam.m_bytes;
}

FutureMemoryStatistics MemorySystem::GetStatistics()
{
	return FutureMemoryTracker::GetInstance()->GetStatistics();
};

FutureMemoryStatistics MemorySystem::GetStatisticsForAllocator(IFutureAllocator * allocator)
{
	return FutureMemoryTracker::GetInstance()->GetStatisticsForAllocator(allocator);
};

void MemorySystem::LogAllocations()
{
	FutureMemoryTracker::GetInstance()->LogAllocations();
};

void MemorySystem::LogAllocation(void * p)
{
	FutureMemoryTracker::GetInstance()->LogAllocation(HeaderFromData(p));
};

void MemorySystem::LogAllocator(IFutureAllocator * allocator)
{
	FutureMemoryTracker::GetInstance()->LogAllocator(allocator);
};