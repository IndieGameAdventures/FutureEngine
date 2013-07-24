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

#include <future/core/system/graphics/graphicstypes.h>
#include <future/core/system/graphics/graphicstexture.h>
#include <future/core/system/graphics/graphicssettings.h>
#include <future/core/system/graphics/graphicsbuffers.h>

enum FutureShaderType
{
    FutureShaderType_Vertex,
    FutureShaderType_PreTesslation,
    FutureShaderType_PostTesslation,
    FutureShaderType_Geometry,
    FutureShaderType_Pixel,
    FutureShaderType_Compute,
};

class IFutureShaderEffect : public FutureManagedObject
{
    
};

class IFutureShader : public FutureManagedObject, public IFutureHardwareObject
{
public:

};

#endif