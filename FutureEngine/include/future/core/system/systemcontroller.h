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

enum FutureSystemMessage
{
	FutureSystemMessage_None,
	FutureSystemMessage_WindowCreated,
	FutureSystemMessage_WindowDestroyed,
	FutureSystemMessage_WindowsResized,
	
	FutureSystemMessage_ForceRedraw,
	FutureSystemMessage_ContentRectChanged,

	FutureSystemMessage_FocusGained,
	FutureSystemMessage_FocusLost,

    FutureSystemMessage_ConfigChanged,

	FutureSystemMessage_LowMemory,

	FutureSystemMessage_AppStart,
	FutureSystemMessage_AppStop,
	FutureSystemMessage_AppPause,
	FutureSystemMessage_AppResume,
	FutureSystemMessage_AppDestroy,

	FutureSystemMessage_SaveState,

	FutureSystemMessage_Max,
};


class FutureSystemController
{
public:
	inline static FutureSystemController* GetInstance()
	{
		return ms_instance;
	}

	static void CreateInstance()
	{
		FUTURE_ASSERT(ms_instance == NULL);
		ms_instance = new FutureSystemController();
	}

	static void DestroyInstance()
	{
		FUTURE_ASSERT(ms_instance != NULL);
		delete ms_instance;
		ms_instance = NULL;
	}

public:

	void	Initialize();
	void	Shutdown();

	void	RunMainLoop();

	void	SetCoreSystem(FutureSystemType type, FutureSystemBase * system);
	void	AddCustomSystem(FutureSystemBase * system);

protected:
	FutureSystemController();
	~FutureSystemController();

	static FutureSystemController * ms_instance;

	FutureSystemBase m_systems[FutureSystemType_Max];
};

extern void FutureMain();

#endif