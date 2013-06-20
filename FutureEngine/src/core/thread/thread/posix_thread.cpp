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
*	This implementation of FutureThread uses pthread for all operations
*
*/

/*#ifndef FUTURE_CORE_THREAD_THREAD_POSIX_H
#define FUTURE_CORE_THREAD_THREAD_POSIX_H

#include <future/core/thread/thread/thread.h>

#ifndef FUTURE_USES_PTHREAD
#	error This file should only be included when using pthreads
#endif

#include <pthread.h>

class FutureThread : public IFutureThread
{
public:

    FutureThread();
	virtual ~FutureThread();

	virtual FutureResult	Start(ThreadFunction function, string name = L"", FinishedCallbackFunction onFinished = NULL);
	virtual void			Join();
	virtual FutureResult	Join(u32 milliTimeOut);
	virtual FutureResult	Join(f32 secondsTimeOut);

	virtual void			Wait(u32 millis);
	virtual void			Wait(f32 seconds);

	virtual u64				ThreadId();
	virtual void*			GetHandle();

	virtual u32				GetPriority();
	virtual void			SetPriority();

protected:

	pthread_t m_thread;
};

extern FutureStrongPointer<IFutureThread>	FutureCreateThread();

#endif*/