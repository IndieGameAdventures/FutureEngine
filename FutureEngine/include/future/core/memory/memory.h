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
*	A Memory System. This class controls memory allocations order to use
*	a custom allocator and store additional data for each allocation. In
*	Debug or when profiling in Release this class will store a large amount
*	of statistical data to help ensure the rest of the program is using
*	memory efficiently. It also detect memory leaks and assert if it is
*	shutdown without all allocations being deleted first.
*
*	The easiest way to allocate memory with this system is to call FUTURE_CREATE
*	with the object type. 
*
*	Object o = new FUTURE_CREATE(Object) Object();
*
*	In place of using FUTURE_CREATE you can use FUTURE_DECLARE_MEMORY_OPERATORS
*	in an object to define it's new and delete operators to use this memory system
*
*	This tracker also has the nice feature of taking no overhead in a
*	production build. All tracking and leak checking is disabled and
*	only allocation required headers of 4 bytes are added. Be careful
*	as this tracker will perform minimal error checking in release
*
*	If this file is included in an application, that application must
*	call FutureMemory::CreateMemory() before allocating any memory through
*	ALLOC or new and must call FutureMemory::DestroyMemory() . 
*	Defining _DEBUG, _PROFILE, or _PROFILE_MEMORY will turn tracking on.
*	Tracking can be manual turned on or off by declaring 
*	FUTURE_TRACK_MEMORY to 1 (true) or 0 (false).
*	
*/

#ifndef FUTURE_CORE_MEMORY_H
#define FUTURE_CORE_MEMORY_H

#include <future/core/type/type.h>
#include <new>

struct FutureMemoryParam;
struct FutureMemoryStatistics;
class IFutureAllocator;

class FutureMemory
{
public:
	static void CreateMemory(u8 globalAlignment = 16);
	static void DestroyMemory();

	// Chooses the best allocator for the param and returns the newly allocated memory location
	// If tracking is turned on, this will also track the new memory
	static void *	Alloc(FutureMemoryParam memParam);
	static void		Free(void * p);
	static void *	ReAlloc(void * p, FutureMemoryParam memParam);

	static u8		GetGlobalAlignment();

	// The total bytes needed for an allocation
	static size_t	BytesForAllocation(FutureMemoryParam memParam);

	// Allocators can be added but cannot be removed as they may be needed
	// to free memory. The allocator with the lowest priority that returns
	// true for ShouldAllocate will be used for each allocation.
	static void					AddAllocator(IFutureAllocator * allocator);
	static IFutureAllocator *	GetAllocator(u32 i);

	// Debugging functions, can be called from non debug/profile builds but will do nothing
	static FutureMemoryStatistics	GetStatistics();

	static void						LogStatistics();
	static void						LogAllocations();
	static void						LogAllocation(void *);

	/*******************************************************************/
	// helper functions

	static size_t HeaderSize(); // return the size of the header added to each allocation in bytes
};


// this parameter tells the memory tracker how is should store allocation request
// NOTE: mainly used to make memory tracking easier
#if FUTURE_TRACK_MEMORY
struct FutureMemoryParam
{	
	FutureMemoryParam(size_t bytes, string type = 0, string file = 0, u32 line = 0, IFutureAllocator * allocator = 0)
		: m_bytes(bytes),
		  m_type(type),
		  m_file(file),
		  m_line(line),
		  m_allocator(allocator)
	{ ; }

	size_t 	m_bytes;	// bytes needed in allocation
	string	m_type;		// the type of object being allocated
	string 	m_file;		// file allocation was requested from
	u32		m_line;		// file line on which allocation was requested

	IFutureAllocator *	m_allocator; // forces the use of a specific allocator
};

// returns a pointer to the new allocation
#define FUTURE_ALLOC(size, type)			FutureMemory::Alloc(FutureMemoryParam(size, type, WFILE, __LINE__ ))
// returns a pointer to a new allocation and copies the original memory
#define FUTURE_REALLOC(p, size, type)		FutureMemory::ReAlloc(p, FutureMemoryParam(size, type, WFILE, __LINE__ ))
// frees the allocated memory
#define FUTURE_FREE(p)						FutureMemory::Free((void *)p)

#else
struct FutureMemoryParam
{	
	FutureMemoryParam(size_t bytes)
		: m_bytes(bytes)
	{ ; }

	size_t 	m_bytes;	// bytes needed in allocation
};

// returns a pointer to the new allocation
#define FUTURE_ALLOC(size, type)			(FutureMemory::Alloc(FutureMemoryParam(size))
// returns a pointer to a new allocation and copies the original memory
#define FUTURE_REALLOC(p, size, type)		(FutureMemory::ReAlloc(p, FutureMemoryParam(size))
// frees the allocated memory
#define FUTURE_FREE(p)						(FutureMemory::Free((void *)p)

#endif

#define FUTURE_CREATE(type)					(FUTURE_ALLOC((size_t)sizeof(type), WIDEN(STRINGIFY(type))))

#define FUTURE_DECLARE_MEMORY_OPERATORS(type)						\
public:																\
	inline void * operator new(size_t bytes)						\
	{																\
		FUTURE_ASSERT(bytes > 0);									\
		return FUTURE_ALLOC(bytes, WIDEN(STRINGIFY(type)));			\
	}																\
	inline void operator delete(void* p)							\
	{																\
		FUTURE_ASSERT(p);											\
		FUTURE_FREE(p);												\
	}																\
	inline void*  operator new(size_t, void* p)	{ return p; }

#endif