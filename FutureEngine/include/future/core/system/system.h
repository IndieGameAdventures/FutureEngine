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
*	The main game system, this handles start up and shut down of the entire system
*	
*/

#ifndef FUTURE_CORE_SYSTEM_H
#define FUTURE_CORE_SYSTEM_H

#include <future/core/type/type.h>

class FutureSystemController;

enum FutureSystemType
{
	FutureSystemType_AI,
	FutureSystemType_Animation,
	FutureSystemType_Game,
	FutureSystemType_Graphics,
	FutureSystemType_Network,
	FutureSystemType_Particles,
	FutureSystemType_Physics,
	FutureSystemType_Sound,

	FutureSystemType_Custom,

	FutureSystemType_Max,
};

class FutureSystemBase
{
public:
	FutureSystemBase();
	virtual ~FutureSystemBase();
	
	virtual void		SetNeedsUpdate(bool update);
	virtual bool		GetNeedsUpdate();

	FutureSystemType	GetSystemType();
	bool				IsSystemActive();

protected:
	friend class FutureSystemController;

	void			UpdateSystem(f32 time);

	virtual void	StartSystem();
	virtual void	ShutdownSystem();
	
	virtual void	OnUpdateSystem(f32 time);

	bool				m_needsUpdate;
	f32					m_systemTime;
	FutureSystemType	m_systemType;
	bool				m_isSystemActive;
};

#endif