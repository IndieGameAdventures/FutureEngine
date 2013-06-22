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
*	Implementation of FutureThread using posix threads
*
*/

#include <future/core/type/type.h>

#ifdef FUTURE_USES_PTHREAD

#include <future/core/thread/thread/posix_thread.h>
#include <future/core/utils/timer/timer.h>
#include <unistd.h>

void * FutureThread::RunThreadInternal(void * param)
{
	((FutureThread*)param)->OnRunThread();
	((FutureThread*)param)->OnFinished();
	return NULL;
}

FutureThread::FutureThread()
	: IFutureThread(),
	  m_thread(0)
{}

FutureThread::~FutureThread()
{
	if(IsRunning())
	{
		pthread_kill(m_thread);
	}
}

FutureResult FutureThread::Start(ThreadFunction function, void * data, FinishedCallbackFunction onFinished)
{
	// Make sure we aren't already started
	FUTURE_ASSERT(!m_started || m_finished);

	Lock();

	m_finished = false;
	m_onFinished = onFinished;
	m_function = function;
	m_data = data;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	__sched_param priority;
	priority.sched_priority = m_priority;
	pthread_attr_setschedparam(&attr, &priority);

	u32 result = pthread_create(&m_thread, &attr, &FutureThread::RunThreadInternal, (void *)this);
	m_id = (u64)m_thread;
	m_started = true;
	Unlock();

    switch (errno) 
	{
    case EINVAL:
		m_started = false;
		return FR_INVALID_ARG;
    case EAGAIN:
    case EPERM:
    default:
		m_started = false;
		return FR_ERROR;
    }

	return FR_OK;
}

void FutureThread::Join()
{
	FUTURE_ASSERT(m_thread);
	pthread_join(m_thread);
}

FutureResult FutureThread::Join(u32 milliTimeOut)
{
	FUTURE_ASSERT(m_thread);
	f32 timeToWait = (f32)milliTimeOut * 1000.f;
	f32 curTime = FutureTimer::CurrentTime();
	
	while(!m_finished && (milliTimeOut <= 0 || FutureTimer::TimeSince(curTime) < timeToWait))
	{
		sleep(5);
	}
	if(!m_finished)
	{
		return FR_TIMEOUT;
	}
	return FR_OK;
}

void FutureThread::Wait(u32 millis)
{
	sleep(millis);
}

void FutureThread::Kill()
{
	FUTURE_ASSERT(m_thread);
	pthread_kill(m_thread, 0);
}

u64 FutureThread::ThreadId()
{
	return m_id;
}
void* FutureThread::GetHandle()
{
	return (void*)&m_thread;
}

IFutureThread::FutureThreadPriority FutureThread::GetPriority()
{
	return (IFutureThread::FutureThreadPriority)m_priority;
}
void FutureThread::SetPriority(FutureThreadPriority priority)
{
	m_priority = priority;
	if(m_thread)
	{
		__sched_param priority;
		priority.sched_priority = m_priority;
		u32 policy;
		pthread_attr_getschedpolicy(&m_thread, &policy);
		pthread_setschedparam(&m_thread, policy, &priority);
	}
}

u64 IFutureThread::CurrentThreadId()
{
	return (u64)pthread_self();
}

#endif