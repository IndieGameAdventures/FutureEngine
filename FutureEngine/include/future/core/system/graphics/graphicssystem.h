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

#ifndef FUTURE_CORE_SYSTEM_GRAPHICS_H
#define FUTURE_CORE_SYSTEM_GRAPHICS_H

#include <future/core/system/system.h>
#include <future/core/system/graphics/graphicstypes.h>

class IFutureGraphicsSystem : public FutureSystemBase
{
public:
	IFutureGraphicsSystem()
		: FutureSystemBase()
	{
		m_needsUpdate = true;
		m_systemTime = 0;
		m_systemType = FutureSystemType_Graphics;
	}
	
	virtual void CreateWindow(u32 width = 640, u32 height = 480, string windowTitle = L"Future Window") = 0;

	// if width and height are 0, the suggested width and height will be used
	virtual void CreateDevice(bool windowed = true, u32 p_nWidth = 0, u32 p_nHeight = 0) = 0;

	// if force is true, this will not check to make sure all settings are valid before creating a new device
	virtual void CreateDeviceFromSettings(FutureGraphicsSettings * settings, bool force = false ) = 0;

	virtual void FindValidDeviceSettings(FutureGraphicsSettings * out, FutureGraphicsSettings * in ) = 0;

	virtual FutureGraphicsSettings *	GraphicsSettings() = 0; 
	virtual void *						ProgramInstance() = 0;

	virtual FutureWindowSettings *		WindowSettings() = 0
	virtual IFutureWindow				Window() = 0;

	virtual bool						HasDevice() = 0;
	virtual void *						GetDevice() = 0;

	virtual void						AddDeviceCallback(IFutureDeviceCallback * deviceCallback) = 0;
	virtual void						RemoveDeviceCallback(IFutureDeviceCallback * deviceCallback) = 0;
};

#endif