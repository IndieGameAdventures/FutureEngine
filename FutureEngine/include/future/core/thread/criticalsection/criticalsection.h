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
*	A simple Critical Section. This is used to ensure that multiple threads are
*	not manipulating the same memory at the same time. After creating a Critical
*	Section call Lock to prevent other threads from getting past this point. Lock
*	will block the current thread until the critical section has been Unlocked.
*	When you are done changing memory, be sure to call Unlock or any other thread,
*	including the current thread will be blocked indefinitely on the next Lock call.
*	
*/

#ifndef FUTURE_CORE_THREAD_CRITICALSECTION_H
#define FUTURE_CORE_THREAD_CRITICALSECTION_H

#include <future/core/type/type.h>

#if FUTURE_PLATFORM_WINDOWS
#	include <windows.h>
#elif defined(FUTURE_USES_PTHREAD)
#	include <pthread.h>
#else
#	error Platform thread type is not defined!
#endif

class FutureCriticalSection
{
public:
	FutureCriticalSection();
	~FutureCriticalSection();

	/*	Attempts to Lock this Critical Section. 
	*	Blocks the current thread until the lock is successful.
	*/
	void Lock();

	/*	Unlocks This Critical Section so other threads can access it.
	*/
	void Unlock();

	/*	Attempts to Lock this Critical Section. 
	*	Does not block if already locked.
	*
	*	@return - Returns true if the lock was successful, false otherwise
	*/
	bool TryLock();

private:
#if FUTURE_PLATFORM_WINDOWS
	CRITICAL_SECTION m_mutex;
#elif defined(FUTURE_USES_PTHREAD)
	pthread_mutex_t  m_mutex;
#endif
};

#endif