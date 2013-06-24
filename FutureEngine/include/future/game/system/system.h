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

#ifndef FUTURE_GAME_SYSTEM_H
#define FUTURE_GAME_SYSTEM_H

#include <future/core/type/type.h>

enum FutureSystemMessage
{
	Message_None,
	Message_WindowCreated,
	Message_WindowDestroyed,
	Message_WindowsResized,
	
	Message_ForceRedraw,
	Message_ContentRectChanged,

	Message_FocusGained,
	Message_FocusLost,

    Message_ConfigChanged,

	Message_LowMemory,

	Message_AppStart,
	Message_AppStop,
	Message_AppPause,
	Message_AppResume,
	Message_AppDestroy,

	Message_SaveState,

	Message_Max,
};


class FutureGameSystem
{
public:
	static void StartUpAllSystems();
	static void ShutDownAllSystems();

protected:
	FutureGameSystem(){};
	~FutureGameSystem(){};
};

extern void FutureMain();

#endif