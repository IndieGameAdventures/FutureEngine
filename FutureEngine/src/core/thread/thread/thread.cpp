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
*	Implementation of IFutureThread
*
*/

#include <future/core/debug/debug.h>
#include <future/core/memory/memory.h>
#include <future/core/thread/thread/thread.h>

FutureResult IFutureThread::Join(f32 secondsTimeOut)
{
	return Join((u32)(secondsTimeOut / 1000.f));
}
void IFutureThread::Wait(f32 seconds)
{
	return Wait((u32)(seconds / 1000.f));
}
bool IFutureThread::IsStarted()
{
	return m_started;
}
bool IFutureThread::IsRunning()
{
	return m_started && !m_finished;
}
bool IFutureThread::IsFinished()
{
	return m_finished;
}

string IFutureThread::Name()
{
	return m_name;
}

void IFutureThread::OnFinished()
{
	m_finished = true;
	if(m_onFinished)
	{
		m_onFinished(m_data);
	}
}

void IFutureThread::OnRunThread()
{
	m_started = true;
	if(m_function)
	{
		m_function(m_data);
	}
}

IFutureThread::IFutureThread()
	: m_data(NULL),
	  m_finished(false),
	  m_id(-1),
	  m_name(NULL),
	  m_started(false),
	  m_priority(0),
	  m_function(NULL),
	  m_onFinished(NULL)
{}

#if FUTURE_ENABLE_MULTITHREADED
#	if FUTURE_PLATFORM_WINDOWS
#		include <future/core/thread/thread/win_thread.h>
#	elif defined(FUTURE_USES_PTHREAD)
#		include <future/core/thread/thread/posix_thread.h>
#	else
#		include <future/core/thread/thread/null_thread.h>
#	endif
#else
#	include <future/core/thread/thread/null_thread.h>
#endif
IFutureThread *	FutureCreateThread()
{
	return (IFutureThread*)(new FutureThread());
}
void FutureDestroyThread(IFutureThread * thread)
{
	if(thread)
	{
		thread->Join();
		delete thread;
	}
}
