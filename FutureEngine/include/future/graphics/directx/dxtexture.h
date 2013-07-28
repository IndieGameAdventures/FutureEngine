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
*	A Texture Class implementation using Windows DirectX
*/

#ifndef FUTURE_GRAPHICS_DIRECTX_TEXTURE_H
#define FUTURE_GRAPHICS_DIRECTX_TEXTURE_H

#include <future/core/object/managedobject.h>
#include <future/graphics/type/texture.h>
#include <future/graphics/directx/dxtexture.h>

#ifndef FUTURE_PLATFORM_WINDOWS
#	error This file must only be included on Windows platforms
#endif

class FutureDXTexture : public IFutureTexture
{
public:

	FutureDXTexture();
	virtual ~FutureDXTexture();

    virtual bool                Map(void ** data, u32 subresource = 0);
	virtual bool                MapAsImage(IFutureImage ** image, u32 subresource = 0);
	virtual bool                IsMapped();
	virtual void                UnMap();
    
    virtual void                Release();
    
	virtual u32					Height();
	virtual u32					Weight();
	virtual u32					Depth();

	virtual u8					MipLevels();

	virtual void				Clear();

	virtual IFutureTexture *	Clone();
	virtual IFutureTexture *	Instance();

	virtual void				GetInfo(FutureTextureInfo & info);


	virtual bool				ApplyToHardware();
	virtual bool				RemoveFromHardware();
	virtual bool				ReapplyToHardware();

	virtual bool				IsAppliedToHardware();

	virtual void				DeviceLost();
	virtual void				DeviceFound();
	virtual void				DevicePreReset();
	virtual void				DeviceReset();
	virtual void				DevicePreChange();
	virtual void				DeviceChange();

protected:
	friend class FutureDXGraphicsSystem;

	ID3D11Texture2D *			m_texture;
	ID3D11ShaderResourceView *	m_SRView;
	ID3D11RenderTargetView *	m_RTView;
	ID3D11DepthStencilView *	m_DSView;

	FutureTextureInfo			m_info;
};
#endif