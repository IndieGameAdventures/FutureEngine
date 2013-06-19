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

/*	Base class for all thread safe objects. All classes should extend this.
*	Before making any modification on an object that may be accessed by multiple
*	threads, that object should be locked and then unlocked when done
*	with modifications
*/

#ifndef FUTURE_CORE_OBJECTS_THREADSAFE_H
#define FUTURE_CORE_OBJECTS_THREADSAFE_H

#include <future/core/debug/debug.h>
#include <future/core/memory/memory.h>
#include <future/core/thread/criticalsection/criticalsection.h>

class IFutureThreadSafeObject
{
public:
	virtual void	Lock() = 0;
	virtual void	Unlock() = 0;
	virtual bool	TryLock() = 0;
};

class FutureThreadSafeObject : public IFutureThreadSafeObject
{
public:
    FutureThreadSafeObject() 
	: m_criticalSection()
	{}

	// create our own critical section
    FutureThreadSafeObject(const FutureThreadSafeObject& managed) 
	: m_criticalSection()
	{}

    virtual ~FutureThreadSafeObject() 
	{}

	inline virtual void	Lock()
	{
		m_criticalSection.Lock();
	}

	inline virtual void	Unlock()
	{
		m_criticalSection.Unlock();
	}

	inline virtual bool	TryLock()
	{
		return m_criticalSection.TryLock();
	}
protected:
	FutureCriticalSection	m_criticalSection;
};

#endif
