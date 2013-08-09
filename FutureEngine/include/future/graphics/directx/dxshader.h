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

#ifndef FUTURE_GRAPHICS_DIRECTX_SHADER_H
#define FUTURE_GRAPHICS_DIRECTX_SHADER_H

#include <future/graphics/type/type.h>
#include <future/graphics/type/shader.h>
#include <future/graphics/directx/dxtype.h>

class FutureShader : public IFutureShader
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureShader);
	virtual ~FutureShader(){};

	virtual const FutureShaderInfo * GetInfo();
	virtual FutureShaderType		GetShaderType();

    virtual void					Release();
    
    virtual IFutureShader *			Clone();
    virtual IFutureShader *			Instance();


	virtual bool					GetConstantBuffers(u32 startSlot, u32 numBuffers, IFutureHardwareBuffer ** buffersOut);
	virtual bool					GetTextures(u32 startSlot, u32 numTextures, IFutureTexture ** texturesOut);
	virtual bool					GetSamplerStates(u32 startSlot, u32 numSamplers, u32 * samplersOut);
	
	virtual IFutureHardwareBuffer *	GetConstantBuffer(u32 slot);
	virtual IFutureTexture *		GetTexture(u32 slot);
	virtual u32						GetSamplerState(u32 slot);
	
	virtual bool					SetConstantBuffers(u32 startSlot, u32 numBuffers, IFutureHardwareBuffer ** buffersOut);
	virtual bool					SetTextures(u32 startSlot, u32 numTextures, IFutureTexture ** texturesOut);
	virtual bool					SetSamplerStates(u32 startSlot, u32 numSamplers, u32 * samplersOut);
	
	virtual IFutureHardwareBuffer *	SetConstantBuffer(u32 slot);
	virtual IFutureTexture *		SetTexture(u32 slot);
	virtual u32						SetSamplerState(u32 slot);

	virtual bool					Apply();
	virtual bool					IsApplied();
	virtual bool					Remove();

protected:
	friend class FutureGraphicsDevice;

	union
	{
		ID3D11VertexShader *	m_vertexShader;
		ID3D11PixelShader *		m_pixelShader;
		ID3D11HullShader *		m_hullShader;
		ID3D11DomainShader *	m_domainShader;
		ID3D11GeometryShader *	m_geometryShader;
		ID3D11ComputeShader *	m_computeShader;
	};

	ID3D11InputLayout *	m_inputLayout;

	FutureShaderType	m_shaderType;
	FutureShaderInfo	m_info;
};

#endif