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

#ifndef FUTURE_CORE_SYSTEM_GRAPHICS_WINDOW_H
#define FUTURE_CORE_SYSTEM_GRAPHICS_WINDOW_H

#include <future/core/type/type.h>

struct FutureWindowInfo
{
    u32         m_width;
    u32         m_height;
    string      m_name;
    bool        m_fullScreen;

    f32			m_dpiX;
    f32			m_dpiY;
};

class IFutureWindow : public FutureManagedObject
{
public:
	virtual ~IFutureWindow(){}
	
	virtual void CreateWindow(const FutureWindowInfo & info) = 0;
    virtual void DestroyWindow();
    
	virtual void GetInfo(FutureWindowInfo & info) = 0;
};

#endif