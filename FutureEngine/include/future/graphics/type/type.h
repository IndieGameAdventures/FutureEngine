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

#ifndef FUTURE_GRAPHICS_TYPE_H
#define FUTURE_GRAPHICS_TYPE_H

#include <future/core/type/type.h>

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

enum FutureDataFormat
{
	FutureDataFormat_Unknown		= 0,

	//	128 bit formats
	FutureDataFormat_RGBA_F32		= 2,
	FutureDataFormat_RGBA_U32		= 3,
	FutureDataFormat_RGBA_S32		= 4,
	
	// 96 bit formats
	FutureDataFormat_RGB_F32		= 6,
	FutureDataFormat_RGB_U32		= 7,
	FutureDataFormat_RGB_S32		= 8,
	
	// 64 bit formats
	FutureDataFormat_RGBA_F16		= 10,
	FutureDataFormat_RGBA_U16NORM	= 11,
	FutureDataFormat_RGBA_U16		= 12,
	FutureDataFormat_RGBA_S16NORM	= 13,
	FutureDataFormat_RGBA_S16		= 14,
	
	FutureDataFormat_RG_F32			= 16,
	FutureDataFormat_RG_U32			= 17,
	FutureDataFormat_RG_S32			= 18,
	
	// 32 bit formats
	FutureDataFormat_RG_F16			= 10,
	FutureDataFormat_RGB10_A2_U		= 25,

	FutureDataFormat_RGBA_U8		= 30,
	FutureDataFormat_RGBA_U8NORM	= 31,
	FutureDataFormat_RGBA_S8		= 32,
	FutureDataFormat_RGBA_S8NORM	= 33,
	
	FutureDataFormat_RG_U16NORM		= 35,
	FutureDataFormat_RG_U16			= 36,
	FutureDataFormat_RG_S16NORM		= 37,
	FutureDataFormat_RG_S16			= 38,
	
	FutureDataFormat_D_F32			= 40,
	FutureDataFormat_R_F32			= 41,
	FutureDataFormat_R_U32			= 42,
	FutureDataFormat_R_S32			= 43,

	// 16 bit formats
	FutureDataFormat_RG_U8			= 50,
	FutureDataFormat_RG_U8NORM		= 51,
	FutureDataFormat_RG_S8			= 52,
	FutureDataFormat_RG_S8NORM		= 53,
	
	FutureDataFormat_R_F16			= 54,
	FutureDataFormat_R_U16			= 57,
	FutureDataFormat_R_U16NORM		= 58,
	FutureDataFormat_R_S16			= 59,
	FutureDataFormat_R_S16NORM		= 60,

	// 8 bit formats
	FutureDataFormat_R_U8			= 62,
	FutureDataFormat_R_U8NORM		= 63,
	FutureDataFormat_R_S8			= 64,
	FutureDataFormat_R_S8NORM		= 65,
};


enum FutureHardwareResourceUsage
{
	FutureHardwareResourceUsage_Default		= 0,
	FutureHardwareResourceUsage_Locked		= 1,
	FutureHardwareResourceUsage_Dynamic		= 2,
	FutureHardwareResourceUsage_Staging		= 3,
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

enum FutureScaleMode
{
	FutureScaleMode_Undefined,
	FutureScaleMode_Center,
	FutureScaleMode_Stretch,
	FutureScaleMode_AspectStretch
};

enum FutureCullMode
{
	FutureCullMode_None		= 1,
	FutureCullMode_Front	= 2,
	FutureCullMode_Back		= 3,
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

enum FutureTextureSamplerFilter
{
    FutureTextureSamplerFilter_Nearest,
    FutureTextureSamplerFilter_Linear,
};

enum FutureTextureWrapMode
{
    FutureTextureWrapMode_Repeat    = 1,
    FutureTextureWrapMode_Mirror    = 2,
    FutureTextureWrapMode_Clamp     = 3,
    FutureTextureWrapMode_Border    = 4,
};

#define FUTURE_MAX_VERTEX_ELEMENTS 16

struct FutureVertexElement
{
	const char *			m_inputSementics;
	u32						m_sementicIndex;
	FutureDataFormat		m_type;
	u32						m_inputSlot;
	u32						m_alignByteOffset;
};


struct FutureInputLayoutInfo
{
	FutureVertexElement	m_elements[FUTURE_MAX_VERTEX_ELEMENTS];
	u32					m_numElements;
};

struct FutureAdapterInfo
{
	char		m_description[128];
	u32			m_vendorId;
	u32			m_deviceId;
	u32			m_subSysId;
	u32			m_revision;
	size_t		m_dedicatedVideoMemory;
	size_t		m_dedicatedSystemMemory;
	size_t		m_sharedSystemMemory;
};

struct FutureViewport
{
	f32 m_left;
	f32 m_right;
	f32 m_top;
	f32 m_bottom;
	f32 m_near;
	f32 m_far;
};

struct FutureStencilInfo
{
    FutureStencilOperation      m_onFail;
    FutureStencilOperation      m_onFailDepth;
    FutureStencilOperation      m_onPassBoth;
    FutureComparisonFunction	m_comparisonFunction;

	FutureStencilInfo()
		: m_onFail(FutureStencilOperation_Keep),
          m_onFailDepth(FutureStencilOperation_Keep),
          m_onPassBoth(FutureStencilOperation_Keep),
    	  m_comparisonFunction(FutureComparisonFunction_Always)
	{}

};

struct FutureDepthStencilInfo
{
	bool						m_enableDepthMap;
	FutureComparisonFunction	m_comparisonFunction;
    bool						m_enableStencil;
    u8                          m_readMask;
    u8                          m_writeMask;
	FutureStencilInfo			m_frontStencil;
	FutureStencilInfo			m_backStencil;

	FutureDepthStencilInfo()
		: m_enableStencil(false),
		  m_readMask(0xFF),
		  m_writeMask(0xFF),
		  m_enableDepthMap(true),
		  m_comparisonFunction(FutureComparisonFunction_Always),
		  m_frontStencil(),
		  m_backStencil()
	{}
};


struct FutureBlendInfo
{
    FutureBlendFunction     m_sourceFunction;
    FutureBlendFunction     m_destFunction;
    FutureBlendOperation    m_blendOperation;

	FutureBlendInfo()
		: m_sourceFunction(FutureBlendFunction_Zero),
		  m_destFunction(FutureBlendFunction_One),
		  m_blendOperation(FutureBlendOperation_Add)
	{}
};

struct FutureRenderTargetInfo
{
    bool            m_enableBlending;
	bool			m_writeColors[4]; // rgba
    FutureBlendInfo m_colorBlend;
    FutureBlendInfo m_alphaBlend;

	FutureRenderTargetInfo()
		: m_enableBlending(false),
		  m_colorBlend(),
		  m_alphaBlend()
	{
		m_writeColors[0] = m_writeColors[1] = m_writeColors[2] = m_writeColors[3] = true;
	}
};


struct FutureBlendStateInfo
{
	bool						m_enableAlphaToCoverage;
	FutureRenderTargetInfo		m_renderTargets[8];
	f32							m_blendFactors[4];
	u32							m_sampleMask;

	FutureBlendStateInfo()
		: m_enableAlphaToCoverage(false),
		  m_sampleMask(0xFFFFFFFF)
	{
		m_blendFactors[0] = m_blendFactors[1] = m_blendFactors[2] = m_blendFactors[3] = 1.0f;
		memset(m_renderTargets, 0, sizeof(FutureRenderTargetInfo) * 8);
		m_renderTargets[0] = FutureRenderTargetInfo();
	}

};

struct FutureTextureSamplerInfo
{
    f32                             m_minLOD;
    f32                             m_maxLOD;
    f32                             m_mipLODBias;
    
    FutureTextureSamplerFilter      m_filterMin;
    FutureTextureSamplerFilter      m_filterMag;
	FutureTextureSamplerFilter		m_filterMip;
    
    FutureTextureWrapMode           m_wrapModeU;
    FutureTextureWrapMode           m_wrapModeV;
    FutureTextureWrapMode           m_wrapModeW;
    
    FutureComparisonFunction        m_compareFunction;

	FutureTextureSamplerInfo()
		: m_minLOD(-3.402823466e+38f),
		  m_maxLOD(3.402823466e+38f),
		  m_mipLODBias(0.f),
		  m_filterMin(FutureTextureSamplerFilter_LinearMip_LinearPoint),
		  m_filterMag(FutureTextureSamplerFilter_Linear),
		  m_wrapModeU(FutureTextureWrapMode_Clamp),
		  m_wrapModeV(FutureTextureWrapMode_Clamp),
		  m_wrapModeW(FutureTextureWrapMode_Clamp),
		  m_compareFunction(FutureComparisonFunction_Never)
	{}
};

struct FutureRasterizerInfo
{
    bool                        m_wireframe;
	bool						m_counterClockwiseWrapping;
	FutureCullMode              m_cullMode;

	bool						m_depthClipping;
	bool						m_enableScissor;
	bool                        m_enableMultisampling;

	FutureRasterizerInfo()
		: m_wireframe(false),
		  m_counterClockwiseWrapping(false),
		  m_cullMode(FutureCullMode_Back),
		  m_depthClipping(true),
		  m_enableScissor(false),
		  m_enableMultisampling(false)
	{}
};

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

// All objects that may need to be stored in hardware buffers (transferred to the GPU) must extend this
class IFutureHardwareObject
{
public:

	IFutureHardwareObject(){};
	virtual ~IFutureHardwareObject(){}

	virtual bool	ApplyToHardware() = 0;
	virtual bool	RemoveFromHardware() = 0;
	virtual bool	ReapplyToHardware() = 0;

	virtual bool	IsAppliedToHardware() = 0;
};

#endif