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
*	Window class used by Windows 7 and Windows 8 Desktop
*/

#ifndef FUTURE_CORE_SYSTEM_WINDOW_IMPL_H
#define FUTURE_CORE_SYSTEM_WINDOW_IMPL_H

#include <future/core/type/type.h>
#include <future/core/system/window.h>

#if !FUTURE_PLATFORM_WINDOWS
#	error This file should only be included on Windows
#endif

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>

class FutureWindow : public IFutureWindow
{
public:
	FutureWindow();
	virtual ~FutureWindow();
	
	virtual void Create(const FutureWindowInfo & info);
    virtual void Destroy();
    
	virtual void GetInfo(FutureWindowInfo & info);

	void		SetInstance(HINSTANCE inst);
	void		SetWindProc(WNDPROC proc);

	HINSTANCE	GetInstance();
	HWND		GetWindow();

protected:

	FutureWindowInfo	m_info;
	HINSTANCE			m_instance;
	HWND				m_window;
	WNDPROC 			m_proc;
};

#endif