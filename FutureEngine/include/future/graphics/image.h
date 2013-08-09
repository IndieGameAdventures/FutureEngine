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

#ifndef FUTURE_GRAPHICS_IMAGE_H
#define FUTURE_GRAPHICS_IMAGE_H

#include <future/core/type/type.h>
#include <future/core/resource/resource.h>

class FutureImage : public FutureResource
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureImage);

	virtual f32					Height();
	virtual f32					Width();

	virtual void *				RawData();

	virtual FutureDataFormat	PixelFormat();
	virtual void				ChangePixelFormat(FutureDataFormat format);
	
	virtual FutureResource *	Instance();
	virtual FutureResource *	Clone();

protected:
	friend class FutureGraphicsSystem;
	friend class FutureResourceManager;
	
	virtual bool				Load(void * data, u32 size, u32 checksum);
    virtual bool				Unload();

	FutureImage();
	virtual ~FutureImage();

	void *		m_data;
};

#endif