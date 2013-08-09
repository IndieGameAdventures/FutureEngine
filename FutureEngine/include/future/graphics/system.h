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

#ifndef FUTURE_GRAPHICS_DRIVER_H
#define FUTURE_GRAPHICS_DRIVER_H

#include <future/core/system/system.h>
#include <future/core/system/window.h>
#include <future/graphics/type/type.h>
#include <future/graphics/type/settings.h>
#include <future/graphics/type/texture.h>
#include <future/graphics/type/buffers.h>
#include <future/graphics/type/shader.h>

class IFutureGraphicsSystem : public FutureSystemBase
{
public:
	IFutureGraphicsSystem()
		: FutureSystemBase()
	{
		m_systemType = FutureSystemType_Graphics;
	}

	virtual bool    CreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings) = 0;
    virtual bool    RecreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings) = 0;
    virtual void    DestroyDevice() = 0;

	virtual bool			HasDevice() = 0;
	virtual void *			GetDevice() = 0;

	virtual	void			GetGraphicsSettings(FutureGraphicsSettings * settings) = 0; 
   
	virtual bool			IsFeatureSupported(FutureDeviceSupport feature) = 0;
	virtual s32				GetDeviceCapability(FutureDeviceCapabilityType feature) = 0;

	virtual IFutureWindow *	Window() = 0;

	virtual void			AddDeviceCallback(IFutureDeviceCallback * deviceCallback) = 0;
	virtual void			RemoveDeviceCallback(IFutureDeviceCallback * deviceCallback) = 0;

    
    virtual s32         CreateBlendState(const FutureBlendStateInfo info) = 0;
    virtual s32         CreateDepthStencilState(const FutureDepthStencilInfo info) = 0;
    virtual s32         CreateRasterizerState(const FutureRasterizerInfo info) = 0;
    virtual s32         CreateTextureSamplerState(const FutureTextureSamplerInfo info) = 0;
    
    virtual bool        GetBlendStateInfo(FutureBlendStateInfo * info, s32 id) = 0;
    virtual bool        GetDepthStencilStateInfo(FutureDepthStencilInfo  * info, s32 id) = 0;
    virtual bool        GetRasterizerStateInfo(FutureRasterizerInfo * info, s32 id) = 0;
    virtual bool        GetTextureSamplerStateInfo(FutureTextureSamplerInfo * info, s32 id) = 0;
    
    virtual bool        CreateBuffer(const FutureHardwareBufferInfo & info, 
									 const FutureInitialBufferData & data, 
									 IFutureHardwareBuffer ** buffer) = 0;
    virtual bool        CreateShader(const FutureShaderInfo & info, 
									 const FutureInitialShaderData & data,
									 IFutureShader ** shader) = 0;
    virtual bool        CreateTexture(const FutureTextureInfo info, 
									  const FutureInitialTextureData & data,
									  IFutureTexture ** texture) = 0;
    virtual bool        CreateMips(IFutureTexture * texture) = 0;
    
    virtual bool        GetViewport(FutureViewport & viewport) = 0;
    virtual bool        SetViewport(const FutureViewport & viewport) = 0;
    
    
    virtual bool        ClearDepthStencil(IFutureTexture * depthStencil, f32 depthClear = 0.f, u8 stencilClear = 0) = 0;
    virtual bool        ClearDepthBuffer(IFutureTexture * depthStencil, f32 clearValue = 0.f) = 0;
    virtual bool        ClearStencil(IFutureTexture * depthStencil, u8 clearValue = 0) = 0;
    virtual bool        ClearRenderTarget(IFutureTexture * renderTarget) = 0;
    virtual bool        ClearState() = 0;
    
    virtual bool        GetRenderTarget(IFutureTexture ** renderTarget) = 0;
    virtual bool        SetRenderTarget(IFutureTexture * renderTarget) = 0;
    
    virtual bool        GetDepthStencil(IFutureTexture ** depthStencil) = 0;
    virtual bool        SetDepthStencil(IFutureTexture * depthStencil) = 0;
    
    virtual bool        GetShader(FutureShaderType type, IFutureShader ** shader) = 0;
    
    virtual bool        SetBlendState(s32 state) = 0;
    virtual bool        SetDepthStencilState(s32 state) = 0;
    virtual bool        SetRasterizerState(s32 state) = 0;
    
    virtual u32         GetBlendState() = 0;
    virtual u32         GetDepthStencilState() = 0;
    virtual u32         GetRasterizerState() = 0;
    
    virtual bool        GetVertexBuffer(IFutureHardwareBuffer ** buffer) = 0;
    virtual bool        GetIndexBuffer(IFutureHardwareBuffer ** buffer) = 0;

    virtual bool        SetVertexBuffer(IFutureHardwareBuffer * buffer) = 0;
    virtual bool        SetIndexBuffer(IFutureHardwareBuffer * buffer) = 0;
    virtual bool		SetPrimitiveType(FuturePrimitiveType primType) = 0;

    virtual bool        BeginRender() = 0;
    virtual bool        Render() = 0;
    virtual bool        EndRender() = 0;
	
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
};

#endif