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

#ifndef FUTURE_CORE_SYSTEM_APPLICATION_H
#define FUTURE_CORE_SYSTEM_APPLICATION_H

#include <future/core/debug/debug.h>
#include <future/core/system/systemcontroller.h>
#include <future/core/utils/container/array.h>
#include <future/core/object/eventdispatcher.h>

enum FutureApplicationEventType
{
	FutureApplicationEvent_Unknown					= 0x00000000,
	FutureApplicationEvent_WindowCreated			= 0x00000001,
	FutureApplicationEvent_WindowDestroyed			= 0x00000002,
	FutureApplicationEvent_WindowResized			= 0x00000004,
	
	FutureApplicationEvent_ForceRedraw				= 0x00000008,
	FutureApplicationEvent_ContentRectChanged		= 0x00000010,

	FutureApplicationEvent_FocusGained				= 0x00000020,
	FutureApplicationEvent_FocusLost				= 0x00000040,

    FutureApplicationEvent_ConfigChanged			= 0x00000080,

	FutureApplicationEvent_LowMemory				= 0x00000100,

	FutureApplicationEvent_AppStart					= 0x00000200,
	FutureApplicationEvent_AppStop					= 0x00000400,
	FutureApplicationEvent_AppPause					= 0x00000800,
	FutureApplicationEvent_AppResume				= 0x00001000,
	FutureApplicationEvent_AppDestroy				= 0x00002000,

	FutureApplicationEvent_SaveState				= 0x00004000,
	FutureApplicationEvent_RestoreState				= 0x00008000,

	FutureApplicationEvent_InputTouch				= 0x00010000,
	FutureApplicationEvent_InputMouse				= 0x00020000,
	FutureApplicationEvent_InputKeyboard			= 0x00040000,
	FutureApplicationEvent_InputGesture				= 0x00080000,
	FutureApplicationEvent_SensoreAccelerometer		= 0x00100000,
	FutureApplicationEvent_SensorGyroscope			= 0x00200000,
	FutureApplicationEvent_SensorAmbientLight		= 0x00400000,
	FutureApplicationEvent_SensorProximity			= 0x00800000,


	FutureApplicationEvent_WindowEvent				= 	FutureApplicationEvent_WindowCreated | 
														FutureApplicationEvent_WindowDestroyed |
														FutureApplicationEvent_WindowResized |
														FutureApplicationEvent_ForceRedraw |
														FutureApplicationEvent_WindowResized,

	FutureApplicationEvent_LifeCycleEvent			= 	FutureApplicationEvent_AppStart | 
														FutureApplicationEvent_AppStop |
														FutureApplicationEvent_AppPause |
														FutureApplicationEvent_AppResume |
														FutureApplicationEvent_AppDestroy |
														FutureApplicationEvent_SaveState |
														FutureApplicationEvent_RestoreState,

	FutureApplicationEvent_InputEvent				= 	FutureApplicationEvent_InputTouch | 
														FutureApplicationEvent_InputMouse |
														FutureApplicationEvent_InputKeyboard |
														FutureApplicationEvent_InputGesture,


	FutureApplicationEvent_SensorEvent				= 	FutureApplicationEvent_SensoreAccelerometer | 
														FutureApplicationEvent_SensorGyroscope |
														FutureApplicationEvent_SensorAmbientLight |
														FutureApplicationEvent_SensorProximity,

	FutureApplicationEvent_All = 0xFFFFFFFF,
	FutureApplicationEvent_Max = 25,
};

/*
enum FutureApplicationInputEventType
{
	FutureApplicationEvent_Input_BeginTouch			= 0x00010000,
	FutureApplicationEvent_Input_MoveTouch			= 0x00020000,
	FutureApplicationEvent_Input_HoverTouch			= 0x00040000,
	FutureApplicationEvent_Input_EndTouch			= 0x00080000,

	FutureApplicationEvent_Input_TapTouch,			= 0x00010000,
	FutureApplicationEvent_Input_SwipeTouch,		= 0x00020000,
	FutureApplicationEvent_Input_PinchTouch,		= 0x00040000,
	FutureApplicationEvent_Input_RotationTouch,		= 0x00080000,
	FutureApplicationEvent_Input_PanTouch,			= 0x00100000,

	FutureApplicationEvent_Input_LeftMouseDown,		= 0x00200000,
	FutureApplicationEvent_Input_LeftMouseUp,		= 0x00400000,
	FutureApplicationEvent_Input_LeftMouseClick,	= 0x00800000,

	FutureApplicationEvent_Input_CenterMouseDown,	= 0x01000000,
	FutureApplicationEvent_Input_CenterMouseUp,		= 0x02000000,
	FutureApplicationEvent_Input_CenterMouseClick,	= 0x04000000,

	FutureApplicationEvent_Input_RightMouseDown,	= 0x08000000,
	FutureApplicationEvent_Input_RightMouseUp,		= 0x10000000,
	FutureApplicationEvent_Input_RightMouseClick,	= 0x20000000,

	FutureApplicationEvent_Input_MouseMove,			= 0x40000000,
	FutureApplicationEvent_Input_MouseWheel,		= 0x80000000,

	FutureApplicationEvent_Input_KeyDown,
	FutureApplicationEvent_Input_KeyUp,
	FutureApplicationEvent_Input_KeyPress,s
};
*/


class FutureApplication : public FutureManagedObject
{
public:
	inline static FutureApplication* GetInstance()
	{
		return ms_instance;
	}

public:

	virtual void						Initialize();
	virtual void						Shutdown();

	virtual void						RunMainLoop() = 0;

	virtual FutureSystemController *	GetSystemController();


protected:
	friend class FutureApplicationImpl;

	FutureApplication();
	virtual ~FutureApplication();

	static FutureApplication * ms_instance;

	FutureSystemController * m_systemController;
};

extern void FutureMain();

#endif