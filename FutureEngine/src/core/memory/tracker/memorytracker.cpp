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
*	Implementation of MemoryTracker
*/

#include <future/core/debug/debug.h>

#include <future/core/memory/memory.h>

#include <future/core/thread/criticalsection/criticalsection.h>
#include <future/core/memory/allocators/allocator.h>
#include <future/core/memory/memorystatistics.h>
#include <future/core/memory/tracker/memorytracker.h>
#include <future/core/utils/timer/timer.h>

#include <wchar.h>
	
FutureMemoryTracker * FutureMemoryTracker::instance;

void FutureMemoryTracker::CreateInstance()
{
	FUTURE_ASSERT(FutureMemoryTracker::instance == NULL);
	FutureMemoryTracker::instance = new FutureMemoryTracker();
};

void FutureMemoryTracker::DestroyInstance()
{
	FUTURE_ASSERT(FutureMemoryTracker::instance != NULL);
	delete FutureMemoryTracker::instance;
	FutureMemoryTracker::instance = NULL;
};

FutureMemoryTracker * FutureMemoryTracker::GetInstance()
{
	return FutureMemoryTracker::instance;
}

// Create the memory tracker
FutureMemoryTracker::FutureMemoryTracker( )
	: m_criticalsection(),
	  m_headerRoot(),
	  m_totalAllocations(0),
	  m_totalAllocationTime(0),
	  m_totalBytesAllocated(0)
{
	// set up the header list
	m_headerRoot.m_bytes = 0;
	m_headerRoot.m_line = 0;
	m_headerRoot.m_file = L"Start";
	m_headerRoot.m_next = NULL;
	m_headerRoot.m_previous = NULL;
	SetChecksum(&m_headerRoot);
	m_headerTail = &m_headerRoot;
}

// destroy the tracker
FutureMemoryTracker::~FutureMemoryTracker()
{
	// make sure there are no memory leaks
	if(m_headerRoot.m_next != NULL)
	{
		LogAllocations();
		FUTURE_ASSERT_MSG(false, L"Memory Leak! Memory Tracker destroyed with active allocations");
	}
}

	
/*******************************************************************/
// Memory Tracker tracking functions

void FutureMemoryTracker::Track(FutureMemoryParam memParam, FutureAllocHeader * header, f32 startTime)
{
	// if the allocation failed then we are out of memory!
	FUTURE_ASSERT_CRIT_MSG(header != NULL, 9871, L"Out of memory!");

#if FUTURE_TRACK_MEMORY

	if (header == NULL)
	{
		return;
	}

	// create the header
	header->m_bytes = memParam.m_bytes;
	header->m_type = memParam.m_type;
	header->m_file = wcsrchr(memParam.m_file, '\\' );
	header->m_file = (string)((u32)header->m_file + sizeof(wchar_t));
	header->m_line = memParam.m_line;
	SetChecksum(header);
		
	// Only one thread can change the header list and statistics at a time
	m_criticalsection.Lock();
	// Add the new header to the header list
	header->m_next = NULL;
	m_headerTail->m_next = header;
	header->m_previous = m_headerTail;
	m_headerTail = header;
	/*m_headerRoot.m_next;
	if(m_headerRoot.m_next)
	{
		m_headerRoot.m_next->m_previous = header;
	}
	header->m_previous = &m_headerRoot;
	m_headerRoot.m_next = header;*/
		
	// Update statistics
	m_totalBytesAllocated += header->m_bytes;
	m_totalAllocations += 1;
	m_totalAllocationTime += FutureTimer::TimeSince(startTime);

	// Make sure other threads can access this now
	m_criticalsection.Unlock();

	// make sure everything copied right
	FUTURE_ASSERT(header->m_line == memParam.m_line);
	FUTURE_ASSERT(header->m_bytes == memParam.m_bytes);
	FUTURE_ASSERT(header->m_bytes != 24296);
	VerifyChecksum(header);
#endif
}

void FutureMemoryTracker::Untrack(FutureAllocHeader * header)
{
#if FUTURE_TRACK_MEMORY
	if(header == NULL)
	{
		return;
	}

	// make sure it is not corrupt
	VerifyChecksum(header);

	// Only one thread can change the header list at a time
	m_criticalsection.Lock();

	// Remove the header from the header list
	FutureAllocHeader * next = header->m_next;
	FutureAllocHeader * prev = header->m_previous;

	FUTURE_ASSERT(prev != NULL);
	prev->m_next = next;
	if(next != NULL)
	{
		next->m_previous = prev;
	}
	else
	{
		// this header is the tail
		m_headerTail = prev;
	}

	// Make sure we allow other threads in when we are done
	m_criticalsection.Unlock();
#endif
}

// check all headers to make sure memory is not corrupt
void FutureMemoryTracker::VerifyAllocations()
{
#if FUTURE_TRACK_MEMORY
	for(FutureAllocHeader * header = m_headerRoot.m_next; header != NULL; header = header->m_next)
	{
		VerifyChecksum(header);
	}
#endif
}

// Set the header's check sum, each header has a unique check sum
void FutureMemoryTracker::SetChecksum(FutureAllocHeader * header)
{
#if FUTURE_TRACK_MEMORY
	header->m_checkSum = FUTURE_CHECKSUM ^ reinterpret_cast<u32>(header) ^ header->m_bytes;
#endif
}

// make sure the check sum for this header is correct, assert if is it not.
void FutureMemoryTracker::VerifyChecksum(FutureAllocHeader * header)
{
#if FUTURE_TRACK_MEMORY
	// NOTE: If this assert fires, then memory is corrupt or some else weird is happening.
	FUTURE_ASSERT_CRIT(header->m_checkSum == (FUTURE_CHECKSUM ^ reinterpret_cast<u32>(header) ^ header->m_bytes), 9899);
#endif
}


	
/*******************************************************************/
// Print debug information about the Memory Tracker

FutureMemoryStatistics FutureMemoryTracker::GetStatistics()
{
	FutureMemoryStatistics stats;
	stats.m_currentBytes = 0;
	stats.m_currentAllocations = 0;
	
#if FUTURE_TRACK_MEMORY
	for(FutureAllocHeader * header = m_headerRoot.m_next; header != NULL; header = header->m_next)
	{
		++stats.m_currentAllocations;
		stats.m_currentBytes += header->m_bytes;
	}
#endif

	stats.m_totalBytes = m_totalBytesAllocated;
	stats.m_totalAllocations = m_totalAllocations;
	stats.m_totalTimeForAllocations = m_totalAllocationTime;
	stats.m_averageAllocationSize = m_totalBytesAllocated / m_totalAllocations;
	stats.m_averageTimeForAllocation = m_totalAllocationTime / (f32)m_totalAllocations;

	return stats;
}

void FutureMemoryTracker::LogStatistics()
{
#if FUTURE_TRACK_MEMORY	
	FutureMemoryStatistics stats = GetStatistics();

	FUTURE_LOG_DEBUG(L"Current allocations: %u", stats.m_currentAllocations);
	FUTURE_LOG_DEBUG(L"Current bytes allocated: %u", stats.m_currentBytes);
	FUTURE_LOG_DEBUG(L"Total allocations: %u", m_totalAllocations);
	FUTURE_LOG_DEBUG(L"Total bytes allocated: %u", m_totalBytesAllocated);
	FUTURE_LOG_DEBUG(L"Total time for allocations: %f", stats.m_totalTimeForAllocations);
	FUTURE_LOG_DEBUG(L"Average allocation size: %u", stats.m_averageAllocationSize);
	FUTURE_LOG_DEBUG(L"Average allocation time: %f", stats.m_averageTimeForAllocation);
#else
	__noop; // don't do anything if not tracking
#endif
}

void FutureMemoryTracker::LogAllocations()
{
#if FUTURE_TRACK_MEMORY		
	if (!m_headerRoot.m_next )
	{
		FUTURE_LOG_DEBUG(L"No Current Allocations");
		return;
	}

	FutureMemoryStatistics stats = GetStatistics();
	u32 allocations = 0;
	f32 time = FutureTimer::CurrentTime();
	for(FutureAllocHeader * header = m_headerRoot.m_next; header != NULL; header = header->m_next)
	{
		++allocations;
		FUTURE_LOG_DEBUG(
			L"%u: Type: %ls File: %ls Line: %u Size: %u Percent: %f",
			allocations,
			header->m_type,
			header->m_file,
			header->m_line,
			header->m_bytes,
			((f32)header->m_bytes / (f32)stats.m_currentBytes) * 100.0f);
	}

	FUTURE_LOG_DEBUG(L"Current allocations: %u", stats.m_currentAllocations);
	FUTURE_LOG_DEBUG(L"Current bytes allocated: %u", stats.m_currentBytes);
	FUTURE_LOG_DEBUG(L"Total allocations: %u", m_totalAllocations);
	FUTURE_LOG_DEBUG(L"Total bytes allocated: %u", m_totalBytesAllocated);
	FUTURE_LOG_DEBUG(L"Total time for allocations: %f", stats.m_totalTimeForAllocations);
	FUTURE_LOG_DEBUG(L"Average allocation size: %u", stats.m_averageAllocationSize);
	FUTURE_LOG_DEBUG(L"Average allocation time: %f", stats.m_averageTimeForAllocation);
#else
	__noop; // don't do anything if not tracking
#endif
}

void FutureMemoryTracker::LogAllocation(FutureAllocHeader * header)
{
#if FUTURE_TRACK_MEMORY	
	FUTURE_LOG_DEBUG(
		L"Type: %ls File: %ls Line: %u Size: %u",
		header->m_type,
		header->m_file,
		header->m_line,
		header->m_bytes);
#else
	__noop; // don't do anything if not tracking
#endif
}
