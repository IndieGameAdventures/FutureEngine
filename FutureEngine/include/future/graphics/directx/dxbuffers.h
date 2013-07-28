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

#ifndef FUTURE_GRAPHICS_DIRECTX_BUFFERS_H
#define FUTURE_GRAPHICS_DIRECTX_BUFFERS_H

#include <future/graphics/type/type.h>
#include <future/graphics/type/buffers.h>
#include <future/graphics/directx/dxtype.h>

struct FutureHardwareBufferInfo
{
public:
    u32                         m_elements;
	u32							m_size;
	u32							m_stride;
    u32                         m_slice;
	FutureHardwareResourceUsage	m_usage;
};

struct FutureInitialBufferData
{
	void *					m_initialData;
	u32						m_size;
	u32						m_initialStride;
	u32						m_initialSlice;
};


class FutureDXHardwareBuffer : public IFutureHardwareBuffer
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureDXHardwareBuffer);

	FutureDXHardwareBuffer();
	virtual ~FutureDXHardwareBuffer();
    
	virtual void	GetInfo(FutureHardwareBufferInfo & info);
    
	virtual bool	Map(void ** data);
	virtual bool	IsMapped();
	virtual void	UnMap();
    
    virtual void    Release();
    
    virtual IFutureHardwareBuffer *   Clone();
    virtual IFutureHardwareBuffer *   Instance();

protected:
	friend class FutureDXSystem;

	ID3D11Buffer  *				m_buffer;
	FutureHardwareBufferInfo	m_info;
};


#endif