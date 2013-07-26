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

#ifndef FUTURE_CORE_SYSTEM_GRAPHICS_SETTINGS_H
#define FUTURE_CORE_SYSTEM_GRAPHICS_SETTINGS_H

#include <future/core/system/graphics/graphicstypes.h>
#include <future/core/system/graphics/graphicswindow.h>
#include <future/core/system/graphics/graphicstexture.h>

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
    FutureDeviceCapability_MaxTexture1DSize,
    FutureDeviceCapability_MaxTexture2DSize,
    FutureDeviceCapability_MaxTexture3DSize,
    FutureDeviceCapability_MaxTextureArraySize,
    FutureDeviceCapability_MaxMultisamples,
    FutureDeviceCapability_MaxActiveTextures,
    FutureDeviceCapability_MaxTextureCubeSize,
    FutureDeviceCapability_MaxDepthTextureSamples,
    FutureDeviceCapability_MaxRenderTargets,
    FutureDeviceCapability_MaxRenderTargetSize
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
    FutureDeviceCapability_MaxUniformComponents,
    FutureDeviceCapability_MaxOutputComponents,
    
    FutureDeviceCapability_MaxViewPortWidth,
    FutureDeviceCapability_MaxViewPortHeight,
    FutureDeviceCapability_MaxViewPortDepth,
    FutureDeviceCapability_MaxViewPorts,
    
    FutureDeviceCapability_BufferMapAlignment,
    
    FutureDeviceCapability_Max,
};

enum FutureGraphicsDeviceType
{
    FutureGraphicsDeviceType_DirectX_10_0   = 0x0001,
    FutureGraphicsDeviceType_DirectX_10_1   = 0x0002,
    FutureGraphicsDeviceType_DirectX_11_0   = 0x0004,
    FutureGraphicsDeviceType_DirectX_11_1   = 0x0008,
    
    FutureGraphicsDeviceType_OpenGL_3_1     = 0x0010,
    FutureGraphicsDeviceType_OpenGl_3_3     = 0x0020,
    FutureGraphicsDeviceType_OpenGL_4_0     = 0x0040,
    FutureGraphicsDeviceType_OpenGL_4_1     = 0x0080,
    FutureGraphicsDeviceType_OpenGL_4_2     = 0x0100,
    FutureGraphicsDeviceType_OpenGL_4_3     = 0x0200,
    FutureGraphicsDeviceType_OpenGL_4_4     = 0x0400,
    
    FutureGraphicsDeviceType_OpenGL_ES_1_0  = 0x1000,
    FutureGraphicsDeviceType_OpenGL_ES_1_1  = 0x2000,
    FutureGraphicsDeviceType_OpenGL_ES_2_0  = 0x4000,
    FutureGraphicsDeviceType_OpenGL_ES_3_0  = 0x8000,
};

enum FutureGraphicsDriverType
{
    FutureGraphicsDriverType_Hardware,
    FutureGraphicsDriverType_Reference,
    FutureGraphicsDriverType_Software,
    FutureGraphicsDriverType_WARP,
};

struct FutureGraphicsSettings
{
    bool                        m_fullScreen;
	bool                        m_wireframe;
	FutureCullMode              m_cullMode;
	bool                        m_enableMultisampling;
    FutureGraphicsDeviceType    m_deviceType;
    FutureGraphicsDriverType    m_driverType;
    bool                        m_debug;
    bool                        m_singleThreaded;
    
    u32                         m_backBufferWidth;
    u32                         m_backBufferHeight;
    
    u32                         m_refreshRateNumerator;
    u32                         m_refreshRateDenominator;
    
    FuturePixelFormat           m_adapterDisplayFormat;
    FutureAdapterInfo           m_adapterInfo;
};

struct FutureGraphicsDeviceCreationSettings
{
    bool                        m_fullScreen;
    FutureRasterizerInfo        m_rasterizer;
    
    u32                         m_multisampleCount;
    f32                         m_multisampleQuality;
    
    FutureGraphicsDeviceType *  m_acceptableDeviceTypes;
    FutureGraphicsDriverType    m_acceptableDriverTypes;
    bool                        m_tryDebug;
    bool                        m_trySingleThreaded;
    
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
};


#endif