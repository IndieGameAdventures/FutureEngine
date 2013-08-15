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
*	Implementation of FutureMemory
*/
#include <stdlib.h>
#include <string.h>

#include <future/core/debug/debug.h>

#include <future/core/memory/memory.h>

#include <future/core/object/threadsafeobject.h>
#include <future/core/memory/allocators/allocator.h>
#include <future/core/memory/allocators/mallocallocator.h>
#include <future/core/memory/allocators/heapallocator.h>
#include <future/core/memory/allocators/poolallocator.h>
#include <future/core/memory/memorystatistics.h>
#include <future/core/memory/tracker/memorytracker.h>
#include <future/core/utils/timer/timer.h>

/*******************************************************************/
// Structure to keep track of memory allocators
struct AllocatorList
{
	IFutureAllocator *	m_allocator;
	AllocatorList *		m_next;
};

	
/*******************************************************************/
// Memory System
class MemorySystem : public FutureThreadSafeObject
{
public:
	MemorySystem();
	~MemorySystem();

	void *					Alloc(const FutureMemoryParam & memParam);
	void *					Track(const FutureMemoryParamDebug & memParam);
	void					Free(void * p );

	u32						BytesForAllocation(const FutureMemoryParam & memParam);
	void					AddAllocator(IFutureAllocator * allocator);
	IFutureAllocator *		GetAllocator(int i);

	IFutureAllocator *		GetBestAllocator(const FutureMemoryParam & memParam);
	IFutureAllocator *		GetPreviousAllocator(void * p);
	
	FutureMemoryStatistics	GetStatistics();
	
	void					LogStatistics();
	void					LogAllocations();
	void					LogAllocation(void *);

	AllocatorList *			m_allocators;
	u32						m_currentMemoryUse;

};

MemorySystem * 	memory;

/*******************************************************************/
// FutureMemory implementation

static u32 futureHeaderSize = 0;
void FutureMemory::CreateMemory()
{
	FUTURE_ASSERT(memory == NULL);
	memory = new MemorySystem();

	// make the header size a multiple of the global alignment for
	// easier and quicker allocations.
	futureHeaderSize = 16;
	FutureMemoryTracker::CreateInstance();
}

void FutureMemory::PostConfigInit()
{
	if(FutureCoreConfig::TrackMemory())
	{
		futureHeaderSize = 48;
	}

	for(u32 i = 0; i < FutureCoreConfig::DefaultMemoryPoolAllcoators(); ++i)
	{
		memory->AddAllocator(new FuturePoolAllocator(FutureCoreConfig::DefaultMemoryPoolAllocatorBlockSizes()[i], FutureCoreConfig::DefaultMemoryPoolAllocatorPoolSizes()[i]));
	}
	memory->AddAllocator(new FutureHeapAllocator(FutureCoreConfig::DefaultMemoryHeapSize()));
}

void FutureMemory::DestroyMemory()
{
	FUTURE_ASSERT(memory != NULL);
	FutureMemoryTracker::DestroyInstance();
	delete memory;
	memory = NULL;
}

void * FutureMemory::Alloc(const FutureMemoryParam & memParam)
{
	return memory->Alloc(memParam);
}
void * FutureMemory::Track(const FutureMemoryParamDebug & memParam)
{
	return memory->Track(memParam);
}
void FutureMemory::Free(void * p)
{
	memory->Free(p);
}
u32	FutureMemory::BytesForAllocation(const FutureMemoryParam & memParam)
{
	return memory->BytesForAllocation(memParam);
}
void FutureMemory::AddAllocator(IFutureAllocator * allocator)
{
	memory->AddAllocator(allocator);
}
IFutureAllocator * FutureMemory::GetAllocator(u32 i)
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

u32 FutureMemory::HeaderSize()
{
	return futureHeaderSize; 
}

inline static void * DataFromHeader(FutureAllocHeader * header)
	{ return (void *)(((u8*)header) + FutureMemory::HeaderSize()); }
inline static FutureAllocHeader * HeaderFromData(void * p)
	{ return (FutureAllocHeader *)((u8*)p - FutureMemory::HeaderSize()); }


/*******************************************************************/
// Memory System functions
void * MemorySystem::Alloc(const FutureMemoryParam & memParam)
{
	if(memParam.m_bytes <= 0 || 
		(FutureCoreConfig::ForceInternalMemoryLimit() && (m_currentMemoryUse + memParam.m_bytes > FutureCoreConfig::InternalMemoryLimit()))
	{
		return NULL;
	}
	IFutureAllocator * allocator = GetBestAllocator(memParam); // get the best allocator
	void * p = allocator->Alloc((u32)BytesForAllocation(memParam)); // allocate enough bytes for the header
	if(!p)
	{
		FUTURE_LOG_E("Out of Memory for allocation of size %u", memParam.m_bytes);
		return NULL;
	}
	FutureAllocHeader * header = reinterpret_cast<FutureAllocHeader *>(p);
	header->m_allocator = allocator;
	m_currentMemoryUse += memParam.m_bytes;
	return DataFromHeader(header);
}

void * MemorySystem::Track(const FutureMemoryParamDebug & memParam)
{
	if(memParam.m_bytes <= 0 || 
		(FutureCoreConfig::ForceInternalMemoryLimit() && (m_currentMemoryUse + memParam.m_bytes > FutureCoreConfig::InternalMemoryLimit()))
	{
		return NULL;
	}
	f32 time = FutureTimer::CurrentTime();
	IFutureAllocator * allocator = GetBestAllocator(memParam); // get the best allocator
	void * p = allocator->Alloc((u32)BytesForAllocation(memParam)); // allocate enough bytes for the header
	if(!p)
	{
		FUTURE_LOG_E("Out of Memory for allocation of size %u", memParam.m_bytes);
		return NULL;
	}
	m_currentMemoryUse += memParam.m_bytes;
	FutureAllocHeaderDebug * header = reinterpret_cast<FutureAllocHeaderDebug *>(p);
	header->m_allocator = allocator;

	FutureMemoryTracker::GetInstance()->Track(memParam, header, time);

	return DataFromHeader(header);
}

void MemorySystem::Free(void * p)
{
	FutureMemoryTracker::GetInstance()->Untrack(HeaderFromData(p));

	IFutureAllocator * allocator = GetPreviousAllocator(p);
	allocator->Free(HeaderFromData(p));

	m_currentMemoryUse -= memParam.m_bytes;
}

	
/*******************************************************************/
// Memory Tracker private functions

// Loop through all available allocators and return the first allocator
// that returns true for ShouldAllocate
IFutureAllocator * MemorySystem::GetBestAllocator(const FutureMemoryParam & memParam)
{
	if(memParam->m_allocator != NULL)
	{
		return memParam->m_allocator;
	}
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
		m_currentMemoryUse += sizeof(AllocatorList);
		m_currentMemoryUse += sizeof(allocator);
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
	m_currentMemoryUse += sizeof(AllocatorList);
	m_currentMemoryUse += sizeof(allocator);
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
	FUTURE_ASSERT_MSG(false, "Index out of bounds exception looking for index %i", i);
	return NULL;
}
	
// Create the memory tracker
MemorySystem::MemorySystem( )
	: m_allocators(NULL),
	  m_currentMemoryUse(sizeof(MemorySystem) + sizeof(FutureMallocAllocator) + sizeof(FutureMemoryTracker))
{
	FUTURE_LOG_V("Creating Memory System");
	// create a default allocator 
	AddAllocator(new FutureMallocAllocator());
}

// destroy the tracker
MemorySystem::~MemorySystem()
{
	FUTURE_LOG_V("Destroying Memory System");
	// loop through all allocators and release them
	for(AllocatorList* allocator = m_allocators; allocator; )
	{
		AllocatorList* next = allocator->m_next;
		if(allocator->m_allocator)
		{
			m_currentMemoryUse -= sizeof(allocator->m_allocator);
			delete allocator->m_allocator;
			allocator->m_allocator = NULL;
		}
		m_currentMemoryUse -= sizeof(AllocatorList);
		delete allocator;
		allocator = next;
	}
	m_currentMemoryUse -= sizeof(MemorySystem) + sizeof(FutureMallocAllocator) + sizeof(FutureMemoryTracker);
	if(m_currentMemoryUse > 0)
	{
		FUTURE_LOG_W("Destroying Memory System will %u bytes still allocated.", %m_currentMemoryUse);
	}
}

	
/*******************************************************************/
// Memory Tracker tracking functions

inline size_t MemorySystem::BytesForAllocation(const FutureMemoryParam & memParam)
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
	FutureMemoryTracker::GetInstance()->LogAllocation((FutureAllocHeaderDebug*)HeaderFromData(p));
}