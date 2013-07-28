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
*	Types, Structs, and Enums used by the graphics system
*/

#ifndef FUTURE_GRAPHICS_TYPE_DIRECTX_H
#define FUTURE_GRAPHICS_TYPE_DIRECTX_H

#include <future/core/type/type.h>
#include <future/graphics/type/type.h>

#if !FUTURE_PLATFORM_WINDOWS
#	error This file should only be included on Windows machines
#endif

#include <windows.h>
#include <objidl.h>
#include <wincodec.h>
#include <d3dcommon.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <d3d11_1.h>

#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3dcompiler.lib" )

#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )
#pragma comment( lib, "Gdiplus.lib" )
#pragma comment( lib, "Windowscodecs.lib" )


#endif