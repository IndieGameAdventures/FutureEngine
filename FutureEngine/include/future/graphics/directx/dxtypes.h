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
*	Types, Structs, and Enums used by the graphics system
*/

#ifndef FUTURE_CORE_SYSTEM_GRAPHICS_TYPE_H
#define FUTURE_CORE_SYSTEM_GRAPHICS_TYPE_H

#include <future/core/system/system.h>

// all classes that use the current device must implement these methods
// all references to buffers must be cleared in all functions
class IFutureDeviceCallback
{
public:
	IFutureDeviceCallback()
	{;}

	// this is called when the device is lost and then found again
	virtual void DeviceLost() = 0;
	virtual void DeviceFound() = 0;
	// this is called before the device is reset, ie. resizing the window, changing format
	// All buffers must cleared
	virtual void DevicePreReset() = 0;
	virtual void DeviceReset() = 0;
	// this is called before the device is changed, ie. changing dx version, changing monitors, changing type( HAL to REF, REF to HAL )
	// All buffers and pointers to the current device must cleared
	virtual void DevicePreChange() = 0;
	virtual void DeviceChange() = 0;
};

// the order in which the renderer renders objects
// objects are rendered in all the phases they are present in
// so if an object is not part of the FutureRP_Shadows phase, it will not have a shadow
// the first 16 bits of the enum are used to determine the phase and the second 16 bits
// can be used to specify priority within a phase
enum FutureRenderPhase
{
	FutureRenderPhase_Shadows				= 0x00010000,
	FutureRenderPhase_Reflection_SkyDome	= 0x00020000,
	FutureRenderPhase_Reflection			= 0x00080000,
	FutureRenderPhase_Normal_SkyDome		= 0x00100000,
	FutureRenderPhase_Normal				= 0x00400000,
	FutureRenderPhase_Water					= 0x00800000,

	FutureRenderPhase_Max,
	FutureRenderPhase_Nil = -1,
};

enum FutureVariableType
{
	FutureVariable_S8,
	FutureVariable_U8,
	FutureVariable_T8,
	FutureVariable_S16,
	FutureVariable_U16,
	FutureVariable_T16,
	FutureVariable_S32,
	FutureVariable_U32,
	FutureVariable_T32,
	FutureVariable_F32,
	
	FutureVariable_Scalar,
	FutureVariable_Vector,
	FutureVariable_Matrix,
};

// the first number is the element type and size, the second number is the number of elements 
// corresponds 1:1 with DXGI_FORMAT
enum FutureVertexElementType
{
	FutureVertexElementType_F32_4			= 2,
	FutureVertexElementType_U32_4			= 3,
	FutureVertexElementType_S32_4			= 4,

	FutureVertexElementType_F32_3			= 6,
	FutureVertexElementType_U32_3			= 7,
	FutureVertexElementType_S32_3			= 8,

	FutureVertexElementType_F16_4			= 10,
	FutureVertexElementType_UNORM16_4		= 11,
	FutureVertexElementType_U16_4			= 12,
	FutureVertexElementType_SNORM16_4		= 13,
	FutureVertexElementType_S16_4			= 14,

	FutureVertexElementType_F32_2			= 16,
	FutureVertexElementType_U32_2			= 17,
	FutureVertexElementType_S32_2			= 18,

	FutureVertexElementType_UNORM8_4		= 28,
	FutureVertexElementType_U8_4			= 30,
	FutureVertexElementType_SNORM8_4		= 31,
	FutureVertexElementType_S8_4			= 32,

	FutureVertexElementType_F16_2			= 34,
	FutureVertexElementType_UNORM16_2		= 35,
	FutureVertexElementType_U16_2			= 36,
	FutureVertexElementType_SNORM16_2		= 37,
	FutureVertexElementType_S16_2			= 38,

	FutureVertexElementType_F32_1			= 40,
	FutureVertexElementType_U32_1			= 42,
	FutureVertexElementType_S32_1			= 43,

	FutureVertexElementType_UNORM8_2		= 49,
	FutureVertexElementType_U8_2			= 50,
	FutureVertexElementType_SNORM8_2		= 51,
	FutureVertexElementType_S8_2			= 52,

	FutureVertexElementType_F16_1			= 54,
	FutureVertexElementType_UNORM16_1		= 55,
	FutureVertexElementType_U16_1			= 57,
	FutureVertexElementType_SNORM16_1		= 58,
	FutureVertexElementType_S16_1			= 59,

	FutureVertexElementType_UNORM8_1		= 61,
	FutureVertexElementType_U8_1			= 62,
	FutureVertexElementType_SNORM8_1		= 63,
	FutureVertexElementType_S8_1			= 64,
};

struct FutureVertexElement
{
	const char *			m_inputSementics;
	FutureVertexElementType	m_type;
};


#define FUTURE_MAX_VERTEX_ELEMENTS 32

// these have parallels in both dx9 and dx10, this just makes it easier
enum FuturePrimitiveType
{
    FuturePrimitiveType_Triangle_List = 0,
    FuturePrimitiveType_Triangle_Strip,
    FuturePrimitiveType_Line_List,
    FuturePrimitiveType_Line_Strip,
    FuturePrimitiveType_Point_List,
    FuturePrimitiveType_Triangle_List_Adj,
    FuturePrimitiveType_Triangle_Strip_Adj,
    FuturePrimitiveType_Line_List_Adj,
    FuturePrimitiveType_Line_Strip_Adj,
};

enum FutureIndexType
{
    FutureIT_16bit = 0,
    FutureIT_32bit,
};

enum FuturePixelFormat
{
	FuturePixelFormat_Unknown		= 0,

	//	128 bit formats
	FuturePixelFormat_RGBA_F32		= 2,
	FuturePixelFormat_RGBA_U32		= 3,
	FuturePixelFormat_RGBA_S32		= 4,
	
	// 96 bit formats
	FuturePixelFormat_RGB_F32		= 6,
	FuturePixelFormat_RGB_U32		= 7,
	FuturePixelFormat_RGB_S32		= 8,
	
	// 64 bit formats
	FuturePixelFormat_RGBA_F16		= 10,
	FuturePixelFormat_RGBA_U16		= 12,
	FuturePixelFormat_RGBA_S16NORM	= 13,
	FuturePixelFormat_RGBA_S16		= 14,
	
	FuturePixelFormat_RG_F32		= 16,
	FuturePixelFormat_RG_U32		= 17,
	FuturePixelFormat_RG_S32		= 18,
	
	// 32 bit formats
	FuturePixelFormat_RG_F16		= 10,
	FuturePixelFormat_RGB10_A2_U	= 25,

	FuturePixelFormat_RGBA_U8		= 30,
	FuturePixelFormat_RGBA_S8NORM	= 31,
	FuturePixelFormat_RGBA_S8		= 32,
	
	FuturePixelFormat_RG_F16		= 34,
	FuturePixelFormat_RG_U16		= 36,
	FuturePixelFormat_RG_S16NORM	= 37,
	FuturePixelFormat_RG_S16		= 38,
	
	FuturePixelFormat_R_F32			= 41,
	FuturePixelFormat_R_U32			= 42,
	FuturePixelFormat_R_S32			= 43,

	// 16 bit formats
	FuturePixelFormat_RG_U8			= 50,
	FuturePixelFormat_RG_S8NORM		= 51,
	FuturePixelFormat_RG_S8			= 52,
	
	FuturePixelFormat_R_F16			= 54,
	FuturePixelFormat_R_U16			= 57,
	FuturePixelFormat_R_S16NORM		= 58,
	FuturePixelFormat_R_S16			= 59,

	// 8 bit formats
	FuturePixelFormat_R_U8			= 62,
	FuturePixelFormat_R_S8NORM		= 63,
	FuturePixelFormat_R_S8			= 64,
};


enum FutureHardwareResourceUsage
{
	FutureHardwareResourceUsage_Default = 0,
	FutureHardwareResourceUsage_Locked = 1,
	FutureHardwareResourceUsage_Dynamic = 2,
	FutureHardwareResourceUsage_Staging = 3,
};

struct FutureAdapterInfo
{
	string  m_description[128];
	u32		m_vendorId;
	u32		m_deviceId;
	u32		m_subSysId;
	u32		m_revision;
	size_t	m_dedicatedVideoMemory;
	size_t	m_dedicatedSystemMemory;
	size_t	m_sharedSystemMemory;
};

struct FutureViewPort
{
	f32 m_left;
	f32 m_right;
	f32 m_top;
	f32 m_bottom;
};

enum FutureComparisonFunction
{
	FutureComparisonFunction_Never				= 1,
	FutureComparisonFunction_LessThan			= 2,
	FutureComparisonFunction_Equal				= 3,
	FutureComparisonFunction_LessThanOrEqual	= 4,
	FutureComparisonFunction_GreaterThan		= 5,
	FutureComparisonFunction_NotEqual			= 6,
	FutureComparisonFunction_GreaterThanOrEqual	= 7,
	FutureComparisonFunction_Always				= 8
};

enum FutureStencilOperation
{
	FutureStencilOperation_Keep			= 1,
	FutureStencilOperation_Zero			= 2,
	FutureStencilOperation_Replace		= 3,
	FutureStencilOperation_Increase		= 4,
	FutureStencilOperation_Decrease		= 5,
	FutureStencilOperation_Invert		= 6,
	FutureStencilOperation_IncreaseWrap = 7,
	FutureStencilOperation_DecreaseWrap	= 8
};

struct FutureStencilInfo
{
    bool						m_enableStencil;
    u8                          m_mask;
    FutureStencilOperation      m_onFail;
    FutureStencilOperation      m_onFailDepth;
    FutureStencilOperation      m_onPassBoth;
    FutureComparisonFunction	m_comparisonFunction;
};

struct FutureDepthStencilInfo
{
	bool						m_enableDepthMap;
	FutureComparisonFunction	m_comparisonFunction;
	FutureStencilInfo			m_frontStencil;
	FutureStencilInfo			m_backStencil;
};


enum FutureScaleMode
{
	FutureScaleMode_Undefined,
	FutureScaleMode_Center,
	FutureScaleMode_Stretch,
	FutureScaleMode_AspectStretch
};

enum FutureCullMode
{
	FutureCullMode_None = 1,
	FutureCullMode_Front = 2,
	FutureCullMode_Back = 3,
};

enum FutureBlendFunction
{
    FutureBlendFunction_Zero                = 1,
    FutureBlendFunction_One                 = 2,
    FutureBlendFunction_Source              = 3,
    FutureBlendFunction_SourceInverse       = 4,
    FutureBlendFunction_SourceAlpha         = 5,
    FutureBlendFunction_SourceInverseAlpha  = 6,
    FutureBlendFunction_DestAlpha           = 7,
    FutureBlendFunction_DesteInverseAlpha   = 8,
    FutureBlendFunction_Dest                = 9,
    FutureBlendFunction_DestInverse         = 10,
    FutureBlendFunction_SaturateAlpha       = 11,
};

enum FutureBlendOperation
{
    FutureBlendOperation_Add        = 1,
    FutureBlendOperation_Subtract   = 2,
    FutureBlendOperation_ReverseSub = 3,
    FutureBlendOperation_Min        = 4,
    FutureBlendOperation_Max        = 5,
};

enum FutureBlendTarget
{
    FutureBlendTarget_Color,
    FutureBlendTarget_Alpha,
};

struct FutureBlendInfo
{
    FutureBlendFunction     m_sourceFunction;
    FutureBlendFunction     m_destFunction;
    FutureBlendOperation    m_blendOperation;
};

struct FutureRenderTargetInfo
{
    bool            m_enableBlending;
    FutureBlendInfo m_colorBlend;
    FutureBlendInfo m_alphaBlend;
};

enum FutureTextureSamplerFilter
{
    FutureTextureSamplerFilter_NearestPoint,
    FutureTextureSamplerFilter_LinearPoint,
    FutureTextureSamplerFilter_NearestMip_NearestPoint,
    FutureTextureSamplerFilter_NearestMip_LinearPoint,
    FutureTextureSamplerFilter_LinearMip_NearestPoint,
    FutureTextureSamplerFilter_LinearMip_LinearPoint,
};

enum FutureTextureWrapMode
{
    FutureTextureWrapMode_Repeat    = 1,
    FutureTextureWrapMode_Mirror    = 2,
    FutureTextureWrapMode_Clamp     = 3,
    FutureTextureWrapMode_Border    = 4,
};

struct FutureTextureSamplerInfo
{
    f32                             m_minLOD;
    f32                             m_maxLOD;
    f32                             m_mipLODBias;
    
    FutureTextureSamplerFilter      m_filterMin;
    FutureTextureSamplerFilter      m_filterMag;
    
    FutureTextureWrapMode           m_wrapModeU;
    FutureTextureWrapMode           m_wrapModeV;
    FutureTextureWrapMode           m_wrapModeW;
    
    FutureComparisonFunction        m_compareFunction;
};

struct FutureRasterizerInfo
{
    bool                        m_wireframe;
	FutureCullMode              m_cullMode;
	bool                        m_enableMultisampling;
};

// Anything that wants to be rendered by the graphics system must extend this class
class IFutureRenderable
{
	FutureRenderable(){};
	virtual ~FutureRenderable(){};

	virtual bool	ShouldRender() = 0;
	virtual void	Invalidate() = 0;

	virtual void	Render() = 0;

	virtual u32		RenderPriority() = 0;
	virtual u32		RenderPhase() = 0;
};


// All objects that may need to be stored in hardware buffers (transferred to the GPU) must extend this
class IFutureHardwareObject
{
	IFutureHardwareObject(){};
	virtual ~IFutureHardwareObject(){}

	virtual bool	ApplyToHardware() = 0;
	virtual bool	RemoveFromHardware() = 0;
	virtual bool	ReapplyToHardware() = 0;

	virtual bool	IsAppliedToHardware() = 0;

	virtual u32		HardwareBufferID() = 0;
};

#endif