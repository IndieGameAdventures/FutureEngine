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
*	Implementation of FutureMallocAllocator
*/

#include <future/core/memory/allocators/mallocallocator.h>
#include <future/core/memory/memory.h>
#include <new>

/*******************************************************************/
// Default Malloc allocator, aligned allocations

FutureMallocAllocator::FutureMallocAllocator()
{}

FutureMallocAllocator::~FutureMallocAllocator()
{}

void * FutureMallocAllocator::Alloc(u32 bytes)
{
	return _aligned_malloc(bytes, 16);
}

void FutureMallocAllocator::Free(void * p)
{
	_aligned_free(p);
}

// return the highest priority possible, this should be our last resort allocator
u8 FutureMallocAllocator::Priority()
{
	return 255;
}

// As this allocator is our default allocator, always return true
bool FutureMallocAllocator::ShouldAllocate(FutureMemoryParam memParam)
{
	return true;
}

void FutureMallocAllocator::Release()
{
}