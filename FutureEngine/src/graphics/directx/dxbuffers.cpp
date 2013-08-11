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

#include <future/graphics/directx/dxbuffers.h>

FutureHardwareBuffer::FutureHardwareBuffer()
	: m_buffer(NULL),
	  m_info(),
	  m_isMapped(false),
	  m_context(NULL)
{}
FutureHardwareBuffer::~FutureHardwareBuffer()
{
	Release();
}
    
const FutureHardwareBufferInfo * FutureHardwareBuffer::GetInfo()
{
	return &m_info;
}
    
bool FutureHardwareBuffer::Map(FutureHardwareBufferData * dataOut)
{
	FUTURE_ASSERT(!m_isMapped);
	FUTURE_ASSERT(dataOut && m_buffer);

	D3D11_MAPPED_SUBRESOURCE resource;
	HRESULT result = E_FAIL;
	if(m_info.m_usage & FutureHardwareResourceUsage_Dynamic)
	{
		result = m_context->Map(m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	}
	else if(m_info.m_usage & FutureHardwareResourceUsage_Staging)
	{
		result = m_context->Map(m_buffer, 0, D3D11_MAP_WRITE, 0, &resource);
	}
	
	if(FAILED(result))
	{
		return false;
	}

	m_isMapped = true;
	dataOut->m_data = resource.pData;
	dataOut->m_stride = resource.RowPitch;
	dataOut->m_slice = resource.DepthPitch;
	return true;
}

bool FutureHardwareBuffer::IsMapped()
{
	return m_isMapped;
}
void FutureHardwareBuffer::UnMap()
{
	FUTURE_ASSERT(m_isMapped);
	m_context->Unmap(m_buffer);
	m_isMapped = false;
}
    
bool FutureHardwareBuffer::Update(const FutureHardwareBufferData * data)
{
	FUTURE_ASSERT(data && m_buffer);
	FUTURE_ASSERT(m_info.m_usage & ~FutureHardwareResourceUsage_Locked);
	
	m_context->UpdateSubresource(m_buffer, 0, NULL, data->m_data, data->m_stride, data->m_slice);
}

void FutureHardwareBuffer::Release()
{
	FUTURE_ASSERT_MSG(m_isMapped, L"Buffer must be Unmapped before it can be destroyed");
	if(m_buffer)
	{
		m_buffer->Release();
		m_buffer = NULL;
	}
}
