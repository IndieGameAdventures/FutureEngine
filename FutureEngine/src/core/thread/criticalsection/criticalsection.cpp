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
*	Implementation of Critical Section
*/

#include <future/core/debug/debug.h>
#include <future/core/thread/criticalsection/criticalsection.h>

// we only want to define these functions is we are using multiple threads
#if FUTURE_ENABLE_MULTITHREADED

/*
*	Initialize the critical section or initialize a new pthread mutex
*/
FutureCriticalSection::FutureCriticalSection()
{
#if FUTURE_PLATFORM_WINDOWS
	InitializeCriticalSection(&m_mutex);
#elif defined(FUTURE_USES_PTHREAD)
	pthread_mutexattr_t mta;
	pthread_mutexattr_init(&mta);
	pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_mutex, &mta);
	pthread_mutexattr_destroy(&mta);
#endif
}

	
/*
*	Release the critical section or destroy the mutex
*/
FutureCriticalSection::~FutureCriticalSection()
{
#if FUTURE_PLATFORM_WINDOWS
	DeleteCriticalSection(&m_mutex);
#elif defined(FUTURE_USES_PTHREAD)
	pthread_mutex_destroy(&m_mutex);
#endif
}
	
/*
*	Lock the mutex, blocks until the mutex is available
*/
void FutureCriticalSection::Lock()
{
#if FUTURE_PLATFORM_WINDOWS
	EnterCriticalSection(&m_mutex);
#elif defined(FUTURE_USES_PTHREAD)
	pthread_mutex_lock(&m_mutex);
#endif
}
	
/*
*	Unlock the mutex so other threads can access this mutex
*/
void FutureCriticalSection::Unlock()
{
#if FUTURE_PLATFORM_WINDOWS
	LeaveCriticalSection(&m_mutex);
#elif defined(FUTURE_USES_PTHREAD)
	pthread_mutex_unlock(&m_mutex);
#endif
}
	
	
/*
*	Try to lock this mutex, does not block
*/
bool FutureCriticalSection::TryLock()
{
#if FUTURE_PLATFORM_WINDOWS
	return TryEnterCriticalSection(&m_mutex) == 1;
#elif defined(FUTURE_USES_PTHREAD)
	return pthread_mutex_trylock(&m_mutex) == 0;
#endif
}

#endif