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
*	Contains Units tests for Debug functions
*/

#ifndef FUTURE_CORE_TESTS_MEMORY_H
#define FUTURE_CORE_TESTS_MEMORY_H

#include <future/core/debug/debug.h>
#include <future/core/utils/timer/timer.h>
#include <future/core/memory/memory.h>
#include <future/core/memory/tracker/memorytracker.h>
#include <future/core/memory/memoryStatistics.h>
#include <future/core/memory/allocators/poolallocator.h>
#include <future/core/memory/allocators/heapallocator.h>
#include <new>

class FutureMemoryTests
{
public:
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

	struct MemoryTestStruct2
	{
		FUTURE_DECLARE_MEMORY_OPERATORS(MemoryTestStruct2);

		MemoryTestStruct2()
			:var0(15)
		{}

		u8		var0;
		s16		var1;
		string	test;
		void*	pointer;
		u32		m_array[32];
	};

	static void TestDefaultTracking()
	{
		f32 startTime = FutureTimer::CurrentTime();
		FutureMemory::CreateMemory();
		FutureMemory::AddAllocator(new FuturePoolAllocator(FutureMemory::GetGlobalAlignment(), sizeof(MemoryTestStruct)));
		FutureMemory::AddAllocator(new FutureHeapAllocator(FutureMemory::GetGlobalAlignment()));

		MemoryTestStruct ** test = (MemoryTestStruct**)FUTURE_ALLOC(sizeof(MemoryTestStruct*) * 1024 * 8, L"Test Array");
		MemoryTestStruct2 ** test2 = (MemoryTestStruct2**)FUTURE_ALLOC(sizeof(MemoryTestStruct2*) * 1024 * 8, L"Test2 Array");
		
		for(int i = 0; i < 1024 * 8; ++i)
		{
			test[i] = new (FUTURE_CREATE(MemoryTestStruct)) MemoryTestStruct();
			FUTURE_ASSERT(test[i] && test[i]->var0 == 5);
			test2[i] = new MemoryTestStruct2();
			FUTURE_ASSERT(test2[i] && test2[i]->var0 == 15);
		}
		//FutureMemory::LogAllocations();
		FutureMemory::LogStatistics();
		for(int i = 0; i < 1024 * 8; ++i)
		{
			FUTURE_FREE(test[i]);
			test[i] = NULL;
			delete test2[i];
			test2[i] = NULL;
		}

		FUTURE_FREE(test);
		FutureMemoryTracker::GetInstance()->Untrack((FutureAllocHeader *)((u32)test2 - FutureMemory::HeaderSize()));

		FutureMemory::LogAllocations();
		FutureMemory::LogStatistics();
		FutureMemory::DestroyMemory();

		f32 endTime = FutureTimer::TimeSince(startTime);
		FUTURE_LOG_DEBUG(L"Took %f second to allocate and free 16384 objects", endTime);
	}

};
#endif