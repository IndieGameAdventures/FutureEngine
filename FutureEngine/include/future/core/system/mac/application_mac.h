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
*	Application class used by Windows 7 and Windows 8 Desktop
*/

#ifndef FUTURE_CORE_SYSTEM_APPLICATION_IMPL_H
#define FUTURE_CORE_SYSTEM_APPLICATION_IMPL_H

#include <future/core/type/type.h>
#include <future/core/system/mac/window_mac.h>
#include <future/core/system/application.h>

#if !FUTURE_PLATFORM_MAC
#	error This file should only be included on Mac
#endif

class FutureApplicationImpl : public FutureApplication
{
public:
	static void CreateInstance();
	static void DestroyInstance();

	FutureApplicationImpl();
	virtual ~FutureApplicationImpl();
	
	virtual void	Initialize();
	virtual void	Shutdown();

	virtual void	RunMainLoop();

	void	UpdateMainLoop();
protected:

	FutureWindow *	m_window;
	bool			m_running;
	void *			m_app;
};

#import <Cocoa/Cocoa.h>

@interface FutureApplicationMac : NSApplication
{
@private
   NSMutableSet *               _viewStorage;
   BOOL                         _isPackaged;
}
 
- (void)runOnce;

@end

#endif