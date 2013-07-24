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

#ifndef FUTURE_CORE_SYSTEM_GRAPHICS_H
#define FUTURE_CORE_SYSTEM_GRAPHICS_H

#include <future/core/system/system.h>
#include <future/core/system/graphics/graphicstypes.h>
#include <future/core/system/graphics/graphicstexture.h>
#include <future/core/system/graphics/graphicsbuffers.h>
#include <future/core/system/graphics/graphicsshader.h>
#include <future/core/system/graphics/graphicswindow.h>

class IFutureGraphicsSystem : public FutureSystemBase
{
public:
	IFutureGraphicsSystem()
		: FutureSystemBase()
	{
		m_needsUpdate = true;
		m_systemTime = 0;
		m_systemType = FutureSystemType_Graphics;
	}
	

	virtual bool    CreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings) = 0;
    virtual bool    RecreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings) = 0;
    virtual void    DestroyDevice() = 0;

	virtual FutureGraphicsSettings *	GraphicsSettings() = 0; 
	virtual void *						ProgramInstance() = 0;

	virtual IFutureWindow *				Window() = 0;

	virtual bool						HasDevice() = 0;
	virtual void *						GetDevice() = 0;

	virtual void						AddDeviceCallback(IFutureDeviceCallback * deviceCallback) = 0;
	virtual void						RemoveDeviceCallback(IFutureDeviceCallback * deviceCallback) = 0;
    
    
    
    virtual u32         CreateBlendState(const FutureBlendInfo info) = 0;
    virtual u32         CreateDepthStencilInfo(const FutureDepthStencilInfo info) = 0;
    virtual u32         CreateRasterizerInfo(const FutureRasterizerInfo info) = 0;
    virtual u32         CreateTextureSamplerInfo(const FutureTextureSamplerInfo info) = 0;
    
    virtual bool        GetBlendState(const FutureBlendInfo info) = 0;
    virtual bool        CreateDepthStencilInfo(const FutureDepthStencilInfo info) = 0;
    virtual bool        CreateRasterizerInfo(const FutureRasterizerInfo info) = 0;
    virtual bool        CreateTextureSamplerInfo(const FutureTextureSamplerInfo info) = 0;
    
    virtual bool        CreateBuffer(const FutureBufferInfo info, IFutureHardwareBuffer ** buffer) = 0;
    virtual bool        CreateShader(const FutureShaderInfo info, IFutureShader ** shader) = 0;
    virtual bool        CreateTexture(const FutureTextureInfo info, IFutureTexture ** texture) = 0;
    virtual bool        CreateMips(IFutureTexture * texture) = 0;
    
    virtual bool        IsFeatureSupported(FutureDeviceSupport feature) = 0;
    virtual u32         GetCapability(FutureDeviceCapabilityType type) = 0;
    
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
    
    virtual bool        SetBlendState(u32 state) = 0
    virtual bool        SetDepthStencilState(u32 state) = 0
    virtual bool        SetRasterizerState(u32 state) = 0
    
    virtual u32         GetBlendState(u32 state) = 0
    virtual u32         GetDepthStencilState(u32 state) = 0
    virtual u32         GetRasterizerState(u32 state) = 0
    
    virtual bool        GetVertexBuffer(IFutureHardwareBuffer ** buffer) = 0;
    virtual bool        GetIndexBuffer(IFutureHardwareBuffer ** buffer) = 0;
    
    virtual bool        Render(IFutureHardwareBuffer * vertexBuffer,
                               IFutureHardwareBuffer * indexBuffer,
                               FuturePrimitiveType primType) = 0;
    
    virtual bool        BeginRender() = 0;
    virtual bool        EndRender() = 0;
};

#endif