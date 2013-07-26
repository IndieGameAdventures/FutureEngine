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
*	The main game system, this handles start up and shut down of the entire engine
*/

#ifndef FUTURE_CORE_SYSTEM_CONTROLLER_H
#define FUTURE_CORE_SYSTEM_CONTROLLER_H

#include <future/core/debug/debug.h>
#include <future/core/system/system.h>
#include <future/core/utils/container/array.h>

class FutureSystemController
{
public:

	void	Initialize();
	void	Shutdown();

	void	PreSynchronizeAll();
	void	PreSynchronizeOne(FutureSystemType type);
	void	PreSynchronizeCore();
	void	PreSynchronizeCustom();

	void	UpdateAll();
	void	UpdateOne(FutureSystemType type);
	void	UpdateCore();
	void	UpdateCustom();

	void	PostSynchronizeAll();
	void	PostSynchronizeOne(FutureSystemType type);
	void	PostSynchronizeCore();
	void	PostSynchronizeCustom();

	void	SetCoreSystem(FutureSystemType type, FutureSystemBase * system);
	bool	HasCoreSystem(FutureSystemType);

	u32		NumCustomSystems();
	void	AddCustomSystem(FutureSystemBase * system);

protected:
	friend class FutureApplication;

	FutureSystemController();
	~FutureSystemController();

	FutureSystemBase *				m_systems[FutureSystemType_Max];
	FutureArray<FutureSystemBase*>	m_customSystems;

	bool							m_isInitialized;
};


#endif