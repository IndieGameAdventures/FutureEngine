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
	  m_isLocked(false),
	  m_mipsCreated(false)
{}

FutureTexture::~FutureTexture()
{
	Release();
}

bool FutureTexture::Map(FutureTextureData * dataOut, u32 subresource)
{
	FUTURE_ASSERT(!m_isLocked);
	FUTURE_ASSERT(dataOut && m_resource && subresource >= 0);

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
	dataOut->m_data = resource.pData;
	dataOut->m_width = resource.RowPitch;
	dataOut->m_height = resource.DepthPitch;
	dataOut->m_format = m_info.m_pixelFormat;
	dataOut->m_depth = m_info.m_depth;
	return true;
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
    
bool FutureTexture::UpdateSubresource(const FutureTextureData * data, u32 subresource)
{
	FUTURE_ASSERT(data && m_resource);
	FUTURE_ASSERT(m_info.m_usage & ~FutureHardwareResourceUsage_Locked);
	
	m_context->UpdateSubresource(m_resource, subresource, NULL, data->m_data, data->m_width, data->m_height);
}

void FutureTexture::Release()
{
	FUTURE_ASSERT_MSG(m_isLocked, L"Texture must be Unmapped before it can be destroyed");
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
	return m_mipsCreated ? m_info.m_mipLevels : 1;
}

const FutureTextureInfo * FutureTexture::GetInfo()
{
	return &m_info;
}
bool FutureTexture::CreateTexture(const FutureTextureInfo * info, const FutureTextureData * data, ID3D11Device * device, ID3D11DeviceContext * context)
{
	m_context = context;
	m_device = device;
	u32	bind = 0;

	switch(info->m_target)
	{
	case FutureTextureTarget_ShaderResource:
		bind |= D3D11_BIND_SHADER_RESOURCE;
		break;
	case FutureTextureTarget_RenderTarget:
		bind |= D3D11_BIND_RENDER_TARGET;
		break;
	case FutureTextureTarget_DepthStencil:
		bind |= D3D11_BIND_DEPTH_STENCIL;
		break;
	}

	if(bind == 0)
	{
		FUTURE_LOG_E(L"Attempted to create texture with an invalid target");
		return false;
	}

	u32 flags = 0;
	if(info->m_usage == FutureHardwareResourceUsage_Dynamic)
	{
		flags = D3D11_CPU_ACCESS_WRITE;
	}
	else if(info->m_usage == FutureHardwareResourceUsage_Staging)
	{
		flags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	}

	bool result = false;
	switch(info->m_type)
	{
	case FutureTextureType_1D:
	case FutureTextureType_1D_Array:
		result = CreateAsTexture1D(info, data, bind, flags);
		break;
	case FutureTextureType_2D:
	case FutureTextureType_2D_Array:
		result = CreateAsTexture2D(info, data, bind, flags);
		break;
	case FutureTextureType_3D:
		result = CreateAsTexture3D(info, data, bind, flags);
		break;
	case FutureTextureType_Cube:
		result = CreateAsTextureCube(info, data, bind, flags);
		break;
	default:
		FUTURE_LOG_E(L"Failed to specify valid texture type");
		return false;
	}
	if(result)
	{
		FUTURE_LOG_E(L"Failed to create texture");
		return false;
	}

	if(info->m_target & FutureTextureTarget_ShaderResource)
	{
		if(!CreateShaderResourceView(info))
		{
			FUTURE_LOG_E(L"Failed to create shader resource view from texture");
			return false;
		}
		if(info->m_generateMipMap)
		{
			if(!CreateMips(info))
			{
				FUTURE_LOG_E(L"Failed to generate mipmap for texture");
				return false;
			}
		}
	}
	if(info->m_target & FutureTextureTarget_RenderTarget)
	{
		if(!CreateRenderTargetView(info))
		{
			FUTURE_LOG_E(L"Failed to create render target view from texture");
			return false;
		}
	}
	if(info->m_target & FutureTextureTarget_DepthStencil)
	{
		if(!CreateDepthStencilView(info))
		{
			FUTURE_LOG_E(L"Failed to create depth stencil view from texture");
			return false;
		}
	}
	memcpy(&m_info, info, sizeof(FutureTextureInfo));

	return true;
}

bool FutureTexture::CreateAsTexture1D(const FutureTextureInfo * info, const FutureTextureData * data, u32 bind, u32 flags)
{
	D3D11_TEXTURE1D_DESC desc;
	desc.Width = info->m_width;
	desc.MipLevels = info->m_mipLevels;
	desc.ArraySize = info->m_arraySize;
	desc.Format = FutureFormatToDXFormat(info->m_pixelFormat);
	desc.Usage = (D3D11_USAGE)info->m_usage;
	desc.BindFlags = bind;
	desc.CPUAccessFlags = flags;
	desc.MiscFlags = info->m_generateMipMap ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;

	HRESULT result;
	if(data && data->m_data)
	{
		if(data->m_format != info->m_pixelFormat)
		{
			FUTURE_LOG_E(L"Attempted to create texture with different initial and end data formats");
			return false;
		}
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = data->m_data;
		initData.SysMemPitch = data->m_width;
		initData.SysMemSlicePitch = data->m_height;
		
		result = m_device->CreateTexture1D(&desc, &initData, &m_texture1d);
	}
	else
	{
		result = m_device->CreateTexture1D(&desc, NULL, &m_texture1d);
	}
	if(FAILED(result))
	{
		FUTURE_LOG_E(L"Failed to create texture, DirectX gave error %x", result);
		return false;
	}
	return true;
}


bool FutureTexture::CreateAsTexture2D(const FutureTextureInfo * info, const FutureTextureData * data, u32 bind, u32 flags)
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = info->m_width;
	desc.Height = info->m_height;
	desc.MipLevels = info->m_mipLevels;
	desc.ArraySize = info->m_arraySize;
	desc.Format = FutureFormatToDXFormat(info->m_pixelFormat);
	desc.SampleDesc.Count = info->m_multisampleCount;
	desc.SampleDesc.Quality = info->m_multisampleQuality;
	desc.Usage = (D3D11_USAGE)info->m_usage;
	desc.BindFlags = bind;
	desc.CPUAccessFlags = flags;
	desc.MiscFlags = info->m_generateMipMap ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;

	HRESULT result;
	if(data && data->m_data)
	{
		if(data->m_format != info->m_pixelFormat)
		{
			FUTURE_LOG_E(L"Attempted to create texture with different initial and end data formats");
			return false;
		}
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = data->m_data;
		initData.SysMemPitch = data->m_width;
		initData.SysMemSlicePitch = data->m_height;
		
		result = m_device->CreateTexture2D(&desc, &initData, &m_texture2d);
	}
	else
	{
		result = m_device->CreateTexture2D(&desc, NULL, &m_texture2d);
	}
	if(FAILED(result))
	{
		FUTURE_LOG_E(L"Failed to create texture, DirectX gave error %x", result);
		return false;
	}
	return true;
}
bool FutureTexture::CreateAsTexture3D(const FutureTextureInfo * info, const FutureTextureData * data, u32 bind, u32 flags)
{
	D3D11_TEXTURE3D_DESC desc;
	desc.Width = info->m_width;
	desc.Height = info->m_height;
	desc.Depth = info->m_depth;
	desc.MipLevels = info->m_mipLevels;
	desc.Format = FutureFormatToDXFormat(info->m_pixelFormat);
	desc.Usage = (D3D11_USAGE)info->m_usage;
	desc.BindFlags = bind;
	desc.CPUAccessFlags = flags;
	desc.MiscFlags = info->m_generateMipMap ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;

	HRESULT result;
	if(data && data->m_data)
	{
		if(data->m_format != info->m_pixelFormat)
		{
			FUTURE_LOG_E(L"Attempted to create texture with different initial and end data formats");
			return false;
		}
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = data->m_data;
		initData.SysMemPitch = data->m_width;
		initData.SysMemSlicePitch = data->m_height;
		
		result = m_device->CreateTexture3D(&desc, &initData, &m_texture3d);
	}
	else
	{
		result = m_device->CreateTexture3D(&desc, NULL, &m_texture3d);
	}
	if(FAILED(result))
	{
		FUTURE_LOG_E(L"Failed to create texture, DirectX gave error %x", result);
		return false;
	}
	return true;
}
bool FutureTexture::CreateAsTextureCube(const FutureTextureInfo * info, const FutureTextureData * data, u32 bind, u32 flags)
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = info->m_width;
	desc.Height = info->m_height;
	desc.MipLevels = info->m_mipLevels;
	desc.ArraySize = info->m_arraySize * 6;
	desc.Format = FutureFormatToDXFormat(info->m_pixelFormat);
	desc.SampleDesc.Count = info->m_multisampleCount;
	desc.SampleDesc.Quality = info->m_multisampleQuality;
	desc.Usage = (D3D11_USAGE)info->m_usage;
	desc.BindFlags = bind;
	desc.CPUAccessFlags = flags;
	desc.MiscFlags = info->m_generateMipMap ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;
	desc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;

	HRESULT result;
	if(data && data->m_data)
	{
		if(data->m_format != info->m_pixelFormat)
		{
			FUTURE_LOG_E(L"Attempted to create texture with different initial and end data formats");
			return false;
		}
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = data->m_data;
		initData.SysMemPitch = data->m_width;
		initData.SysMemSlicePitch = data->m_height;
		
		result = m_device->CreateTexture2D(&desc, &initData, &m_texture2d);
	}
	else
	{
		result = m_device->CreateTexture2D(&desc, NULL, &m_texture2d);
	}
	if(FAILED(result))
	{
		FUTURE_LOG_E(L"Failed to create texture, DirectX gave error %x", result);
		return false;
	}
	return true;
}


bool FutureTexture::CreateRenderTargetView(const FutureTextureInfo * info)
{
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	desc.Format = FutureFormatToDXFormat(info->m_pixelFormat);
	switch(info->m_type)
	{
	case FutureTextureType_1D:
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
		desc.Texture1D.MipSlice = 0;
		break;
	case FutureTextureType_1D_Array:
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1DARRAY;
		desc.Texture1DArray.MipSlice = 0;
		desc.Texture1DArray.FirstArraySlice = 0;
		desc.Texture1DArray.ArraySize = info->m_arraySize;
		break;
	case FutureTextureType_2D:
		if(info->m_multisampleCount > 1)
		{
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipSlice = 0;
		}
		break;
	case FutureTextureType_2D_Array:
	case FutureTextureType_Cube:
		if(info->m_multisampleCount > 1)
		{
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
			desc.Texture2DMSArray.FirstArraySlice = 0;
			desc.Texture2DMSArray.ArraySize = info->m_arraySize;
		}
		else
		{
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.MipSlice = 0;
			desc.Texture2DArray.FirstArraySlice = 0;
			desc.Texture2DArray.ArraySize = info->m_arraySize * 6;
		}
		break;
	case FutureTextureType_3D:
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
		desc.Texture3D.MipSlice = 0;
		desc.Texture3D.FirstWSlice = 0;
		desc.Texture3D.WSize = -1;
		break;
	}
	
	HRESULT result = m_device->CreateRenderTargetView(m_resource, &desc, &m_RTView);
	if(FAILED(result))
	{
		FUTURE_LOG_E(L"Failed to create Render Target View with DirectX Error %x", result);
		return false;
	}
	return m_RTView != NULL;
}
bool FutureTexture::CreateDepthStencilView(const FutureTextureInfo * info)
{
	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	desc.Format = FutureFormatToDXFormat(info->m_pixelFormat);
	desc.Flags = 0;
	switch(info->m_type)
	{
	case FutureTextureType_1D:
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1D;
		desc.Texture1D.MipSlice = 0;
		break;
	case FutureTextureType_1D_Array:
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1DARRAY;
		desc.Texture1DArray.MipSlice = 0;
		desc.Texture1DArray.FirstArraySlice = 0;
		desc.Texture1DArray.ArraySize = info->m_arraySize;
		break;
	case FutureTextureType_2D:
		if(info->m_multisampleCount > 1)
		{
			desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipSlice = 0;
		}
		break;
	case FutureTextureType_2D_Array:
	case FutureTextureType_Cube:
		if(info->m_multisampleCount > 1)
		{
			desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
			desc.Texture2DMSArray.FirstArraySlice = 0;
			desc.Texture2DMSArray.ArraySize = info->m_arraySize;
			if(info->m_type == FutureTextureType_Cube)
			{
				desc.Texture2DMSArray.ArraySize *= 6;
			}
		}
		else
		{
			desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.MipSlice = 0;
			desc.Texture2DArray.FirstArraySlice = 0;
			desc.Texture2DArray.ArraySize = info->m_arraySize;
			if(info->m_type == FutureTextureType_Cube)
			{
				desc.Texture2DArray.ArraySize *= 6;
			}
		}
		break;
	case FutureTextureType_3D:
	default:
		FUTURE_LOG_E(L"3D Textures cannot be used a Depth Stencil Views");
		return false;
	}
	
	HRESULT result = m_device->CreateDepthStencilView(m_resource, &desc, &m_DSView);
	if(FAILED(result))
	{
		FUTURE_LOG_E(L"Failed to create Depth Stencil View with DirectX Error %x", result);
		return false;
	}
	return m_DSView != NULL;
}
bool FutureTexture::CreateShaderResourceView(const FutureTextureInfo * info)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = FutureFormatToDXFormat(info->m_pixelFormat);
	switch(info->m_type)
	{
	case FutureTextureType_1D:
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
		desc.Texture1D.MipLevels = info->m_mipLevels;
		desc.Texture1D.MostDetailedMip = 0;
		break;
	case FutureTextureType_1D_Array:
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
		desc.Texture1DArray.MipLevels = info->m_mipLevels;
		desc.Texture1DArray.MostDetailedMip = 0;
		desc.Texture1DArray.FirstArraySlice = 0;
		desc.Texture1DArray.ArraySize = info->m_arraySize;
		break;
	case FutureTextureType_2D:
		if(info->m_multisampleCount > 1)
		{
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipLevels = info->m_mipLevels;
			desc.Texture2D.MostDetailedMip = 0;
		}
		break;
	case FutureTextureType_2D_Array:
		if(info->m_multisampleCount > 1)
		{
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
			desc.Texture2DMSArray.FirstArraySlice = 0;
			desc.Texture2DMSArray.ArraySize = info->m_arraySize;
		}
		else
		{
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.MipLevels = info->m_mipLevels;
			desc.Texture2DArray.MostDetailedMip = 0;
			desc.Texture2DArray.FirstArraySlice = 0;
			desc.Texture2DArray.ArraySize = info->m_arraySize;
		}
		break;
	case FutureTextureType_3D:
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
		desc.Texture3D.MipLevels = info->m_mipLevels;
		desc.Texture3D.MostDetailedMip = 0;
		break;
	case FutureTextureType_Cube:
		if(info->m_arraySize > 1)
		{
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
			desc.TextureCubeArray.First2DArrayFace = 0; 
			desc.TextureCubeArray.MostDetailedMip = 0;
			desc.TextureCubeArray.MipLevels = info->m_mipLevels;
			desc.TextureCubeArray.NumCubes = info->m_arraySize;
		}
		else
		{
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
			desc.TextureCube.MostDetailedMip = 0;
			desc.TextureCube.MipLevels = info->m_mipLevels;
		}
		break;
	}
	
	HRESULT result = m_device->CreateShaderResourceView(m_resource, &desc, &m_SRView);
	if(FAILED(result))
	{
		FUTURE_LOG_E(L"Failed to create Shader Resource View with DirectX Error %x", result);
		return false;
	}
	return m_SRView != NULL;
}

bool FutureTexture::CreateMips(const FutureTextureInfo * info)
{
	m_context->GenerateMips(m_SRView);
	m_mipsCreated = true;
}


DXGI_FORMAT	FutureTexture::FutureFormatToDXFormat(FutureDataFormat format)
{
	return (DXGI_FORMAT)format;
}