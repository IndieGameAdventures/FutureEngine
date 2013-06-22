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
*	Tests ThreadPool with 5 threads and 500 Jobs
*/

#ifndef FUTURE_CORE_TESTS_THREADPOOL_H
#define FUTURE_CORE_TESTS_THREADPOOL_H

#include <future/core/debug/debug.h>
#include <future/core/thread/pool/job.h>
#include <future/core/thread/pool/threadpool.h>
#include <future/core/utils/timer/timer.h>
#include <new>

class FutureThreadPoolTests
{
protected:
	static void ThreadTest(void* data)
	{
		u64 count = 0;
		while(count < *((u64*)data))
		{
			++count;
		}
		//FUTURE_LOG_D(L"Thread Pool has %i jobs left", FutureThreadPool::GetInstance()->ActiveJobs());
	}

	static void RunTest(u32 threads)
	{
		u64 timeout = 100000000;

		f32 time = FutureTimer::CurrentTime();

		FutureThreadPool::GetInstance()->SetNumThreads(threads);

		for(int i = 0; i < 100; ++i)
		{
			FutureThreadJob * job = new FutureThreadJob(FutureThreadPoolTests::ThreadTest, &timeout);
			FutureThreadPool::GetInstance()->AddJob(job);
			if(i % 5 == 0)
			{
				job = new FutureThreadJob(FutureThreadPoolTests::ThreadTest, &timeout, FutureThreadJob::JobPriority_Critical);
				FutureThreadPool::GetInstance()->AddJob(job);
			}
		}

		FutureThreadPool::GetInstance()->WaitForCompletion();

		FUTURE_LOG_DEBUG(L"Took %f seconds for thread pool with %i threads", FutureTimer::TimeSince(time), threads);
	}
public:
	static void TestThreadPool()
	{
		FutureMemory::CreateMemory();
		FutureThreadPool::CreateInstance();
		
		RunTest(1);
		RunTest(5);
		RunTest(10);
		RunTest(20);
		RunTest(25);
		RunTest(30);
		RunTest(40);
		RunTest(50);

		FutureThreadPool::DestroyInstance();
		FutureMemory::DestroyMemory();
	};
};
	

#endif