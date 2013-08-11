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

#include <future/graphics/type/texture.h>
#include <future/graphics/directx/dxtype.h>

#ifndef FUTURE_PLATFORM_WINDOWS
#	error This file must only be included on Windows platforms
#endif

class FutureTexture : public IFutureTexture
{
public:
	static DXGI_FORMAT	FutureFormatToDXFormat(FutureDataFormat format);


	FUTURE_DECLARE_MEMORY_OPERATORS(FutureTexture);

	FutureTexture();
	virtual ~FutureTexture();

    virtual bool                Map(FutureTextureData * dataOut, u32 subresource = 0);
	virtual bool                IsMapped();
	virtual void                UnMap();
    
	virtual bool				UpdateSubresource(const FutureTextureData * data, u32 subresource = 0); 

    virtual void                Release();
    
	virtual u32					Height();
	virtual u32					Weight();
	virtual u32					Depth();

	virtual u8					MipLevels();
	
	virtual const FutureTextureInfo *	GetInfo();

protected:
	friend class FutureGraphicsDevice;
	friend class FutureShader;

	union
	{
		ID3D11Texture1D *			m_texture1d;
		ID3D11Texture2D *			m_texture2d;
		ID3D11Texture3D *			m_texture3d;
		ID3D11Resource *			m_resource;
	};
	ID3D11ShaderResourceView *	m_SRView;
	ID3D11RenderTargetView *	m_RTView;
	ID3D11DepthStencilView *	m_DSView;

	ID3D11DeviceContext *		m_context;
	ID3D11Device *				m_device;

	FutureTextureInfo			m_info;

	bool						m_isLocked;
	u32							m_mappedResource;

	bool						m_mipsCreated;
	
	bool CreateTexture(const FutureTextureInfo * info, const FutureTextureData * data, ID3D11Device * device, ID3D11DeviceContext * context);
	
private:
	bool CreateAsTexture1D(const FutureTextureInfo * info, const FutureTextureData * data, u32 bind, u32 flags);
	bool CreateAsTexture2D(const FutureTextureInfo * info, const FutureTextureData * data, u32 bind, u32 flags);
	bool CreateAsTexture3D(const FutureTextureInfo * info, const FutureTextureData * data, u32 bind, u32 flags);
	bool CreateAsTextureCube(const FutureTextureInfo * info, const FutureTextureData * data, u32 bind, u32 flags);
	
	bool CreateRenderTargetView(const FutureTextureInfo * info);
	bool CreateDepthStencilView(const FutureTextureInfo * info);
	bool CreateShaderResourceView(const FutureTextureInfo * info);

	bool CreateMips(const FutureTextureInfo * info);
};
#endif