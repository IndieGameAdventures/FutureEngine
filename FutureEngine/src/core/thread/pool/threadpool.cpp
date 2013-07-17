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
*	ThreadPool keeps a pool of threads available for performing Jobs. Threadpool
*	keeps a list of jobs in a Priority Queue and pulls jobs off the queue whenever
*	a thread becomes available. Jobs with higher priority are executed first.
*
*	When running in a single threaded application, ThreadPool executes each job
*	on the main thread, when WaitForCompletion is called. If a timeout is specified
*	then ThreadPool will execute as many jobs as possible within the allotted time
*	then exit, leaving unfinished jobs in the queue.
*/

#include <future/core/thread/pool/threadpool.h>
#include <future/core/thread/thread/workerthread.h>
#include <future/core/utils/timer/timer.h>

FutureThreadPool * FutureThreadPool::ms_instance = NULL;

FutureThreadPool::FutureThreadPool()
	: m_jobs(NULL)
#if FUTURE_ENABLE_MULTITHREADED
	,m_threads(NULL)
#endif
#if FUTURE_PROFILE_THREAD_POOL
	 ,m_totalJobs(0),
	  m_threadTime(0.f),
	  m_jobTime(0.f)
#endif
{		
	FUTURE_ASSERT(ms_instance == NULL);
	ms_instance = this;
}

FutureThreadPool::~FutureThreadPool()
{
	ClearJobQueue();
#if FUTURE_ENABLE_MULTITHREADED
	for(FutureWorkerThread * thread = m_threads; thread;)
	{
		FutureWorkerThread * next = thread->m_next;
		thread->Release();
		delete thread;
		thread = next;
	}
#endif
	ms_instance = NULL;
}

// Returns the id of the newly added job
u32	FutureThreadPool::AddJob(FutureThreadJob * job)
{
	if(job->m_state != FutureThreadJob::JobState_Created &&
		job->m_state != FutureThreadJob::JobState_Finished)
	{
		return -1;
	}
	
#if FUTURE_ENABLE_MULTITHREADED
	if(!m_threads)
	{
		SetNumThreads(1);
	}
#endif

	Lock();
	job->Lock();
#if FUTURE_PROFILE_THREAD_POOL
	f32 startTime = FutureTimer::CurrentTime();
	job->m_timeAdded = startTime;
#endif
	job->m_state = FutureThreadJob::JobState_ToBeAdded;
	job->m_id = m_totalJobs;
	job->Unlock();
	++m_totalJobs;

	if(m_jobs == NULL)
	{
		m_jobs = job;
		job->Lock();
		job->m_next = NULL;
		job->m_state = FutureThreadJob::JobState_InQueue;
		job->Unlock();
#if FUTURE_PROFILE_THREAD_POOL
		f32 time = FutureTimer::TimeSince(startTime);
		m_threadTime += time;
#endif
		Unlock();
		return job->m_id;
	}
	FutureThreadJob * last = NULL;
	bool added = false;
	for(FutureThreadJob * j = m_jobs; j; j = j->m_next)
	{
		if(j->GetPriority() < job->GetPriority())
		{
			added = true;
			job->Lock();
			job->m_next = j;
			if(last)
			{
				last->m_next = job;
			}
			else
			{
				m_jobs = job;
			}
			job->m_state = FutureThreadJob::JobState_InQueue;
			job->Unlock();
			break;
		}
		last = j;
	}
	if(!added)
	{
		job->Lock();
		if(last)
		{
			last->m_next = job;
			job->m_next = NULL;
		}
		else
		{
			job->m_next = m_jobs;
			m_jobs = job;
		}
		job->m_state = FutureThreadJob::JobState_InQueue;
		job->Unlock();
	}
#if FUTURE_PROFILE_THREAD_POOL
	f32 time = FutureTimer::TimeSince(startTime);
	m_threadTime += time;
#endif
	Unlock();
	return job->m_id;
}

u32	FutureThreadPool::AddJobAtPriority(FutureThreadJob * job, FutureThreadJob::FutureThreadJobPriority priority)
{
	job->SetPriority(priority);
	return AddJob(job);
}

// Removes all jobs from the queue, jobs currently executing will not be stopped
void FutureThreadPool::ClearJobQueue()
{
	Lock();
	for(FutureThreadJob * j = m_jobs; j;)
	{
		FutureThreadJob * next = j->m_next;
		delete j;
		j = next;
	}
	m_jobs = NULL;
	Unlock();
}

// Gets the job with the provided id
FutureThreadJob * FutureThreadPool::GetJob(u32 id)
{
	Lock();
	for(FutureThreadJob * j = m_jobs; j; j = j->m_next)
	{
		if(j->m_id == id)
		{
			Unlock();
			return j;
		}
	}
	Unlock();
	return NULL;
}
// returns the number of jobs in the queue
u32	FutureThreadPool::ActiveJobs()
{
	Lock();
	u32 count = 0;
	for(FutureThreadJob * j = m_jobs; j; j = j->m_next)
	{
		++count;
	}
	Unlock();
	return count;
}

// Checks if there are any active jobs
bool FutureThreadPool::IsProcessing()
{
	Lock();
	if(m_jobs)
	{
		Unlock();
		return true;
	}
#if FUTURE_ENABLE_MULTITHREADED
	for(FutureWorkerThread * thread = m_threads; thread; thread = thread->m_next)
	{
		if(!thread->m_idle)
		{
			Unlock();
			return true;
		}
	}
#endif
	Unlock();
	return false;
}

// Waits until the job queue is empty and all jobs are finished before returning
// In a single threaded environment, this must be called before any jobs are executed
void FutureThreadPool::WaitForCompletion(f32 secondsTimeOut)
{
	f32 startTime = FutureTimer::CurrentTime();
	while(IsProcessing() && (secondsTimeOut <= 0 || FutureTimer::TimeSince(startTime) < secondsTimeOut))
	{
		FutureThreadJob * job = GetNextJob();
		if(job)
		{
			job->Execute(NULL);
			JobFinished(job);
		}
		else
		{
			Sleep(5);
		}
	}

#if FUTURE_PROFILE_THREAD_POOL
	f32 time = FutureTimer::TimeSince(startTime);
	Lock();
	m_threadTime += time;
	Unlock();
#endif
}

void FutureThreadPool::WaitForCompletion(u32 millisTimeOut)
{
	WaitForCompletion((f32)millisTimeOut * 1000.f);
}

// functions for getting and setting the number of active threads
u32	FutureThreadPool::GetNumThreads()
{
#if FUTURE_ENABLE_MULTITHREADED
	Lock();
	u32 count = 0;
	for(FutureWorkerThread * thread = m_threads; thread; thread = thread->m_next)
	{
		++count;
	}
	Unlock();
	return count;
#else
	return 0;
#endif
}
void FutureThreadPool::SetNumThreads(u32 threads)
{
#if FUTURE_ENABLE_MULTITHREADED
#if FUTURE_PROFILE_THREAD_POOL
	f32 startTime = FutureTimer::CurrentTime();
#endif
	u32 count = GetNumThreads();
	while(count < threads)
	{
		FutureWorkerThread * thread = new FutureWorkerThread();
		FutureResult result = thread->Start(NULL);
		if(result == FR_OK)
		{
			Lock();
			thread->m_next = m_threads;
			m_threads = thread;
			++count;
			Unlock();
		}
		else
		{
			return;
		}
	}
	while(count > threads)
	{
		Lock();
		FutureWorkerThread * thread = m_threads;
		m_threads = m_threads->m_next;
		--count;
		Unlock();
		thread->Release();
		delete thread;
	}
#if FUTURE_PROFILE_THREAD_POOL
	f32 time = FutureTimer::TimeSince(startTime);
	Lock();
	m_threadTime += time;
	Unlock();
#endif

#endif
}

// Profiling information
u32	FutureThreadPool::TotalJobsExecuted()
{
	return m_totalJobs;
}
f32	FutureThreadPool::AverageWaitTime()
{
#if FUTURE_PROFILE_THREAD_POOL
	return m_waitTime / (f32)m_totalJobs;
#endif
}
f32	FutureThreadPool::TimeOnMainThread()
{
#if FUTURE_PROFILE_THREAD_POOL
	return m_threadTime;
#endif
}
f32	FutureThreadPool::TimeSpentExecutingJobs()
{
#if FUTURE_PROFILE_THREAD_POOL
	return m_jobTime;
#endif
}

FutureThreadJob *	FutureThreadPool::GetNextJob()
{
#if FUTURE_PROFILE_THREAD_POOL
	f32 startTime = FutureTimer::CurrentTime();
#endif
	Lock();
	FutureThreadJob * job = m_jobs;
	if(job)
	{
		job->Lock();
#if FUTURE_PROFILE_THREAD_POOL
		job->m_timeStarted = startTime;
		m_waitTime += job->m_timeAdded - job->m_timeStarted;
#endif
		job->m_state = FutureThreadJob::JobState_Executing;
		m_jobs = m_jobs->m_next;
	}
#if FUTURE_PROFILE_THREAD_POOL
	f32 time = FutureTimer::TimeSince(startTime);
	m_threadTime += time;
#endif
	Unlock();
	return job;
}

void FutureThreadPool::JobFinished(FutureThreadJob * job)
{
#if FUTURE_PROFILE_THREAD_POOL
	f32 startTime = FutureTimer::CurrentTime();
#endif
	Lock();
	if(job)
	{
		job->Lock();
#if FUTURE_PROFILE_THREAD_POOL
		job->m_timeCompleted = startTime;
		m_jobTime += job->m_timeStarted - job->m_timeCompleted;
#endif
		job->m_state = FutureThreadJob::JobState_Finished;
		if(job->m_autoDelete)
		{
			delete job;
		}
		else
		{
			job->Unlock();
		}
	}
#if FUTURE_PROFILE_THREAD_POOL
	f32 time = FutureTimer::TimeSince(startTime);
	m_threadTime += time;
#endif
	Unlock();
}
