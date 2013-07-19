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
*	A Memory Tracker. 
*	In Debug or when profiling in Release this class will store a large amount
*	of statistical data to help ensure the rest of the program is using
*	memory efficiently. It also detect memory leaks and assert if it is
*	shutdown without all allocations being deleted first.
*
*	This tracker also has the nice feature of taking no overhead in a
*	production build. All tracking and leak checking is disabled and
*	only allocation required headers of 4 bytes are added. Be careful
*	as this tracker will perform minimal error checking in Release
*	
*/

#ifndef FUTURE_CORE_MEMORY_TRACKER_H
#define FUTURE_CORE_MEMORY_TRACKER_H

#include <future/core/type/type.h>
#include <future/core/thread/criticalsection/criticalsection.h>

struct FutureMemoryParam;
struct FutureMemoryStatistics;
class IFutureAllocator;

#if FUTURE_TRACK_MEMORY
// this keeps track of all allocations in a linked list style
// each header is placed directly before the memory it is tracking
struct FutureAllocHeader
{
	IFutureAllocator *	m_allocator;
	size_t				m_allocatorData;

	u16 				m_bytes;

	string 				m_type;
	string 				m_file;
	u16 				m_line;

	FutureAllocHeader *	m_next;
	FutureAllocHeader *	m_previous;

	u32					m_checkSum;
};
		
#else
// If we aren't tracking memory, we still need to keep track of which
// allocator was used for this allocation so we can free it properly
struct FutureAllocHeader
{
	IFutureAllocator *	m_allocator;
	size_t				m_allocatorData;
};
#endif

// Memory Tracker
class FutureMemoryTracker
{
public:
	static void CreateInstance();
	static void DestroyInstance();
	static FutureMemoryTracker * GetInstance();

	// Tracking functions do nothing if FUTURE_TRACK_MEMORY is 0 

	// Functions used for tracking purposes, if data is allocated through a direct
	// call to malloc or through a system that does not use this allocator, these
	// functions can be called to track the memory. Make sure that enough memory is
	// allocated before hand by using BytesForAllocation.
	void	Track(FutureMemoryParam memParam, FutureAllocHeader * header, f32 timeCreated);
	void	Untrack(FutureAllocHeader * header);

	// Debugging functions, can be called from non debug/profile builds but will do nothing
	FutureMemoryStatistics	GetStatistics();
	void					LogStatistics();
	void					LogAllocations();
	void					LogAllocation(FutureAllocHeader * header);

private:
	FutureMemoryTracker();
	~FutureMemoryTracker();

	static FutureMemoryTracker * instance;

	void	VerifyAllocations();

	void	SetChecksum(FutureAllocHeader * header);
	void	VerifyChecksum(FutureAllocHeader * header);

	FutureAllocHeader		m_headerRoot;
	FutureAllocHeader *		m_headerTail;
	FutureCriticalSection	m_criticalsection;

	u32						m_totalBytesAllocated;
	u32						m_totalAllocations;
	f32						m_totalAllocationTime;
};

#endif