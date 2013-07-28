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
 *	Settings for creating a graphics device.
 *   Also contains structures for getting device capabilities
 */

#ifndef FUTURE_GRAPHICS_SETTINGS_H
#define FUTURE_GRAPHICS_SETTINGS_H

#include <future/graphics/type/type.h>
#include <future/core/system/window.h>
#include <future/core/system/application.h>
#include <future/graphics/type/texture.h>

enum FutureDeviceSupport
{
    FutureDeviceSupport_CoreFeatures,
    FutureDeviceSupport_Multisample,
    FutureDeviceSupport_TextureCubemap,
    FutureDeviceSupport_RenderToTexture,
    FutureDeviceSupport_Depth_Stencil,
    FutureDeviceSupport_VertexShader,
    FutureDeviceSupport_PixelShader,
    FutureDeviceSupport_VertexBuffer,
    FutureDeviceSupport_IndexBuffer,
    FutureDeviceSupport_PixelBuffer,
    FutureDeviceSupport_NonUniformTexture,
    FutureDeviceSupport_Instancing,
    FutureDeviceSupport_RenderTarget,
    FutureDeviceSupport_GeometryShader,
    FutureDeviceSupport_Texture1D,
    FutureDeviceSupport_Texture2D,
    FutureDeviceSupport_Texture3D,
    FutureDeviceSupport_TextureArrays,
    FutureDeviceSupport_TextureSamplers,
    FutureDeviceSupport_ShaderSubroutine,
    FutureDeviceSupport_TesslationShaders,
    FutureDeviceSupport_ComputeShaders,
    FutureDeviceSupport_VertexCustomAttributes,
    FutureDeviceSupport_MipMap,
    FutureDeviceSupport_GenerateMipMap,
    FutureDeviceSupport_TwoSidedStencil,
    FutureDeviceSupport_HardwareVideo,
    FutureDeviceSupport_Stereoscopic,
    FutureDeviceSupport_FullScreen,
    FutureDeviceSupport_ResolutionChange,
    FutureDeviceSupport_Threading,
    
    FutureDeviceSupport_Max,
};

enum FutureDeviceCapabilityType
{
    FutureDeviceCapability_MaxTexture1DDimension,
    FutureDeviceCapability_MaxTexture2DDimension,
    FutureDeviceCapability_MaxTexture3DDimension,
    FutureDeviceCapability_MaxTextureArraySize,
    FutureDeviceCapability_MaxMultiSamples,
    FutureDeviceCapability_MaxActiveTextures,
    FutureDeviceCapability_MaxTextureCubeDimension,
    FutureDeviceCapability_MaxRenderTargets,
    FutureDeviceCapability_MaxRenderTargetDimension,
    FutureDeviceCapability_MaxTextureBufferSize,
    FutureDeviceCapability_MaxTextureLODBias,
    
    FutureDeviceCapability_MaxIndices,
    FutureDeviceCapability_MaxVertices,
    
    FutureDeviceCapability_MaxComputeShaderStorageBlocks,
    FutureDeviceCapability_MaxComputeShaderUniformBlocks,
    FutureDeviceCapability_MaxComputeShaderWorkGroups,
    FutureDeviceCapability_MaxComputeShaderWorkGroupSize,
    
    FutureDeviceCapability_MaxPixelShaderInputComponents,
    FutureDeviceCapability_MaxPixelShaderUniformComponents,
    FutureDeviceCapability_MaxPixelShaderTextures,
    
    FutureDeviceCapability_MaxGeometryShaderInputComponents,
    FutureDeviceCapability_MaxGeometryShaderOutputComponents,
    FutureDeviceCapability_MaxGeometryShaderUniformComponents,
    
    FutureDeviceCapability_MaxPreTesslationShaderStorageBlocks,
    FutureDeviceCapability_MaxPostTesslationShaderStorageBlocks,
    
    FutureDeviceCapability_MaxVertexShaderAttributes,
    FutureDeviceCapability_MaxVertexShaderTextures,
    FutureDeviceCapability_MaxVertexShaderUniformComponents,
    FutureDeviceCapability_MaxVertexShaderOutputComponents,
    
    FutureDeviceCapability_MaxViewPortWidth,
    FutureDeviceCapability_MaxViewPortHeight,
    FutureDeviceCapability_MaxViewPortDepth,
    FutureDeviceCapability_MaxViewPorts,
    
    FutureDeviceCapability_BufferMapAlignment,
    
    FutureDeviceCapability_Max,
};

enum FutureGraphicsDeviceType
{
    FutureGraphicsDeviceType_DirectX,
    FutureGraphicsDeviceType_OpenGL,
    FutureGraphicsDeviceType_OpenGL_ES,
};

enum FutureGraphicsDriverType
{
    FutureGraphicsDriverType_Hardware,
    FutureGraphicsDriverType_Software,
};

struct FutureGraphicsSettings
{
    bool                        m_fullScreen;
    FutureRasterizerInfo        m_rasterizer;

    u32                         m_multisampleCount;
    u32                         m_multisampleQuality;
    FutureGraphicsDeviceType    m_deviceType;
    FutureGraphicsDriverType    m_driverType;
    bool                        m_debug;
    bool                        m_singleThreaded;
    
	u32							m_deviceMajorVersion;
	u32							m_deviceMinorVersion;

    u32                         m_backBufferWidth;
    u32                         m_backBufferHeight;
    
    u32                         m_refreshRateNumerator;
    u32                         m_refreshRateDenominator;
    
    FutureDataFormat	        m_adapterDisplayFormat;
    FutureAdapterInfo           m_adapterInfo;
};

struct FutureGraphicsDeviceCreationSettings
{
public:

    bool                        m_fullScreen;
    FutureRasterizerInfo        m_rasterizer;
    
    u32                         m_multisampleCount;
    u32                         m_multisampleQuality;

    bool                        m_tryDebug;
    bool                        m_singleThreaded;
    
    IFutureWindow *             m_window;
    
    u32                         m_minBackBufferWidth;
    u32                         m_minBackBufferHeight;
    u32                         m_maxBackBufferWidth;
    u32                         m_maxBackBufferHeight;
    u32                         m_targetBackBufferWidth;
    u32                         m_targetBackBufferHeight;
    f32                         m_forceAspectRatio;
    
    bool                        m_createDefaultDepthBuffer;
    bool                        m_createDefaultDepthStencil;
    FutureDepthStencilInfo      m_stencilInfo;

	
	FutureGraphicsDeviceCreationSettings()
		: m_fullScreen(true),
		  m_rasterizer(),
		  m_multisampleCount(1),
		  m_multisampleQuality(0),
		  m_tryDebug(FUTURE_DEBUG),
		  m_singleThreaded(false),
		  m_window(FutureApplication::GetInstance()->GetWindow()),
		  m_minBackBufferWidth(0),
		  m_minBackBufferHeight(0),
		  m_maxBackBufferWidth(0),
		  m_maxBackBufferHeight(0),
		  m_targetBackBufferWidth(0),
	      m_targetBackBufferHeight(0),
		  m_forceAspectRatio(-1),
		  m_createDefaultDepthBuffer(true),
		  m_createDefaultDepthStencil(true),
		  m_stencilInfo()
	{};
};


#endif