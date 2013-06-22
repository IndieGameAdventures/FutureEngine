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
*	Implementation of FutureThread for single threaded builds
*
*/

#include <future/core/type/type.h>

#if !(FUTURE_PLATFORM_WINDOWS || defined(FUTURE_USES_PTHREAD)) || !FUTURE_ENABLE_MULTITHREADED
#include <future/core/thread/thread/null_thread.h>


FutureThread::FutureThread()
	: IFutureThread()
{}
FutureThread::~FutureThread()
{}

FutureResult FutureThread::Start(ThreadFunction function, void * data, FinishedCallbackFunction onFinished)
{
	if(!function)
	{
		return FR_INVALID_ARG;
	}

	m_onFinished = onFinished;
	m_function = function;
	m_data = data;

	OnRunThread();
	OnFinished();

	return FR_OK;
}

void FutureThread::Join()
{
	return;
}

FutureResult FutureThread::Join(u32 milliTimeOut)
{
	return FR_OK;
}

void FutureThread::Wait(u32 millis)
{
	Sleep(millis);
}

void FutureThread::Kill()
{
}


u64 FutureThread::ThreadId()
{
	return 0;
}
void* FutureThread::GetHandle()
{
	return NULL;
}

IFutureThread::FutureThreadPriority FutureThread::GetPriority()
{
	return (IFutureThread::FutureThreadPriority)m_priority;
}
void FutureThread::SetPriority(FutureThreadPriority priority)
{
	m_priority = priority;
}

u64 IFutureThread::CurrentThreadId()
{
	return (u64)0;
}

#endif