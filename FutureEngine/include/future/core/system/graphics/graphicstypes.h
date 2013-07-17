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
enum FutureRenderPriority
{
	FutureRP_Shadows				= 0x00010000,
	FutureRP_Reflection_SkyDome		= 0x00020000,
	FutureRP_Reflection				= 0x00080000,
	FutureRP_Normal_SkyDome			= 0x00100000,
	FutureRP_Normal					= 0x00400000,
	FutureRP_Water					= 0x00800000,

	FutureRP_Max,
	FutureRP_Nil = -1,
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
// corrosponds 1:1 with DXGI_FORMAT
enum FutureVertexElementType
{
	FutureVertexElementType_Typeless32_4	= 1,
	FutureVertexElementType_F32_4			= 2,
	FutureVertexElementType_U32_4			= 3,
	FutureVertexElementType_S32_4			= 4,

	FutureVertexElementType_Typeless32_3	= 5,
	FutureVertexElementType_F32_3			= 6,
	FutureVertexElementType_U32_3			= 7,
	FutureVertexElementType_S32_3			= 8,

	FutureVertexElementType_Typeless16_4	= 9,
	FutureVertexElementType_F16_4			= 10,
	FutureVertexElementType_UNORM16_4		= 11,
	FutureVertexElementType_U16_4			= 12,
	FutureVertexElementType_SNORM16_4		= 13,
	FutureVertexElementType_S16_4			= 14,

	FutureVertexElementType_Typeless32_2	= 15,
	FutureVertexElementType_F32_2			= 16,
	FutureVertexElementType_U32_2			= 17,
	FutureVertexElementType_S32_2			= 18,

	FutureVertexElementType_Typeless8_4     = 27,
	FutureVertexElementType_UNORM8_4		= 28,
	FutureVertexElementType_U8_4			= 30,
	FutureVertexElementType_SNORM8_4		= 31,
	FutureVertexElementType_S8_4			= 32,

	FutureVertexElementType_Typeless16_2    = 33,
	FutureVertexElementType_F16_2			= 34,
	FutureVertexElementType_UNORM16_2		= 35,
	FutureVertexElementType_U16_2			= 36,
	FutureVertexElementType_SNORM16_2		= 37,
	FutureVertexElementType_S16_2			= 38,

	FutureVertexElementType_Typeless32_1	= 39,
	FutureVertexElementType_F32_1			= 40,
	FutureVertexElementType_U32_1			= 42,
	FutureVertexElementType_S32_1			= 43,

	FutureVertexElementType_Typeless8_2     = 48,
	FutureVertexElementType_UNORM8_2		= 49,
	FutureVertexElementType_U8_2			= 50,
	FutureVertexElementType_SNORM8_2		= 51,
	FutureVertexElementType_S8_2			= 52,

	FutureVertexElementType_Typeless16_1    = 53,
	FutureVertexElementType_F16_1			= 54,
	FutureVertexElementType_UNORM16_1		= 55,
	FutureVertexElementType_U16_1			= 57,
	FutureVertexElementType_SNORM16_1		= 58,
	FutureVertexElementType_S16_1			= 59,

	FutureVertexElementType_Typeless8_1      = 60,
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
    FuturePT_Triangle_List = 0,
    FuturePT_Triangle_Strip,
    FuturePT_Line_List,
    FuturePT_Line_Strip,
    FuturePT_Point_List,
    FuturePT_Triangle_List_Adj,
    FuturePT_Triangle_Strip_Adj,
    FuturePT_Line_List_Adj,
    FuturePT_Line_Strip_Adj,
};

enum FutureIndexType
{
    FutureIT_16bit = 0,
    FutureIT_32bit,
};

#endif