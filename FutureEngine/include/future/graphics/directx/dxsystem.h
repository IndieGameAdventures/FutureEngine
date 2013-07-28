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
#include <future/graphics/type/system.h>
#include <future/graphics/directx/dxtype.h>
#include <future/graphics/directx/dxtexture.h>
#include <future/graphics/directx/dxbuffers.h>
#include <future/graphics/directx/dxshader.h>


class FutureDXGraphicsSystem : public IFutureGraphicsSystem
{
public:
	FutureDXGraphicsSystem();
	~FutureDXGraphicsSystem();

	virtual bool    CreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings);
    virtual bool    RecreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings);
    virtual void    DestroyDevice();

	virtual bool						HasDevice();
	virtual void *						GetDevice();

	virtual const FutureGraphicsSettings *	GraphicsSettings(); 
   
	virtual bool						IsFeatureSupported(FutureDeviceSupport feature);
	virtual s32							GetDeviceCapability(FutureDeviceCapabilityType feature);

	virtual IFutureWindow *				Window();

	virtual void						AddDeviceCallback(IFutureDeviceCallback * deviceCallback);
	virtual void						RemoveDeviceCallback(IFutureDeviceCallback * deviceCallback);

    
    virtual s32         CreateBlendState(const FutureBlendInfo info);
    virtual s32         CreateDepthStencilState(const FutureDepthStencilInfo info);
    virtual s32         CreateRasterizerState(const FutureRasterizerInfo info);
    virtual s32         CreateTextureSamplerState(const FutureTextureSamplerInfo info);
    
    virtual bool        GetBlendStateInfo(FutureBlendInfo & info, s32 id);
    virtual bool        GetDepthStencilStateInfo(FutureDepthStencilInfo  & info, s32 id);
    virtual bool        GetRasterizerStateInfo(FutureRasterizerInfo & info, s32 id);
    virtual bool        GetTextureSamplerStateInfo(FutureTextureSamplerInfo & info, s32 id);
    
    virtual bool        CreateBuffer(const FutureHardwareBufferInfo & info, 
									 const FutureInitialBufferData & data, 
									 IFutureHardwareBuffer ** buffer);
    virtual bool        CreateShader(const FutureShaderInfo & info, 
									 const FutureInitialShaderData & data,
									 IFutureShader ** shader);
    virtual bool        CreateTexture(const FutureTextureInfo info, 
									  const FutureInitialTextureData & data,
									  IFutureTexture ** texture);
    virtual bool        CreateMips(IFutureTexture * texture);
    
    virtual bool        IsFeatureSupported(FutureDeviceSupport feature);
    virtual u32         GetCapability(FutureDeviceCapabilityType type);
    
    virtual bool        GetViewport(FutureViewport & viewport);
    virtual bool        SetViewport(const FutureViewport & viewport);
    
    
    virtual bool        ClearDepthStencil(IFutureTexture * depthStencil, f32 depthClear = 0.f, u8 stencilClear = 0);
    virtual bool        ClearDepthBuffer(IFutureTexture * depthStencil, f32 clearValue = 0.f);
    virtual bool        ClearStencil(IFutureTexture * depthStencil, u8 clearValue = 0);
    virtual bool        ClearRenderTarget(IFutureTexture * renderTarget);
    virtual bool        ClearState();
    
    virtual bool        GetRenderTarget(IFutureTexture ** renderTarget);
    virtual bool        SetRenderTarget(IFutureTexture * renderTarget);
    
    virtual bool        GetDepthStencil(IFutureTexture ** depthStencil);
    virtual bool        SetDepthStencil(IFutureTexture * depthStencil);
    
    virtual bool        GetShader(FutureShaderType type, IFutureShader ** shader);
    
    virtual bool        SetBlendState(s32 state);
    virtual bool        SetDepthStencilState(s32 state);
    virtual bool        SetRasterizerState(s32 state);
    
    virtual u32         GetBlendState();
    virtual u32         GetDepthStencilState();
    virtual u32         GetRasterizerState();
    
    virtual bool        GetVertexBuffer(IFutureHardwareBuffer ** buffer);
    virtual bool        GetIndexBuffer(IFutureHardwareBuffer ** buffer);

    virtual bool        SetVertexBuffer(IFutureHardwareBuffer * buffer);
    virtual bool        SetIndexBuffer(IFutureHardwareBuffer * buffer);
    virtual bool		SetPrimitiveType(FuturePrimitiveType primType);

    virtual bool        BeginRender();
    virtual bool        Render();
    virtual bool        EndRender();


	void				CallDeviceCreated();
	void				CallDeviceLost();
	void				CallDevicePreReset();
	void				CallDeviceReset();
	void				CallDevicePreChange();
	void				CallDeviceChanged();

protected:
	
	virtual void		OnPreSyncSystem(f32 deltaTime);
	virtual void		OnUpdateSystem(f32 deltaTime);
	virtual void		OnPostSyncSystem(f32 deltaTime);

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

	FutureDXShader	*						m_activeShaders[FutureShaderType_Max];

	FutureDXHardwareBuffer *				m_vertexBuffer;
	FutureDXHardwareBuffer *				m_indexBuffer;
	FuturePrimitiveType						m_primitiveType;

	FutureDXTexture *						m_depthStencil;
	FutureDXTexture *						m_renderTarget;
	ID3D11Texture2D *						m_backBuffer;
	FutureViewport							m_viewport;

	FutureArray<IFutureDeviceCallback*>		m_deviceCallbacks;
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