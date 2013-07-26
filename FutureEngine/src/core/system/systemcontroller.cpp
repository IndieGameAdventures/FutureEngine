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
*	Implementation of FutureSystemController
*/

#include <future/core/system/systemcontroller.h>
#include <future/core/thread/pool/job.h>
#include <future/core/thread/pool/threadpool.h>

void FutureSystemControllerUpdateHandler(void* data)
{
	FutureSystemBase * system = reinterpret_cast<FutureSystemBase*>(data);
	if(system == NULL || !system->GetNeedsUpdate())
	{
		return;
	}	
	system->UpdateSystem();
}

void	FutureSystemController::Initialize()
{
	FUTURE_ASSERT(!m_isInitialized);

	for(u32 i = 0; i < FutureSystemType_Max; ++i)
	{
		if(m_systems[i] != NULL)
		{
			m_systems[i]->StartSystem();
		}
	}
	for(u32 i = 0; i < m_customSystems.Size(); ++i)
	{
		m_customSystems[i]->StartSystem();
	}
	m_isInitialized = true;
}
void	FutureSystemController::Shutdown()
{
	FUTURE_ASSERT(m_isInitialized);

	for(u32 i = 0; i < FutureSystemType_Max; ++i)
	{
		if(m_systems[i] != NULL)
		{
			m_systems[i]->ShutdownSystem();
			delete m_systems[i];
			m_systems[i] = NULL;
		}
	}
	for(u32 i = 0; i < m_customSystems.Size(); ++i)
	{
		m_customSystems[i]->ShutdownSystem();
	}
	m_customSystems.Clear();

	m_isInitialized = false;
}

void	FutureSystemController::PreSynchronizeAll()
{
	PreSynchronizeCore();
	PreSynchronizeCustom();
}

void	FutureSystemController::PreSynchronizeOne(FutureSystemType type)
{
	if(type == FutureSystemType_Custom)
	{
		PreSynchronizeCustom();
	}

	FutureSystemBase * system = m_systems[type];
	if(system == NULL)
	{
		return;
	}
	if(!system->GetNeedsPreSync())
	{
		return;
	}

	system->PreSyncSystem();
}
void	FutureSystemController::PreSynchronizeCore()
{
	for(u32 i = 0; i < FutureSystemType_Max; ++i)
	{
		FutureSystemBase * system = m_systems[i];
		if(system == NULL)
		{
			return;
		}
		if(!system->GetNeedsPreSync())
		{
			return;
		}

		system->PreSyncSystem();
	}
}
void	FutureSystemController::PreSynchronizeCustom()
{
	for(u32 i = 0; i < m_customSystems.Size(); ++i)
	{
		FutureSystemBase * system = m_customSystems[i];
		if(system == NULL)
		{
			return;
		}
		if(!system->GetNeedsPreSync())
		{
			return;
		}

		system->PreSyncSystem();
	}
}

void	FutureSystemController::UpdateAll()
{
	UpdateCore();
	UpdateCustom();
}
void	FutureSystemController::UpdateOne(FutureSystemType type)
{
	if(type == FutureSystemType_Custom)
	{
		UpdateCustom();
	}

	FutureSystemBase * system = m_systems[type];
	if(system == NULL)
	{
		return;
	}
	if(!system->GetNeedsUpdate())
	{
		return;
	}

	FutureThreadJob * job = new FutureThreadJob(FutureSystemControllerUpdateHandler, system);
	FutureThreadPool::GetInstance()->AddJob(job);
}
void	FutureSystemController::UpdateCore()
{
	for(u32 i = 0; i < FutureSystemType_Max; ++i)
	{
		FutureSystemBase * system = m_systems[i];
		if(system == NULL)
		{
			return;
		}
		if(!system->GetNeedsUpdate())
		{
			return;
		}

		FutureThreadJob * job = new FutureThreadJob(FutureSystemControllerUpdateHandler, system);
		FutureThreadPool::GetInstance()->AddJob(job);
	}
}
void	FutureSystemController::UpdateCustom()
{
	for(u32 i = 0; i < m_customSystems.Size(); ++i)
	{
		FutureSystemBase * system = m_customSystems[i];
		if(system == NULL)
		{
			return;
		}
		if(!system->GetNeedsUpdate())
		{
			return;
		}

		FutureThreadJob * job = new FutureThreadJob(FutureSystemControllerUpdateHandler, system);
		FutureThreadPool::GetInstance()->AddJob(job);
	}
}

void	FutureSystemController::PostSynchronizeAll()
{
	PostSynchronizeCore();
	PostSynchronizeCustom();
}
void	FutureSystemController::PostSynchronizeOne(FutureSystemType type)
{
	if(type == FutureSystemType_Custom)
	{
		PostSynchronizeCustom();
	}

	FutureSystemBase * system = m_systems[type];
	if(system == NULL)
	{
		return;
	}
	if(!system->GetNeedsPostSync())
	{
		return;
	}

	system->PostSyncSystem();
}
void	FutureSystemController::PostSynchronizeCore()
{
	for(u32 i = 0; i < FutureSystemType_Max; ++i)
	{
		FutureSystemBase * system = m_systems[i];
		if(system == NULL)
		{
			return;
		}
		if(!system->GetNeedsPostSync())
		{
			return;
		}

		system->PostSyncSystem();
	}
}
void	FutureSystemController::PostSynchronizeCustom()
{
	for(u32 i = 0; i < m_customSystems.Size(); ++i)
	{
		FutureSystemBase * system = m_customSystems[i];
		if(system == NULL)
		{
			return;
		}
		if(!system->GetNeedsPostSync())
		{
			return;
		}

		system->PostSyncSystem();
	}
}

void	FutureSystemController::SetCoreSystem(FutureSystemType type, FutureSystemBase * system)
{
	if(type == FutureSystemType_Custom)
	{
		AddCustomSystem(system);
		return;
	}

	FUTURE_ASSERT(system->GetSystemType() != type);

	if(m_systems[type] != NULL)
	{
		if(m_isInitialized)
		{
			m_systems[type]->ShutdownSystem();
		}
		delete m_systems[type];
		m_systems[type] = NULL;
	}

	m_systems[type] = system;

	if(m_isInitialized)
	{
		m_systems[type]->StartSystem();
	}
}
bool	FutureSystemController::HasCoreSystem(FutureSystemType type)
{
	return m_systems[type] != NULL;
}

u32		FutureSystemController::NumCustomSystems()
{
	return m_customSystems.Size();
}
void	FutureSystemController::AddCustomSystem(FutureSystemBase * system)
{	
	FUTURE_ASSERT(system->GetSystemType() != FutureSystemType_Custom);

	for(u32 i = 0; i < m_customSystems.Size(); ++i)
	{
		if(m_customSystems[i] == system)
		{
			if(m_isInitialized)
			{
				m_customSystems[i]->ShutdownSystem();
				m_customSystems[i]->StartSystem();
			}
			return;
		}
	}

	m_customSystems.Add(system);
	
	if(m_isInitialized)
	{
		system->StartSystem();
	}
}

FutureSystemController::FutureSystemController()
	: m_systems(),
	  m_customSystems(),
	  m_isInitialized(false)
{
}
FutureSystemController::~FutureSystemController()
{
	if(m_isInitialized)
	{
		Shutdown();
	}
}
