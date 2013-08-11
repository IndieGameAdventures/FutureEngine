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

#include <future/graphics/type/type.h>
#include <future/graphics/type/settings.h>
#include <future/graphics/type/texture.h>
#include <future/graphics/type/buffers.h>
#include <future/graphics/type/shader.h>

class IFutureGraphicsDevice
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(IFutureGraphicsDevice);
	virtual ~IFutureGraphicsDevice(){};

	virtual bool								HasDevice() = 0;
	virtual void *								GetDevice() = 0;
   
	virtual bool								IsFeatureSupported(FutureDeviceSupport feature) = 0;
	virtual s32									GetDeviceCapability(FutureDeviceCapabilityType feature) = 0;
    
    virtual s32									CreateBlendState(const FutureBlendStateInfo * info) = 0;
    virtual s32									CreateDepthStencilState(const FutureDepthStencilInfo * info) = 0;
    virtual s32									CreateRasterizerState(const FutureRasterizerInfo * info) = 0;
    virtual s32									CreateTextureSamplerState(const FutureTextureSamplerInfo * info) = 0;
    
    virtual const FutureBlendStateInfo *		GetBlendStateInfo(s32 id) = 0;
    virtual const FutureDepthStencilInfo *		GetDepthStencilStateInfo(s32 id) = 0;
    virtual const FutureRasterizerInfo *		GetRasterizerStateInfo(s32 id) = 0;
    virtual const FutureTextureSamplerInfo *	GetTextureSamplerStateInfo(s32 id) = 0;
    
	virtual bool								CreateBuffer(const FutureHardwareBufferInfo * info, 
															 const FutureInitialBufferData * data, 
															 IFutureHardwareBuffer ** buffer) = 0;
    virtual bool								CreateShader(const FutureShaderCreationData * info, 
															IFutureShader ** shader) = 0;
    virtual bool								CreateTexture(const FutureTextureInfo * info, 
															  const FutureInitialTextureData * data,
															  IFutureTexture ** texture) = 0;
    virtual bool								CreateMips(IFutureTexture * texture) = 0;
    
    virtual const FutureViewport *				GetViewport() = 0;
    virtual bool								SetViewport(const FutureViewport * viewport) = 0;
    
    
    virtual bool								ClearDepthStencil(IFutureTexture * depthStencil, f32 depthClear = 0.f, u8 stencilClear = 0) = 0;
    virtual bool								ClearDepthBuffer(IFutureTexture * depthStencil, f32 clearValue = 0.f) = 0;
    virtual bool								ClearStencil(IFutureTexture * depthStencil, u8 clearValue = 0) = 0;
    virtual bool								ClearRenderTarget(IFutureTexture * renderTarget) = 0;
    virtual bool								ClearState() = 0;
    
    virtual IFutureTexture *					GetRenderTarget() = 0;
    virtual bool								SetRenderTarget(IFutureTexture * renderTarget) = 0;
    
    virtual IFutureTexture *					GetDepthStencil() = 0;
    virtual bool								SetDepthStencil(IFutureTexture * depthStencil) = 0;
    
    virtual bool								SetShader(FutureShaderType type, IFutureShader * shader) = 0;
    virtual IFutureShader *						GetShader(FutureShaderType type) = 0;
    
    virtual bool								SetBlendState(s32 state) = 0;
    virtual bool								SetDepthStencilState(s32 state) = 0;
    virtual bool								SetRasterizerState(s32 state) = 0;
    
    virtual s32									GetBlendState() = 0;
    virtual s32									GetDepthStencilState() = 0;
    virtual s32									GetRasterizerState() = 0;
    
    virtual IFutureHardwareBuffer *				GetVertexBuffer() = 0;
    virtual IFutureHardwareBuffer *				GetIndexBuffer() = 0;

    virtual bool								SetVertexBuffer(IFutureHardwareBuffer * buffer) = 0;
    virtual bool								SetIndexBuffer(IFutureHardwareBuffer * buffer) = 0;
    virtual bool								SetPrimitiveType(FuturePrimitiveType primType) = 0;

    virtual bool								BeginRender() = 0;
    virtual bool								Render() = 0;
    virtual bool								EndRender() = 0;

protected:
	friend class FutureGraphicsSystem;

	IFutureGraphicsDevice();
	~IFutureGraphicsDevice();
	
	virtual bool		CreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings) = 0;
    virtual bool		RecreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings) = 0;
    virtual void		DestroyDevice() = 0;
};

#endif