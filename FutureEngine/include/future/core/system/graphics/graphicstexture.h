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
*	A Texture Object Interface. This stores an image that can be used on hardware
*/

#ifndef FUTURE_CORE_SYSTEM_GRAPHICS_TEXTURE_H
#define FUTURE_CORE_SYSTEM_GRAPHICS_TEXTURE_H

#include <future/core/object/managedobject.h>
#include <future/core/system/graphics/graphicstypes.h>
#include <future/core/system/graphics/graphicsimage.h>

enum FutureTextureType
{
	FutureTextureType_1D,
	FutureTextureType_2D,
	FutureTextureType_3D,

	FutureTextureType_1D_Array,
	FutureTextureType_2D_Array,
	FutureTextureType_3D_Array,
	
	FutureTextureType_Cube,
};

enum FutureTextureTarget
{
	FutureTextureTarget_ShaderResource = 0x1,
	FutureTextureTarget_RenderTarget = 0x2,
	FutureTextureTarget_DepthStencil = 0x4,
};

struct FutureTextureInfo
{
	FutureTextureInfo()
		: m_height(512),
		  m_width(512),
		  m_depth(1),
		  m_multisampleCount(1),
		  m_multisampleQuality(1),
		  m_arraySize(1),
		  m_generateMipMap(true),
		  m_mipLevels(6),
		  m_pixelFormat(FuturePixelFormat_RGBA_U8),
		  m_type(FutureTextureType_2D),
		  m_usage(FutureHardwareResourceUsage_Dynamic),
		  m_target(FutureTextureTarget_ShaderResource)
	{}

	u32					m_height;
	u32					m_width;
	u32					m_depth;

	u8					m_multisampleCount;
	u8					m_multisampleQuality;

	u8					m_arraySize;

	bool				m_generateMipMap;
	u32					m_mipLevels;

	FuturePixelFormat			m_pixelFormat;
	FutureTextureType			m_type;
	FutureHardwareResourceUsage	m_usage;
	FutureTextureTarget			m_target;
};


class IFutureTexture : public FutureManagedObject, public IFutureHardwareObject
{
public:
	virtual ~IFutureTexture();

    virtual bool                Map(void ** data, u32 subresource = 0) = 0;
	virtual bool                MapAsImage(IFutureImage ** image, u32 subresource = 0) = 0;
	virtual bool                IsMapped() = 0;
	virtual void                UnMap() = 0;
    
    virtual void                Release() = 0;
    
	virtual u32					Height() = 0;
	virtual u32					Weight() = 0;
	virtual u32					Depth() = 0;

	virtual u8					MipLevels() = 0;

	virtual void				Clear() = 0;

	virtual IFutureTexture *	Clone() = 0;
	virtual IFutureTexture *	Instance() = 0;

	virtual void				GetInfo(FutureTextureInfo & info) = 0;

protected:

	IFutureTexture(){};
};

#endif