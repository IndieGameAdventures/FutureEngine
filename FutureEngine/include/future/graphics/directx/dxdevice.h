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

#ifndef FUTURE_GRAPHICS_DX_SYSTEM_H
#define FUTURE_GRAPHICS_DX_SYSTEM_H

#include <future/core/system/system.h>
#include <future/core/system/window.h>
#include <future/graphics/type/driver.h>
#include <future/graphics/directx/dxtype.h>
#include <future/graphics/directx/dxtexture.h>
#include <future/graphics/directx/dxbuffers.h>
#include <future/graphics/directx/dxshader.h>


class FutureGraphicsDevice : public IFutureGraphicsDevice
{
public:

	virtual bool								HasDevice();
	virtual void *								GetDevice();
   
	virtual bool								IsFeatureSupported(FutureDeviceSupport feature);
	virtual s32									GetDeviceCapability(FutureDeviceCapabilityType feature);
    
    virtual s32									CreateBlendState(const FutureBlendStateInfo * info);
    virtual s32									CreateDepthStencilState(const FutureDepthStencilInfo * info);
    virtual s32									CreateRasterizerState(const FutureRasterizerInfo * info);
    virtual s32									CreateTextureSamplerState(const FutureTextureSamplerInfo * info);
    
    virtual const FutureBlendStateInfo *		GetBlendStateInfo(s32 id);
    virtual const FutureDepthStencilInfo *		GetDepthStencilStateInfo(s32 id);
    virtual const FutureRasterizerInfo *		GetRasterizerStateInfo(s32 id);
    virtual const FutureTextureSamplerInfo *	GetTextureSamplerStateInfo(s32 id);
    
	virtual bool								CreateBuffer(const FutureHardwareBufferInfo * info, 
															 const FutureHardwareBufferData * data, 
															 IFutureHardwareBuffer ** buffer);
    virtual bool								CreateShader(const FutureShaderCreationData * info, 
															IFutureShader ** shader);
    virtual bool								CreateTexture(const FutureTextureInfo * info, 
															  const FutureTextureData * data,
															  IFutureTexture ** texture);
    
    virtual const FutureViewport *				GetViewport();
    virtual bool								SetViewport(const FutureViewport * viewport);
    
    
    virtual bool								ClearDepthStencil(IFutureTexture * depthStencil, f32 depthClear = 0.f, u8 stencilClear = 0);
    virtual bool								ClearDepthBuffer(IFutureTexture * depthStencil, f32 clearValue = 0.f);
    virtual bool								ClearStencil(IFutureTexture * depthStencil, u8 clearValue = 0);
    virtual bool								ClearRenderTarget(IFutureTexture * renderTarget);
    virtual bool								ClearState();
    
    virtual IFutureTexture *					GetRenderTarget();
    virtual bool								SetRenderTarget(IFutureTexture * renderTarget);
    
    virtual IFutureTexture *					GetDepthStencil();
    virtual bool								SetDepthStencil(IFutureTexture * depthStencil);
    
    virtual bool								SetShader(FutureShaderType type, IFutureShader * shader);
    virtual IFutureShader *						GetShader(FutureShaderType type);
    
    virtual bool								SetBlendState(s32 state);
    virtual bool								SetDepthStencilState(s32 state);
    virtual bool								SetRasterizerState(s32 state);
    
    virtual s32									GetBlendState();
    virtual s32									GetDepthStencilState();
    virtual s32									GetRasterizerState();
    
    virtual IFutureHardwareBuffer *				GetVertexBuffer();
    virtual IFutureHardwareBuffer *				GetIndexBuffer();

    virtual bool								SetVertexBuffer(IFutureHardwareBuffer * buffer);
    virtual bool								SetIndexBuffer(IFutureHardwareBuffer * buffer);
    virtual bool								SetPrimitiveType(FuturePrimitiveType primType);

    virtual bool								BeginRender();
    virtual bool								Render();
    virtual bool								EndRender();

protected:
	friend class FutureGraphicsSystem;
	friend class FutureShader;

	FutureGraphicsDevice();
	~FutureGraphicsDevice();

	virtual bool    CreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings);
    virtual bool    RecreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings);
    virtual void    DestroyDevice();


	FutureArray<ID3D11RasterizerState *>	m_rasterStates;
	FutureArray<FutureRasterizerInfo>		m_rasterInfo;
	u32										m_currentRasterState;

	FutureArray<ID3D11DepthStencilState *>	m_depthStencilStates;
	FutureArray<FutureDepthStencilInfo>		m_depthStencilInfo;
	u32										m_currentDepthStencilState;

	FutureArray<ID3D11BlendState *>			m_blendStates;
	FutureArray<FutureBlendStateInfo>		m_blendInfo;
	u32										m_currentBlendState;


	FutureArray<ID3D11SamplerState *>		m_samplerStates;
	FutureArray<FutureTextureSamplerInfo>	m_samplerInfo;
	u32										m_currentSamplerState;

	FutureShader *							m_activeShaders[FutureShaderType_Max];

	FutureHardwareBuffer *					m_vertexBuffer;
	FutureHardwareBuffer *					m_indexBuffer;
	FuturePrimitiveType						m_primitiveType;

	FutureTexture *							m_depthStencil;
	FutureTexture *							m_renderTarget;
	ID3D11Texture2D *						m_backBuffer;
	FutureViewport							m_viewport;
	
	FutureGraphicsSettings					m_settings;

public:

	IDXGIFactory *							m_factory;
	IDXGIAdapter *							m_adapter;
	IDXGIOutput	*							m_output;
	IDXGISwapChain *						m_swapChain;
	ID3D11Device *							m_device;
	ID3D11DeviceContext *					m_deviceContext;

	bool									m_usingVersion1;
	bool									m_usingVersion2;

	u32										m_majorVersion;
	u32										m_minorVersion;
};

#endif