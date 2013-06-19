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

#ifndef FUTURE_CORE_TESTS_ALLOCATOR_H
#define FUTURE_CORE_TESTS_ALLOCATOR_H

#include <future/core/debug/debug.h>
#include <future/core/memory/allocators/mallocallocator.h>
#include <future/core/memory/allocators/poolallocator.h>
#include <future/core/memory/allocators/heapallocator.h>
#include <future/core/memory/allocators/stackallocator.h>
#include <future/core/utils/timer/timer.h>
#include <new>

class FutureAllocatorTests
{
public:
	static const u32 TEST_OBJECTS = 1024 * 1024;

	struct MemoryTestStruct
	{
		MemoryTestStruct()
			:var0(5)
		{}

		u8		var0;
		s16		var1;
		string	test;
		void*	pointer;
	};

	static void TestAllocator(IFutureAllocator * allocator)
	{
		MemoryTestStruct ** test = (MemoryTestStruct**)malloc(sizeof(MemoryTestStruct*) * TEST_OBJECTS);
		for(int i = 0; i < TEST_OBJECTS; ++i)
		{
			test[i] = new (allocator->Alloc(sizeof(MemoryTestStruct))) MemoryTestStruct();
			FUTURE_ASSERT(test[i] && test[i]->var0 == 5);
		}
		for(int i = TEST_OBJECTS - 1; i >= 0; --i)
		{
			FUTURE_ASSERT(test[i] && test[i]->var0 == 5);
			allocator->Free(test[i]);
			test[i] = NULL;
		}
		free(test);
	}

	static void TestMallocAllocator()
	{
		f32 start = FutureTimer::CurrentTime();
		FutureMallocAllocator * allocator = new FutureMallocAllocator();
		allocator->SetAlign(16);
		TestAllocator(allocator);
		allocator->Release();
		f32 runtime = FutureTimer::TimeSince(start);
		FUTURE_LOG_DEBUG(L"Malloc Allocator took %f seconds to allocate and free %u elements", runtime, TEST_OBJECTS);
	};

	static void TestPoolAllocator()
	{
		f32 start = FutureTimer::CurrentTime();
		FuturePoolAllocator * allocator = new FuturePoolAllocator(16, sizeof(MemoryTestStruct), TEST_OBJECTS);
		TestAllocator(allocator);
		allocator->Release();
		f32 runtime = FutureTimer::TimeSince(start);
		FUTURE_LOG_DEBUG(L"Pool Allocator took %f seconds to allocate and free %u elements", runtime, TEST_OBJECTS);
	};
	
	static void TestHeapAllocator()
	{
		f32 start = FutureTimer::CurrentTime();
		FutureHeapAllocator * allocator = new FutureHeapAllocator(16, 1024 * 1024, false);
		TestAllocator(allocator);
		allocator->Release();
		f32 runtime = FutureTimer::TimeSince(start);
		FUTURE_LOG_DEBUG(L"Heap Allocator took %f seconds to allocate and free %u elements", runtime, TEST_OBJECTS);
	};
	
	static void TestStackAllocator()
	{
		f32 start = FutureTimer::CurrentTime();
		FutureStackAllocator * allocator = new FutureStackAllocator(16, 1024 * 1024, false);
		TestAllocator(allocator);
		allocator->Release();
		f32 runtime = FutureTimer::TimeSince(start);
		FUTURE_LOG_DEBUG(L"Stack Allocator took %f seconds to allocate and free %u elements", runtime, TEST_OBJECTS);
	};
};
	

#endif