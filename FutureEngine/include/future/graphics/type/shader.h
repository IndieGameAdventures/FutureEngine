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

#ifndef FUTURE_GRAPHICS_SHADER_H
#define FUTURE_GRAPHICS_SHADER_H

#include <future/graphics/type/type.h>
#include <future/graphics/type/texture.h>
#include <future/graphics/type/settings.h>
#include <future/graphics/type/buffers.h>

enum FutureShaderType
{
    FutureShaderType_Vertex,
    FutureShaderType_PreTesslation,
    FutureShaderType_PostTesslation,
    FutureShaderType_Geometry,
    FutureShaderType_Pixel,
    FutureShaderType_Compute,

	FutureShaderType_Max,
};

struct FutureShaderInfo
{
	u8							m_majorVersion;
	u8							m_minorVersion;

	FutureShaderType			m_shaderType;

	const FutureInputLayoutInfo	m_inputLayout;
};

struct FutureShaderCreationData
{
	void *					m_shaderByteCode;
	u32						m_shaderSize;

	FutureInputLayoutInfo	m_inputLayout;
};

class IFutureShader : public FutureManagedObject
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(IFutureShader);
	virtual ~IFutureShader(){};

	virtual const FutureShaderInfo * GetInfo() = 0;
	virtual FutureShaderType		GetShaderType() = 0;

    virtual void					Release() = 0;
    
    virtual IFutureShader *			Clone() = 0;
    virtual IFutureShader *			Instance() = 0;


	virtual bool					GetConstantBuffers(u32 startSlot, u32 numBuffers, IFutureHardwareBuffer ** buffersOut) = 0;
	virtual bool					GetTextures(u32 startSlot, u32 numTextures, IFutureTexture ** texturesOut) = 0;
	virtual bool					GetSamplerStates(u32 startSlot, u32 numSamplers, u32 * samplersOut) = 0;
	
	virtual IFutureHardwareBuffer *	GetConstantBuffer(u32 slot) = 0;
	virtual IFutureTexture *		GetTexture(u32 slot) = 0;
	virtual u32						GetSamplerState(u32 slot) = 0;
	
	virtual bool					SetConstantBuffers(u32 startSlot, u32 numBuffers, IFutureHardwareBuffer ** buffersOut) = 0;
	virtual bool					SetTextures(u32 startSlot, u32 numTextures, IFutureTexture ** texturesOut) = 0;
	virtual bool					SetSamplerStates(u32 startSlot, u32 numSamplers, u32 * samplersOut) = 0;
	
	virtual IFutureHardwareBuffer *	SetConstantBuffer(u32 slot) = 0;
	virtual IFutureTexture *		SetTexture(u32 slot) = 0;
	virtual u32						SetSamplerState(u32 slot) = 0;

	virtual bool					Apply() = 0;
	virtual bool					IsApplied() = 0;
	virtual bool					Remove() = 0;
};

#endif