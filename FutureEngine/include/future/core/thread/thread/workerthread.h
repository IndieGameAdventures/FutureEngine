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
*	A thread that works with ThreadPool to execute jobs
*/

#ifndef FUTURE_CORE_THREAD_THREAD_WORKER_H
#define FUTURE_CORE_THREAD_THREAD_WORKER_H

#include <future/core/type/type.h>

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

class FutureWorkerThread : public FutureThread
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureWorkerThread);

    FutureWorkerThread();
	virtual ~FutureWorkerThread();

	FutureResult	WaitForJob(u32 milliTimeOut = -1);
	void			Release();

protected:
	friend class FutureThreadPool;

	virtual void	OnRunThread();
	virtual void	OnFinished();

	volatile bool			m_running;
	volatile bool			m_idle;

	// keep track of threads in a linked list.
	FutureWorkerThread *	m_next;
};

#endif