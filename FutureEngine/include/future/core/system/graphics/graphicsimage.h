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
*	A 2d image loaded from a resource.
*/

#ifndef FUTURE_CORE_SYSTEM_GRAPHICS_IMAGE_H
#define FUTURE_CORE_SYSTEM_GRAPHICS_IMAGE_H

#include <future/core/type/type.h>
#include <future/core/object/managedobject.h>

class IFutureImage : public FutureManagedObject
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(IFutureImage);

	IFutureImage();
	virtual ~IFutureImage();

	virtual void				Release();

	virtual f32					Height() = 0;
	virtual f32					Width() = 0;

	virtual bool				RawData(void ** data) = 0;

	virtual FuturePixelFormat	PixelFormat() = 0;
	virtual void				ChangePixelFormat(FuturePixelFormat format) = 0;
	
	virtual bool				Load(u32 resource, FuturePixelFormat format = FuturePixelFormat_R8B8G8A8) = 0;
	virtual bool				Load(string file, FuturePixelFormat format = FuturePixelFormat_R8B8G8A8) = 0;
	virtual bool				Load(void * file, FuturePixelFormat inFormat, FuturePixelFormat outFormat = FuturePixelFormat_R8B8G8A8) = 0;

	virtual bool				IsLoaded() = 0;

	virtual void				Unload() = 0;
};

#endif