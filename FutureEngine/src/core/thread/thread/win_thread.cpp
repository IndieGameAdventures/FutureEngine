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
*	Implementation of FutureThread using windows threads
*
*/

#include <future/core/thread/thread/win_thread.h>

#include <windows.h>

DWORD WINAPI FutureThread::RunThreadInternal(LPVOID param)
{
	((FutureThread*)param)->OnRunThread();
	((FutureThread*)param)->OnFinished();
	return 0;
}

FutureThread::FutureThread()
	: IFutureThread(),
	  m_thread(NULL)
{}
FutureThread::~FutureThread()
{

}

FutureResult FutureThread::Start(ThreadFunction function, void * data, FinishedCallbackFunction onFinished)
{
	Lock();
	// Make sure we aren't already started
	FUTURE_ASSERT(!m_started || m_finished);

	m_finished = false;
	m_onFinished = onFinished;
	m_function = function;
	m_data = data;

	DWORD id = 0;
	m_thread = CreateThread(NULL, 0, &FutureThread::RunThreadInternal, this, 0, &id);
	m_id = id;
	m_started = true;
	Unlock();

	if(m_thread == NULL)
	{
		m_started = false;
		return FR_ERROR;
	}

	return FR_OK;
}

void FutureThread::Join()
{
	Join(INFINITE);
}

FutureResult FutureThread::Join(u32 milliTimeOut)
{
	FUTURE_ASSERT(m_thread);
	DWORD result = WaitForSingleObject(m_thread, milliTimeOut);
	if(result == WAIT_TIMEOUT)
	{
		return FR_TIMEOUT;
	}
	else if(result == WAIT_FAILED || result == WAIT_ABANDONED)
	{
		return FR_ERROR;
	}
	return FR_OK;
}

void FutureThread::Wait(u32 millis)
{
	Sleep(millis);
}

void FutureThread::Kill()
{
	FUTURE_ASSERT(m_thread);
#pragma warning(suppress: 6258)
	TerminateThread(m_thread, 0);
}

u64 FutureThread::ThreadId()
{
	return m_id;
}
void* FutureThread::GetHandle()
{
	return m_thread;
}

IFutureThread::FutureThreadPriority FutureThread::GetPriority()
{
	if(m_thread)
	{
		return (IFutureThread::FutureThreadPriority)GetThreadPriority(m_thread);
	}
	else
	{
		return (IFutureThread::FutureThreadPriority)m_priority;
	}
}
void FutureThread::SetPriority(FutureThreadPriority priority)
{
	m_priority = priority;
	if(m_thread)
	{
		SetThreadPriority(m_thread, priority);
	}
}

u64 IFutureThread::CurrentThreadId()
{
	return (u64)GetCurrentThreadId();
}
