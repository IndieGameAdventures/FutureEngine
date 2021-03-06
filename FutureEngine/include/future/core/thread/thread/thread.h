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
*	IFutureThread interface contains a system thread. IFutureThread cannot
*	be instantiated but must be created through CreateFutureThread which
*	will ensure the newly created thread is compatible with the current
*	platform and type settings.
*
*/

#ifndef FUTURE_CORE_THREAD_THREAD_H
#define FUTURE_CORE_THREAD_THREAD_H

#include <future/core/object/managedobject.h>

#if FUTURE_ENABLE_MULTITHREADED && defined(FUTURE_USES_PTHREAD)
#	include <unistd.h>
#	define Sleep(milli) usleep(milli * 1000)
#endif

class IFutureThread : public FutureManagedObject
{
public:
	static u64				CurrentThreadId();
	static IFutureThread *	CreateThread();
	static void				DestroyThread(IFutureThread * thread);

	enum FutureThreadPriority
	{
		FutureThreadPriority_Idle = -15,
		FutureThreadPriority_Lowest = -2,
		FutureThreadPriority_Low = -1,
		FutureThreadPriority_Normal = 0,
		FutureThreadPriority_High = 1,
		FutureThreadPriority_Highest = 2,
		FutureThreadPriority_Critical = 15
	};

	typedef void (*ThreadFunction)(void*);
	typedef void (*FinishedCallbackFunction)(void*);

	virtual FutureResult	Start(ThreadFunction function, void * data = NULL, FinishedCallbackFunction onFinished = NULL) = 0;
	virtual void			Join() = 0;
	virtual FutureResult	Join(u32 milliTimeOut) = 0;
	virtual FutureResult	Join(f32 secondsTimeOut);

	virtual void			Wait(u32 millis) = 0;
	virtual void			Wait(f32 seconds);

	virtual void			Kill() = 0;

	virtual u64				ThreadId() = 0;
	virtual void*			GetHandle() = 0;

	virtual FutureThreadPriority	GetPriority() = 0;
	virtual void					SetPriority(FutureThreadPriority priority) = 0;
 
	bool					IsStarted();
	bool					IsRunning();
	bool					IsFinished();

 
protected:

	u32				m_priority;
	u64				m_id;
	bool			m_started;
	bool			m_finished;
	void *			m_data;

	ThreadFunction				m_function;
	FinishedCallbackFunction	m_onFinished;

	virtual void	OnFinished();
	virtual void	OnRunThread();

    IFutureThread();
	IFutureThread(const IFutureThread& thread);
};



#endif