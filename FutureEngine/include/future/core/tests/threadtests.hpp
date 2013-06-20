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
*	Runs a simple test that creates 5 threads and runs them all at the same time
*/

#ifndef FUTURE_CORE_TESTS_THREAD_H
#define FUTURE_CORE_TESTS_THREAD_H

#include <future/core/debug/debug.h>
#include <future/core/thread/thread/thread.h>
#include <new>

class FutureThreadTests
{
protected:
	static void ThreadTest0(void*)
	{
		Sleep(10);
		FUTURE_LOG_D(L"Thread 0 executing.");
	}
	static void ThreadTest1(void*)
	{
		Sleep(8);
		FUTURE_LOG_D(L"Thread 1 executing.");
	}
	static void ThreadTest2(void*)
	{
		Sleep(5);
		FUTURE_LOG_D(L"Thread 2 executing.");
	}
	static void ThreadTest3(void*)
	{
		Sleep(2);
		FUTURE_LOG_D(L"Thread 3 executing.");
	}
	static void ThreadTest4(void*)
	{
		FUTURE_LOG_D(L"Thread 4 executing.");
	}

public:
	static void TestThreads()
	{
		FutureMemory::CreateMemory();

		IFutureThread * thread0 = FutureCreateThread();
		IFutureThread * thread1 = FutureCreateThread();
		IFutureThread * thread2 = FutureCreateThread();
		IFutureThread * thread3 = FutureCreateThread();
		IFutureThread * thread4 = FutureCreateThread();

		thread0->Start(ThreadTest0, NULL);
		thread1->Start(ThreadTest1, NULL);
		thread2->Start(ThreadTest2, NULL);
		thread3->Start(ThreadTest3, NULL);
		thread4->Start(ThreadTest4, NULL);
	
		FutureDestroyThread(thread0);
		FutureDestroyThread(thread1);
		FutureDestroyThread(thread2);
		FutureDestroyThread(thread3);
		FutureDestroyThread(thread4);

		FutureMemory::DestroyMemory();
	};
};
	

#endif