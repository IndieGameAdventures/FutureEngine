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
*	Abstract class used for memory allocation. Multiple Allocators can be added
*	to the same MemorySystem and the lowest priority allocator that returns true for
*	ShouldAllocate will be used. The default allocator is MallocAllocator.
*/


#ifndef FUTURE_CORE_MEMORY_ALLOCATOR_H
#define FUTURE_CORE_MEMORY_ALLOCATOR_H

#include <future/core/type/type.h>

struct FutureMemoryParam;

class IFutureAllocator
{
public:
	virtual void *	Alloc(u32 bytes) = 0;
	virtual void	Free(void * p) = 0;

	virtual u8		Priority() = 0;
	virtual bool	ShouldAllocate(FutureMemoryParam memParam) = 0;

	virtual void	Release() = 0;
};

#endif