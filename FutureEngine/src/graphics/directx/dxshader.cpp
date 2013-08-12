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

#include <future/graphics/type/type.h>
#include <future/graphics/type/shader.h>
#include <future/graphics/directx/dxtype.h>
#include <future/graphics/directx/dxshader.h>
#include <future/graphics/directx/dxtexture.h>
#include <future/graphics/directx/dxbuffers.h>
#include <future/graphics/directx/dxdevice.h>

			
FutureTexture *			ms_textures[FutureShaderType_Max][D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
FutureHardwareBuffer *	ms_buffers[FutureShaderType_Max][D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
u32						ms_samplers[FutureShaderType_Max][D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT];

FutureShader::FutureShader()
	: m_vertexShader(NULL),
	  m_pixelShader(NULL),
	  m_hullShader(NULL),
	  m_domainShader(NULL),
	  m_geometryShader(NULL),
	  m_computeShader(NULL),
	  m_inputLayout(NULL),
	  m_shaderType(),
	  m_info(),
	  m_isApplied(false)
{}
FutureShader::~FutureShader()
{
	Release();
}

const FutureShaderInfo * FutureShader::GetInfo()
{
	return &m_info;
}
FutureShaderType FutureShader::GetShaderType()
{
	return m_shaderType;
}

void FutureShader::Release()
{
	Remove();

	switch(m_shaderType)
	{
	case FutureShaderType_Compute:
		if(m_computeShader)
		{
			m_computeShader->Release();
			m_computeShader = NULL;
		}break;
	case FutureShaderType_Geometry:
		if(m_geometryShader)
		{
			m_geometryShader->Release();
			m_geometryShader = NULL;
		}break;
	case FutureShaderType_Vertex:
		if(m_vertexShader)
		{
			m_vertexShader->Release();
			m_vertexShader = NULL;
		}break;
	case FutureShaderType_Pixel:
		if(m_pixelShader)
		{
			m_pixelShader->Release();
			m_pixelShader = NULL;
		}break;
	case FutureShaderType_PostTesslation:
		if(m_domainShader)
		{
			m_domainShader->Release();
			m_domainShader = NULL;
		}break;
	case FutureShaderType_PreTesslation:
		if(m_hullShader)
		{
			m_hullShader->Release();
			m_hullShader = NULL;
		}break;
	}

	if(m_inputLayout)
	{
		m_inputLayout->Release();
		m_inputLayout = NULL;
	}
}

IFutureShader * FutureShader::Instance()
{
	return this;
}

bool FutureShader::GetConstantBuffers(u32 startSlot, u32 numBuffers, IFutureHardwareBuffer ** buffersOut)
{
	FUTURE_ASSERT(startSlot + numBuffers < D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
	for(u32 i = 0; i < numBuffers; ++i)
	{
		buffersOut[i] = ms_buffers[m_shaderType][i + startSlot];
	}
	return true;
}
bool FutureShader::GetTextures(u32 startSlot, u32 numTextures, IFutureTexture ** texturesOut)
{
	FUTURE_ASSERT(startSlot + numTextures < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);
	for(u32 i = 0; i < numTextures; ++i)
	{
		texturesOut[i] = ms_textures[m_shaderType][i + startSlot];
	}
	return true;
}
bool FutureShader::GetSamplerStates(u32 startSlot, u32 numSamplers, u32 * samplersOut)
{
	FUTURE_ASSERT(startSlot + numSamplers < D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT);
	for(u32 i = 0; i < numSamplers; ++i)
	{
		samplersOut[i] = ms_samplers[m_shaderType][i + startSlot];
	}
	return true;
}
	
IFutureHardwareBuffer * FutureShader::GetConstantBuffer(u32 slot)
{
	FUTURE_ASSERT(slot < D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
	return ms_buffers[m_shaderType][slot];
}
IFutureTexture * FutureShader::GetTexture(u32 slot)
{
	FUTURE_ASSERT(slot < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);
	return ms_textures[m_shaderType][slot];
}
u32 FutureShader::GetSamplerState(u32 slot)
{
	FUTURE_ASSERT(slot < D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT);
	return ms_samplers[m_shaderType][slot];
}
	
bool FutureShader::SetConstantBuffers(u32 startSlot, u32 numBuffers, IFutureHardwareBuffer ** buffers)
{
	FUTURE_ASSERT(startSlot + numBuffers < D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
	ID3D11Buffer ** bufferList = (ID3D11Buffer**)FUTURE_ALLOC(numBuffers * sizeof(ID3D11Buffer*), L"Shader buffer temp");
	for(u32 i = 0; i < numBuffers; ++i)
	{
		FutureHardwareBuffer * buffer = dynamic_cast<FutureHardwareBuffer*>(buffers[i]);
		if(buffer == NULL)
		{
			return false;
		}
		ms_buffers[m_shaderType][i + startSlot] = buffer;
		bufferList[i] = buffer->m_buffer;
	}
	switch(m_shaderType)
	{
	case FutureShaderType_Compute:
		m_context->CSSetConstantBuffers(startSlot, numBuffers, bufferList);
		break;
	case FutureShaderType_Geometry:
		m_context->GSSetConstantBuffers(startSlot, numBuffers, bufferList);
		break;
	case FutureShaderType_Vertex:
		m_context->VSSetConstantBuffers(startSlot, numBuffers, bufferList);
		break;
	case FutureShaderType_Pixel:
		m_context->PSSetConstantBuffers(startSlot, numBuffers, bufferList);
		break;
	case FutureShaderType_PostTesslation:
		m_context->DSSetConstantBuffers(startSlot, numBuffers, bufferList);
		break;
	case FutureShaderType_PreTesslation:
		m_context->HSSetConstantBuffers(startSlot, numBuffers, bufferList);
		break;
	}
	FUTURE_FREE(bufferList);
	return true;
}
bool FutureShader::SetTextures(u32 startSlot, u32 numTextures, IFutureTexture ** textures)
{
	FUTURE_ASSERT(startSlot + numTextures < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);
	ID3D11ShaderResourceView ** views = (ID3D11ShaderResourceView**)FUTURE_ALLOC(numTextures * sizeof(ID3D11ShaderResourceView*), L"Shader resource view temp");
	for(u32 i = 0; i < numTextures; ++i)
	{
		FutureTexture * texture = dynamic_cast<FutureTexture*>(textures[i]);
		if(texture == NULL || !(texture->m_info.m_target & FutureTextureTarget_ShaderResource))
		{
			return false;
		}
		ms_textures[m_shaderType][i + startSlot] = texture;
		views[i] = texture->m_SRView;
	}
	switch(m_shaderType)
	{
	case FutureShaderType_Compute:
		m_context->CSSetShaderResources(startSlot, numTextures, views);
		break;
	case FutureShaderType_Geometry:
		m_context->GSSetShaderResources(startSlot, numTextures, views);
		break;
	case FutureShaderType_Vertex:
		m_context->VSSetShaderResources(startSlot, numTextures, views);
		break;
	case FutureShaderType_Pixel:
		m_context->PSSetShaderResources(startSlot, numTextures, views);
		break;
	case FutureShaderType_PostTesslation:
		m_context->DSSetShaderResources(startSlot, numTextures, views);
		break;
	case FutureShaderType_PreTesslation:
		m_context->HSSetShaderResources(startSlot, numTextures, views);
		break;
	}
	FUTURE_FREE(views);
	return true;
}
bool FutureShader::SetSamplerStates(u32 startSlot, u32 numSamplers, u32 * samplers)
{
	FUTURE_ASSERT(startSlot + numSamplers < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);
	ID3D11SamplerState ** sam = (ID3D11SamplerState**)FUTURE_ALLOC(numSamplers * sizeof(ID3D11SamplerState*), L"Shader sampler temp");
	FutureGraphicsDevice * device = dynamic_cast<FutureGraphicsDevice*>(m_device);
	for(u32 i = 0; i < numSamplers; ++i)
	{
		ID3D11SamplerState * s = device->m_samplerStates[samplers[i]];
		if(s == NULL)
		{
			return false;
		}
		ms_samplers[m_shaderType][i + startSlot] = samplers[i];
		sam[i] = s;
	}
	switch(m_shaderType)
	{
	case FutureShaderType_Compute:
		m_context->CSSetSamplers(startSlot, numSamplers, sam);
		break;
	case FutureShaderType_Geometry:
		m_context->GSSetSamplers(startSlot, numSamplers, sam);
		break;
	case FutureShaderType_Vertex:
		m_context->VSSetSamplers(startSlot, numSamplers, sam);
		break;
	case FutureShaderType_Pixel:
		m_context->PSSetSamplers(startSlot, numSamplers, sam);
		break;
	case FutureShaderType_PostTesslation:
		m_context->DSSetSamplers(startSlot, numSamplers, sam);
		break;
	case FutureShaderType_PreTesslation:
		m_context->HSSetSamplers(startSlot, numSamplers, sam);
		break;
	}
	FUTURE_FREE(sam);
	return true;
}
	
bool FutureShader::SetConstantBuffer(u32 slot, IFutureHardwareBuffer * buffer)
{
	FUTURE_ASSERT(slot < D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
	FutureHardwareBuffer * b = dynamic_cast<FutureHardwareBuffer*>(buffer);
	if(b == NULL)
	{
		return false;
	}
	ms_buffers[m_shaderType][slot] = b;
	ID3D11Buffer * buf = b->m_buffer;

	switch(m_shaderType)
	{
	case FutureShaderType_Compute:
		m_context->CSSetConstantBuffers(slot, 1, &buf);
		break;
	case FutureShaderType_Geometry:
		m_context->GSSetConstantBuffers(slot, 1, &buf);
		break;
	case FutureShaderType_Vertex:
		m_context->VSSetConstantBuffers(slot, 1, &buf);
		break;
	case FutureShaderType_Pixel:
		m_context->PSSetConstantBuffers(slot, 1, &buf);
		break;
	case FutureShaderType_PostTesslation:
		m_context->DSSetConstantBuffers(slot, 1, &buf);
		break;
	case FutureShaderType_PreTesslation:
		m_context->HSSetConstantBuffers(slot, 1, &buf);
		break;
	}
	return true;
}

bool FutureShader::SetTexture(u32 slot, IFutureTexture * texture)
{
	FUTURE_ASSERT(slot < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);
	FutureTexture * t = dynamic_cast<FutureTexture*>(texture);
	if(t == NULL || !(t->m_info.m_target & FutureTextureTarget_ShaderResource))
	{
		return false;
	}
	ms_textures[m_shaderType][slot] = t;
	ID3D11ShaderResourceView * buf = t->m_SRView;

	switch(m_shaderType)
	{
	case FutureShaderType_Compute:
		m_context->CSSetShaderResources(slot, 1, &buf);
		break;
	case FutureShaderType_Geometry:
		m_context->GSSetShaderResources(slot, 1, &buf);
		break;
	case FutureShaderType_Vertex:
		m_context->VSSetShaderResources(slot, 1, &buf);
		break;
	case FutureShaderType_Pixel:
		m_context->PSSetShaderResources(slot, 1, &buf);
		break;
	case FutureShaderType_PostTesslation:
		m_context->DSSetShaderResources(slot, 1, &buf);
		break;
	case FutureShaderType_PreTesslation:
		m_context->HSSetShaderResources(slot, 1, &buf);
		break;
	}
	return true;
}
bool FutureShader::SetSamplerState(u32 slot, u32 sampler)
{
	FUTURE_ASSERT(slot < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);
	FutureGraphicsDevice * device = dynamic_cast<FutureGraphicsDevice*>(m_device);

	ID3D11SamplerState * s = device->m_samplerStates[sampler];
	if(s == NULL)
	{
		return false;
	}
	ms_samplers[m_shaderType][slot] = sampler;

	switch(m_shaderType)
	{
	case FutureShaderType_Compute:
		m_context->CSSetSamplers(slot, 1, &s);
		break;
	case FutureShaderType_Geometry:
		m_context->GSSetSamplers(slot, 1, &s);
		break;
	case FutureShaderType_Vertex:
		m_context->VSSetSamplers(slot, 1, &s);
		break;
	case FutureShaderType_Pixel:
		m_context->PSSetSamplers(slot, 1, &s);
		break;
	case FutureShaderType_PostTesslation:
		m_context->DSSetSamplers(slot, 1, &s);
		break;
	case FutureShaderType_PreTesslation:
		m_context->HSSetSamplers(slot, 1, &s);
		break;
	}
}
bool FutureShader::Apply()
{
	if(m_isApplied)
	{
		return true;
	}
	switch(m_shaderType)
	{
	case FutureShaderType_Compute:
		m_context->CSSetShader(m_computeShader, NULL, 0);
		break;
	case FutureShaderType_Geometry:
		m_context->GSSetShader(m_geometryShader, NULL, 0);
		break;
	case FutureShaderType_Vertex:
		m_context->VSSetShader(m_vertexShader, NULL, 0);
		break;
	case FutureShaderType_Pixel:
		m_context->PSSetShader(m_pixelShader, NULL, 0);
		break;
	case FutureShaderType_PostTesslation:
		m_context->DSSetShader(m_domainShader, NULL, 0);
		break;
	case FutureShaderType_PreTesslation:
		m_context->HSSetShader(m_hullShader, NULL, 0);
		break;
	}

	if(m_inputLayout)
	{
		m_context->IASetInputLayout(m_inputLayout);
	}
	m_isApplied = true;
	return true;
}
bool FutureShader::IsApplied()
{
	return m_isApplied;
}
bool FutureShader::Remove()
{
	if(!m_isApplied)
	{
		return true;
	}
	
	switch(m_shaderType)
	{
	case FutureShaderType_Compute:
		m_context->CSSetShader(NULL, NULL, 0);
		break;
	case FutureShaderType_Geometry:
		m_context->GSSetShader(NULL, NULL, 0);
		break;
	case FutureShaderType_Vertex:
		m_context->VSSetShader(NULL, NULL, 0);
		break;
	case FutureShaderType_Pixel:
		m_context->PSSetShader(NULL, NULL, 0);
		break;
	case FutureShaderType_PostTesslation:
		m_context->DSSetShader(NULL, NULL, 0);
		break;
	case FutureShaderType_PreTesslation:
		m_context->HSSetShader(NULL, NULL, 0);
		break;
	}

	if(m_inputLayout)
	{
		m_context->IASetInputLayout(NULL);
	}
	m_isApplied = false;
	return true;
}


bool FutureShader::Create(const FutureShaderCreationData * info, ID3D11Device * device, ID3D11DeviceContext * context)
{
	m_device = device;
	m_context = context;

	HRESULT result;
	switch(info->m_shaderType)
	{
	case FutureShaderType_Vertex:
		result = m_device->CreateVertexShader(info->m_shaderByteCode, info->m_shaderSize, NULL, &m_vertexShader);
		break;
	case FutureShaderType_Pixel:
		result = m_device->CreatePixelShader(info->m_shaderByteCode, info->m_shaderSize, NULL, &m_pixelShader);
		break;
	case FutureShaderType_Geometry:
		result = m_device->CreateGeometryShader(info->m_shaderByteCode, info->m_shaderSize, NULL, &m_geometryShader);
		break;
	case FutureShaderType_PreTesslation:
		result = m_device->CreateDomainShader(info->m_shaderByteCode, info->m_shaderSize, NULL, &m_domainShader);
		break;
	case FutureShaderType_PostTesslation:
		result = m_device->CreateHullShader(info->m_shaderByteCode, info->m_shaderSize, NULL, &m_hullShader);
		break;
	case FutureShaderType_Compute:
		result = m_device->CreateComputeShader(info->m_shaderByteCode, info->m_shaderSize, NULL, &m_computeShader);
		break;
	}
	if(FAILED(result))
	{
		FUTURE_LOG_E(L"Failed to create shader with error code %x", result);
		return false;
	}

	if(info->m_shaderType == FutureShaderType_Vertex && info->m_inputLayout.m_numElements > 0)
	{
		D3D11_INPUT_ELEMENT_DESC * desc = new D3D11_INPUT_ELEMENT_DESC[info->m_inputLayout.m_numElements];
		for(u32 i = 0; i < info->m_inputLayout.m_numElements; ++i)
		{
			desc[i].AlignedByteOffset = info->m_inputLayout.m_elements[i].m_alignByteOffset;
			desc[i].Format = FutureTexture::FutureFormatToDXFormat(info->m_inputLayout.m_elements[i].m_type);
			desc[i].InputSlot = info->m_inputLayout.m_elements[i].m_inputSlot;
			desc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			desc[i].SemanticIndex = info->m_inputLayout.m_elements[i].m_sementicIndex;
			desc[i].SemanticName = info->m_inputLayout.m_elements[i].m_inputSementics;
		}
		result = m_device->CreateInputLayout(desc, info->m_inputLayout.m_numElements, info->m_shaderByteCode, info->m_shaderSize, &m_inputLayout);
		
		if(FAILED(result))
		{
			FUTURE_LOG_E(L"Failed to create shader input layout with error code %x", result);
			return false;
		}
	}
	return true;
}