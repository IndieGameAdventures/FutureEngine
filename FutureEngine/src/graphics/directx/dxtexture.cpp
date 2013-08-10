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

#include <future/graphics/directx/dxtexture.h>

FutureTexture::FutureTexture()
	: m_texture1d(NULL),
	  m_texture2d(NULL),
	  m_texture3d(NULL),
	  m_SRView(NULL),
	  m_RTView(NULL),
	  m_DSView(NULL),
	  m_context(NULL),
	  m_info(),
	  m_isLocked(false)
{}

FutureTexture::~FutureTexture()
{
	Release();
}

bool FutureTexture::Map(void ** data, u32 subresource)
{
	FUTURE_ASSERT(!m_isLocked);
	FUTURE_ASSERT(data && m_resource);

	D3D11_MAPPED_SUBRESOURCE resource;
	HRESULT result = E_FAIL;
	if(m_info.m_usage & FutureHardwareResourceUsage_Dynamic)
	{
		result = m_context->Map(m_resource, subresource, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	}
	else if(m_info.m_usage & FutureHardwareResourceUsage_Staging)
	{
		result = m_context->Map(m_resource, subresource, D3D11_MAP_WRITE, 0, &resource);
	}
	
	if(FAILED(result))
	{
		return false;
	}

	m_isLocked = true;
	m_mappedResource = subresource;
	*data = resource.pData;
}

bool FutureTexture::IsMapped()
{
	return m_isLocked;
}
void FutureTexture::UnMap()
{
	FUTURE_ASSERT(m_isLocked);
	m_context->Unmap(m_resource, m_mappedResource);
	m_isLocked = false;
}
    
bool FutureTexture::UpdateSubresource(const FutureInitialTextureData * data, u32 subresource)
{
	FUTURE_ASSERT(data && m_resource);
	FUTURE_ASSERT(m_info.m_usage & ~FutureHardwareResourceUsage_Locked);
	
	m_context->UpdateSubresource(m_resource, subresource, NULL, data->m_initialData, data->m_initialWidth, data->m_initialHeight);
	
}

void FutureTexture::Release()
{
	switch(m_info.m_type)
	{
	case FutureTextureType_1D:
	case FutureTextureType_1D_Array:
		m_texture1d->Release();
		m_texture1d = NULL;
		break;
	case FutureTextureType_2D:
	case FutureTextureType_2D_Array:
	case FutureTextureType_Cube:
		m_texture2d->Release();
		m_texture2d = NULL;
		break;
	case FutureTextureType_3D:
	case FutureTextureType_3D_Array:
		m_texture3d->Release();
		m_texture3d = NULL;
		break;
	}
	if(m_SRView)
	{
		m_SRView->Release();
		m_SRView = NULL;
	}
	if(m_RTView)
	{
		m_RTView->Release();
		m_RTView = NULL;
	}
	if(m_DSView)
	{
		m_DSView->Release();
		m_DSView = NULL;
	}
}
    
u32 FutureTexture::Height()
{
	return m_info.m_height;
}

u32 FutureTexture::Weight()
{
	return m_info.m_width;
}
u32 FutureTexture::Depth()
{
	return m_info.m_depth;
}

u8 FutureTexture::MipLevels()
{
	return m_info.m_mipLevels;
}

IFutureTexture * FutureTexture::Instance()
{
	FutureTexture * tex = new FutureTexture();
	switch(m_info.m_type)
	{
	case FutureTextureType_1D:
	case FutureTextureType_1D_Array:
		if(m_texture1d)
		{
			tex->m_texture1d = m_texture1d;
			m_texture1d->AddRef();
		}
		break;
	case FutureTextureType_2D:
	case FutureTextureType_2D_Array:
	case FutureTextureType_Cube:
		if(m_texture1d)
		{
			tex->m_texture2d = m_texture2d;
			m_texture1d->AddRef();
		}
		break;
	case FutureTextureType_3D:
	case FutureTextureType_3D_Array:
		if(m_texture1d)
		{
			tex->m_texture3d = m_texture3d;
			m_texture1d->AddRef();
		}
		break;
	}
	tex->m_SRView = m_SRView;
	tex->m_RTView = m_RTView;
	tex->m_DSView = m_DSView;

	if(m_SRView)
	{
		m_SRView->AddRef();
	}
	if(m_RTView)
	{
		m_RTView->AddRef();
	}
	if(m_DSView)
	{
		m_DSView->AddRef();
	}

	memcpy(&tex->m_info, &m_info, sizeof(FutureTextureInfo));
	return tex;
}

const FutureTextureInfo * FutureTexture::GetInfo()
{
	return &m_info;
}