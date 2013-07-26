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
*	Implementation of FutureSystemBase
*/

#include <future/core/system/systemcontroller.h>
#include <future/core/system/system.h>
#include <future/core/utils/timer/timer.h>

FutureSystemBase::FutureSystemBase()
	: m_needsPreSync(false),
	  m_needsUpdate(false),
	  m_needsPostSync(false),
	  m_systemTime(0.f),
	  m_systemType(FutureSystemType_Custom),
	  m_isSystemInSync(false),
	  m_isSystemActive(false),
	  m_isSystemRunning(false)
{}

FutureSystemBase::~FutureSystemBase()
{
	FUTURE_ASSERT(!m_isSystemActive && !m_isSystemRunning);
}

void		FutureSystemBase::SetNeedsPreSync(bool needs)
{
	m_needsPreSync = needs; 
}
bool		FutureSystemBase::GetNeedsPreSync()
{
	return m_needsPreSync; 
}

void		FutureSystemBase::SetNeedsUpdate(bool needs)
{
	m_needsUpdate = needs; 
}
bool		FutureSystemBase::GetNeedsUpdate()
{
	return m_needsUpdate; 
}

void		FutureSystemBase::SetNeedsPostSync(bool needs)
{
	m_needsPostSync = needs; 
}
bool		FutureSystemBase::GetNeedsPostSync()
{
	return m_needsPostSync; 
}

FutureSystemType	FutureSystemBase::GetSystemType()
{
	return m_systemType;
}
bool				FutureSystemBase::IsSystemActive()
{
	return m_isSystemActive;
}
bool				FutureSystemBase::IsSystemInSync()
{
	return m_isSystemInSync;
}
bool				FutureSystemBase::IsSystemRunning()
{
	return m_isSystemRunning;
}

void				FutureSystemBase::PreSyncSystem()
{
	FUTURE_ASSERT(!IsSystemRunning() && IsSystemActive() && GetNeedsPreSync());
	f32 delta = FutureTimer::TimeSince(m_systemTime);
	m_isSystemRunning = true;
	OnPreSyncSystem(delta);
	m_isSystemRunning = false;
}
void				FutureSystemBase::UpdateSystem()
{
	FUTURE_ASSERT(!IsSystemRunning() && IsSystemActive() && GetNeedsUpdate());
	f32 delta = FutureTimer::TimeSince(m_systemTime);
	m_isSystemRunning = true;
	OnUpdateSystem(delta);
	m_isSystemRunning = false;
}
void				FutureSystemBase::PostSyncSystem()
{
	FUTURE_ASSERT(!IsSystemRunning() && IsSystemActive() && GetNeedsPostSync());
	f32 delta = FutureTimer::TimeSince(m_systemTime);
	m_isSystemRunning = true;
	OnPostSyncSystem(delta);
	m_isSystemRunning = false;
	m_systemTime = FutureTimer::CurrentTime();
}

void		FutureSystemBase::StartSystem()
{
	FUTURE_ASSERT(!IsSystemActive());
	m_isSystemActive = true;
	m_systemTime = FutureTimer::CurrentTime();
}
void		FutureSystemBase::ShutdownSystem()
{
	FUTURE_ASSERT(IsSystemActive());
	m_isSystemActive = false;
}
