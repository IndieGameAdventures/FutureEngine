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
*	A job is something to be executed by a thread. Jobs are added to
*	the ThreaPool JobQueue where they will be given to the next available
*	thread. Jobs with higher priority will be executed first.
*
*/

#ifndef FUTURE_CORE_THREAD_JOB_H
#define FUTURE_CORE_THREAD_JOB_H

#include <future/core/type/type.h>
#include <future/core/object/threadsafeobject.h>

class IFutureThread;
class FutureThreadPool;

class FutureThreadJob : public FutureThreadSafeObject
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureThreadJob);

	// Enum to determine the job's priority. Priority can be any u32 but
	// these are the suggested values.
	// Idle will only execute when there is a free thread with nothing else to do
	// Critical will execute on the next available thread
	enum FutureThreadJobPriority
	{
		JobPriority_Idle		= 0x00000,
		JobPriority_VeryLow		= 0x00010,
		JobPriority_Low			= 0x00020,
		JobPriority_Normal		= 0x00100,
		JobPriority_High		= 0x01000,
		JobPriority_VeryHigh	= 0x02000,
		JobPriority_Critical	= 0x10000,
	};
	
	// Job State. The state is changed internally and is useful for
	// tracking jobs and debugging
	enum FutureThreadJobState
	{
		JobState_Created,
		JobState_ToBeAdded,
		JobState_InQueue,
		JobState_Executing,
		JobState_Finished,
	};

	typedef void (*JobFunction)(void*); // Prototype for the function this job should call
	typedef void (*FinishedCallbackFunction)(void*); // Prototype for this this job's callback function

	// Constructors
	FutureThreadJob();
	FutureThreadJob(JobFunction function, void * data = NULL, FutureThreadJobPriority priority = JobPriority_Normal);
	FutureThreadJob(const FutureThreadJob& job);
	
	virtual ~FutureThreadJob();

	// Returns the job's state
	FutureThreadJobState	GetState();

	/* Note that all set functions must be called before adding this job to the
	*  ThreadPool. Set Functions will assert if called when state != created
	*/

	// Gets or sets the job's priority. Higher priority jobs are performed first
	FutureThreadJobPriority	GetPriority();
	void					SetPriority(FutureThreadJobPriority priority);

	// The data to be sent to the job function
	void *					GetData();
	void					SetData(void * data);

	// Set the functions this job should call
	void					SetJobFunction(JobFunction function);
	void					SetOnFinishedCallback(FinishedCallbackFunction callback);

	// sets if this job should automatically be deleted when it has finished;
	void					SetAutoDelete(bool autoDelete);

	// The job's id, only valid after being added to the ThreadPool
	u32						GetId();

	// The thread that is executing this job, only valid during state = executing
	IFutureThread *			GetThread();

protected:
	friend class FutureWorkerThread;
	friend class FutureThreadPool;

	// executes this job
	void		Execute(IFutureThread * thread);

	FutureThreadJobState	m_state;
	IFutureThread *			m_thread;
	u32						m_id;
	FutureThreadJobPriority	m_priority;
	bool					m_autoDelete;

	// keeps track of where this job is in the job queue
	// Much cheaper than using a FutureLinkedList
	FutureThreadJob *		m_next;

	f32						m_timeAdded;
	f32						m_timeStarted;
	f32						m_timeCompleted;

private:
	JobFunction					m_function;
	FinishedCallbackFunction	m_onFinished;
	void *						m_data;
	
};

#endif