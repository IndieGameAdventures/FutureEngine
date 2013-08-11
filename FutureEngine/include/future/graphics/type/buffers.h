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
*	Hardware and software buffer interfaces used by the graphics system
*/

#ifndef FUTURE_GRAPHICS_BUFFERS_H
#define FUTURE_GRAPHICS_BUFFERS_H

#include <future/graphics/type/type.h>
#include <future/core/object/managedobject.h>
#include <future/core/object/clonable.h>

enum FutureHardwareBufferType
{
	FutureHardwareBuffer_VertexBuffer	= 1,
	FutureHardwareBuffer_IndexBuffer	= 2,
	FutureHardwareBuffer_ConstantBuffer	= 4,
	//FutureHardwareBuffer_ShaderResource	= 8,
	//FutureHardwareBuffer_StreamOutput	= 10,
};

struct FutureHardwareBufferInfo
{
public:
    u32                         m_elements;
	u32							m_size;
	u32							m_stride;
    u32                         m_slice;
	FutureHardwareResourceUsage	m_usage;
	FutureHardwareBufferType	m_type;
};

struct FutureHardwareBufferData
{
	void *					m_data;
	u32						m_size;
	u32						m_stride;
	u32						m_slice;
};


class IFutureHardwareBuffer : public FutureManagedObject
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(IFutureHardwareBuffer);

	virtual ~IFutureHardwareBuffer(){};
    
	virtual const FutureHardwareBufferInfo *	GetInfo() = 0;
    
	virtual bool					Map(FutureHardwareBufferData * dataOut) = 0;
	virtual bool					IsMapped() = 0;
	virtual void					UnMap() = 0;
    
	virtual bool					Update(const FutureHardwareBufferData * data) = 0;

    virtual void					Release() = 0;
};


#endif