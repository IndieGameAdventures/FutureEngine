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
*	Implementation of FutureWorkerThread
*
*/

#include <future/core/thread/thread/workerthread.h>
#include <future/core/thread/pool/job.h>
#include <future/core/thread/pool/threadpool.h>
#include <future/core/utils/timer/timer.h>

FutureWorkerThread::FutureWorkerThread()
	: m_idle(false),
	  m_next(NULL)
{}
FutureWorkerThread::~FutureWorkerThread()
{
}

FutureResult FutureWorkerThread::WaitForJob(u32 milliTimeOut)
{
	if(m_idle)
	{
		return FR_OK;
	}
	f32 timeToWait = (f32)milliTimeOut * 1000.f;
	f32 curTime = FutureTimer::CurrentTime();
	
	while(!m_idle && (timeToWait <= 0 || FutureTimer::TimeSince(curTime) < timeToWait))
	{
		Sleep(5);
	}
	if(!m_idle)
	{
		return FR_TIMEOUT;
	}
	return FR_OK;
}

void FutureWorkerThread::OnFinished()
{
	m_finished = true;
	if(m_onFinished)
	{
		m_onFinished(m_data);
	}
}

void FutureWorkerThread::Release()
{
	m_running = false;
	Join();
}

void FutureWorkerThread::OnRunThread()
{
	m_started = true;
	m_idle = false;
	m_running = true;
#if FUTURE_ENABLE_MULTITHREADED
	while(m_running)
	{
#endif
		FutureThreadJob * job = FutureThreadPool::GetInstance()->GetNextJob();
		
		if(job)
		{
			m_idle = false;
			job->Execute(this);
			FutureThreadPool::GetInstance()->JobFinished(job);
		}
		else
		{
			m_idle = true;
			Sleep(5);
		}
#if FUTURE_ENABLE_MULTITHREADED
	}
#endif
}