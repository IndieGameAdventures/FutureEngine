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
*	Implementation of FutureThreadJob
*
*/
#include <future/core/thread/pool/job.h>

// Constructors
FutureThreadJob::FutureThreadJob()
	: m_state(FutureThreadJob::JobState_Created),
	  m_thread(NULL),
	  m_id(-1),
	  m_priority(FutureThreadJob::JobPriority_Normal),
	  m_autoDelete(true),
	  m_next(NULL),
	  m_function(NULL),
	  m_onFinished(NULL),
	  m_data(NULL)
#if FUTURE_PROFILE_THREAD_POOL
	 ,m_timeAdded(0),
	  m_timeStarted(0),
	  m_timeCompleted(0)
#endif
{}

FutureThreadJob::FutureThreadJob(JobFunction function, void * data, FutureThreadJobPriority priority)
	: m_state(FutureThreadJob::JobState_Created),
	  m_thread(NULL),
	  m_id(-1),
	  m_priority(priority),
	  m_autoDelete(true),
	  m_next(NULL),
	  m_function(function),
	  m_onFinished(NULL),
	  m_data(data)
#if FUTURE_PROFILE_THREAD_POOL
	 ,m_timeAdded(0),
	  m_timeStarted(0),
	  m_timeCompleted(0)
#endif
{}

FutureThreadJob::FutureThreadJob(const FutureThreadJob& job)
	: m_state(FutureThreadJob::JobState_Created),
	  m_thread(NULL),
	  m_id(-1),
	  m_priority(job.m_priority),
	  m_autoDelete(job.m_autoDelete),
	  m_next(NULL),
	  m_function(job.m_function),
	  m_onFinished(job.m_onFinished),
	  m_data(job.m_data)
#if FUTURE_PROFILE_THREAD_POOL
	 ,m_timeAdded(0),
	  m_timeStarted(0),
	  m_timeCompleted(0)
#endif
{}
	
FutureThreadJob::~FutureThreadJob()
{}

// Returns the job's state
FutureThreadJob::FutureThreadJobState FutureThreadJob::GetState()
{
	return m_state;
}

// Gets or sets the job's priority. Higher priority jobs are performed first
FutureThreadJob::FutureThreadJobPriority FutureThreadJob::GetPriority()
{
	return m_priority;
}
void FutureThreadJob::SetPriority(FutureThreadJobPriority priority)
{
	FUTURE_ASSERT(	m_state == FutureThreadJob::JobState_Created ||
					m_state != FutureThreadJob::JobState_Finished);

	m_priority = priority;
}

// The data to be sent to the job function
void * FutureThreadJob::GetData()
{
	return m_data;
}
void FutureThreadJob::SetData(void * data)
{
	FUTURE_ASSERT(	m_state == FutureThreadJob::JobState_Created ||
					m_state != FutureThreadJob::JobState_Finished);

	m_data = data;
}

// Set the functions this job should call
void FutureThreadJob::SetJobFunction(JobFunction function)
{
	FUTURE_ASSERT(	m_state == FutureThreadJob::JobState_Created ||
					m_state != FutureThreadJob::JobState_Finished);

	m_function = function;
}
void FutureThreadJob::SetOnFinishedCallback(FinishedCallbackFunction callback)
{
	FUTURE_ASSERT(	m_state == FutureThreadJob::JobState_Created ||
					m_state != FutureThreadJob::JobState_Finished);

	m_onFinished = callback;
}

void  FutureThreadJob::SetAutoDelete(bool autoDelete)
{
	m_autoDelete = autoDelete;
}

// The job's id, only valid after being added to the ThreadPool
u32 FutureThreadJob::GetId()
{
	return m_id;
}

// The thread that is executing this job, only valid during state = executing
IFutureThread * FutureThreadJob::GetThread()
{
	return m_thread;
}

// executes this job
void FutureThreadJob::Execute(IFutureThread * thread)
{
	m_thread = thread;
	if(m_function)
	{
		m_function(m_data);
	}
	if(m_onFinished)
	{
		m_onFinished(m_data);
	}
}
