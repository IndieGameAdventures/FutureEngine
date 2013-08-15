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
#include <future/core/object/threadsafeobject.h>

struct FutureMemoryParam;
struct FutureMemoryStatistics;
class IFutureAllocator;

		
// If we aren't tracking memory, we still need to keep track of which
// allocator was used for this allocation so we can free it properly
struct FutureAllocHeader
{
public:
	IFutureAllocator *	m_allocator;
	size_t				m_allocatorData;
};

// this keeps track of all allocations in a linked list style
// each header is placed directly before the memory it is tracking
struct FutureAllocHeaderDebug : public FutureAllocHeader
{
public:
	u32							m_headerCheck;

	u32 						m_line;
	u32 						m_bytes;

	const char *				m_type;
	const char *				m_file;

	FutureAllocHeaderDebug *	m_next;
	FutureAllocHeaderDebug *	m_previous;

	u32							m_checkSum;
};

// Memory Tracker
class FutureMemoryTracker : public FutureThreadSafeObject
{
public:
	static void 					CreateInstance();
	static void 					DestroyInstance();
	static FutureMemoryTracker * 	GetInstance();

	// Tracking functions do nothing if CoreConfig::TrackMemory

	// Functions used for tracking purposes, if data is allocated through a direct
	// call to malloc or through a system that does not use this allocator, these
	// functions can be called to track the memory. Make sure that enough memory is
	// allocated before hand by using BytesForAllocation.
	void					Track(const FutureMemoryParam & memParam, FutureAllocHeaderDebug * header, f32 timeCreated);
	void					Untrack(FutureAllocHeader * header);

	// Debugging functions, can be called from non debug/profile builds but will do nothing
	FutureMemoryStatistics	GetStatistics();
	void					LogStatistics();
	void					LogAllocations();
	void					LogAllocation(FutureAllocHeaderDebug * header);

private:
	FutureMemoryTracker();
	~FutureMemoryTracker();

	static FutureMemoryTracker * instance;

	void	VerifyAllocations();

	void	SetChecksum(FutureAllocHeaderDebug * header);
	void	VerifyChecksum(FutureAllocHeaderDebug * header);

	FutureAllocHeaderDebug		m_headerRoot;
	FutureAllocHeaderDebug *	m_headerTail;

	u64							m_totalBytesAllocated;
	u32							m_totalAllocations;
	f32							m_totalAllocationTime;
};

#endif