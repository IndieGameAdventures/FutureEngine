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

#ifndef FUTURE_CORE_THREAD_THREADPOOL_H
#define FUTURE_CORE_THREAD_THREADPOOL_H

#include <future/core/object/threadsafeobject.h>
#include <future/core/object/singleton.h>
#include <future/core/thread/thread/thread.h>
#include <future/core/thread/pool/job.h>

#undef AddJob
#undef GetJob

// TODO: add multiple job queues so threads don't have to wait on each other to get a new job
class FutureWorkerThread;

class FutureThreadPool : public FutureThreadSafeObject
{
private:
	static FutureThreadPool * ms_instance;

public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureThreadPool);

	inline static FutureThreadPool* GetInstance()
	{
		return ms_instance;
	}

	inline static void CreateInstance()
	{
		FUTURE_ASSERT(ms_instance == NULL);
		ms_instance = new FutureThreadPool();
	}

	inline static void DestroyInstance()
	{
		FUTURE_ASSERT(ms_instance != NULL);
		delete ms_instance;
		ms_instance = NULL;
	}

	// Returns the id of the newly added job
	u32					AddJob(FutureThreadJob * job);
	u32					AddJobAtPriority(FutureThreadJob * job, FutureThreadJob::FutureThreadJobPriority priority);

	// Removes all jobs from the queue, jobs currently executing will not be stopped
	void				ClearJobQueue();

	// Gets the job with the provided id
	FutureThreadJob *	GetJob(u32 id);
	// returns the number of jobs in the queue
	u32					ActiveJobs();

	// Checks if there are any active jobs
	bool				IsProcessing();

	// Waits until the job queue is empty and all jobs are finished before returning
	// In a single threaded environment, this must be called before any jobs are executed
	void				WaitForCompletion(f32 secondsTimeOut = -1);
	void				WaitForCompletion(u32 millisTimeOut);

	// functions for getting and setting the number of active threads
	u32					GetNumThreads();
	void				SetNumThreads(u32 thread);

	// Profiling information
	u32					TotalJobsExecuted();
	f32					AverageWaitTime();
	f32					TimeOnMainThread();
	f32					TimeSpentExecutingJobs();

protected:
	friend class FutureWorkerThread;
	friend class FutureSingleton<FutureThreadPool>;

	FutureThreadPool();
	~FutureThreadPool();

	FutureThreadJob *	GetNextJob();
	void				JobFinished(FutureThreadJob * job);

#if FUTURE_ENABLE_MULTITHREADED
	FutureWorkerThread *	m_threads;
#endif
	FutureThreadJob *		m_jobs;
	u32						m_totalJobs;

#if FUTURE_PROFILE_THREAD_POOL
	f32						m_threadTime;
	f32						m_jobTime;
	f32						m_waitTime;
#endif
};

#endif