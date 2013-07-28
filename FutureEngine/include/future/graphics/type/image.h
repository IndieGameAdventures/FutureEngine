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

#ifndef FUTURE_GRAPHICS_DIRECTX_IMAGE_H
#define FUTURE_GRAPHICS_DIRECTX_IMAGE_H

#include <future/core/type/type.h>
#include <future/graphics/directx/dxtype.h>
#include <future/graphics/type/image.h>

class FutureDXImage : public IFutureImage
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureDXImage);

	FutureDXImage();
	virtual ~FutureDXImage();

	virtual void				Release();

	virtual f32					Height();
	virtual f32					Width();

	virtual bool				RawData(void ** data);

	virtual FutureDataFormat	PixelFormat();
	virtual void				ChangePixelFormat(FutureDataFormat format);
	
	virtual bool				Load(u32 resource, FutureDataFormat format = FutureDataFormat_RGBA_U8);
	virtual bool				Load(string file, FutureDataFormat format = FutureDataFormat_RGBA_U8);
	virtual bool				Load(void * file, FutureDataFormat inFormat, FutureDataFormat outFormat = FutureDataFormat_RGBA_U8);

	virtual bool				IsLoaded();

	virtual void				Unload();
	
	virtual IFutureImage *		Instance();
	virtual IFutureImage *		Clone();

protected:

	void *		m_data;
};

#endif