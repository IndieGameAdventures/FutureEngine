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

#ifndef FUTURE_GRAPHICS_DRIVER_H
#define FUTURE_GRAPHICS_DRIVER_H

#include <future/core/system/system.h>
#include <future/core/system/window.h>
#include <future/graphics/type/type.h>
#include <future/graphics/type/settings.h>
#include <future/graphics/type/texture.h>
#include <future/graphics/type/buffers.h>
#include <future/graphics/type/shader.h>

class FutureGraphicsSystem : public FutureSystemBase
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureGraphicsSystem);

	FutureGraphicsSystem()
		: FutureSystemBase()
	{
		m_systemType = FutureSystemType_Graphics;
	}

	virtual bool			CreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings) = 0;
    virtual bool			RecreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings) = 0;
    virtual void			DestroyDevice() = 0;

	virtual bool			HasDevice() = 0;
	virtual IFutureGraphicsDevice *	GetDevice() = 0;

	virtual	void			GetGraphicsSettings(FutureGraphicsSettings * settings) = 0; 
   
	virtual bool			IsFeatureSupported(FutureDeviceSupport feature) = 0;
	virtual s32				GetDeviceCapability(FutureDeviceCapabilityType feature) = 0;

	virtual IFutureWindow *	Window() = 0;

protected:

	virtual void		OnPreSyncSystem(f32 deltaTime);
	virtual void		OnUpdateSystem(f32 deltaTime);
	virtual void		OnPostSyncSystem(f32 deltaTime);
};

#endif