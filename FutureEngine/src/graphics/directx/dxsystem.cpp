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
*/

#include <future/graphics/directx/dxsystem.h>
#include <future/core/system/windows/window_win.h>

FutureDXGraphicsSystem::FutureDXGraphicsSystem()
		: m_majorVersion(11),
		  m_minorVersion(0),
		  m_factory(NULL),
		  m_adapter(NULL),
		  m_swapChain(NULL),
		  m_device(NULL),
		  m_deviceContext(NULL),
		  m_rasterStates(),
		  m_rasterInfo(),
		  m_currentRasterState(0),
		  m_depthStencilStates(),
		  m_depthStencilInfo(),
		  m_currentDepthStencilState(0),
		  m_blendStates(),
		  m_blendInfo(),
		  m_currentBlendState(0),
		  m_samplerStates(),
		  m_samplerInfo(),
		  m_currentSamplerState(0),
		  m_vertexBuffer(NULL),
		  m_indexBuffer(NULL),
		  m_primitiveType(FuturePrimitiveType_Triangle_List),
		  m_depthStencil(NULL),
		  m_renderTarget(NULL),
		  m_backBuffer(NULL),
		  m_deviceCallbacks(),
		  m_usingVersion1(false),
		  m_usingVersion2(false)
	{
		for(u32 i = 0; i < FutureShaderType_Max; ++i)
		{
			m_activeShaders[i] = NULL;
		}
	}

FutureDXGraphicsSystem::~FutureDXGraphicsSystem()
{
	if(HasDevice())
	{
		DestroyDevice();
	}
}

bool    FutureDXGraphicsSystem::CreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings)
{
	FUTURE_ASSERT(!HasDevice());

	HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_factory);
	if(FAILED(result))
	{
		return false;
	}
	m_factory->MakeWindowAssociation(((FutureWindow*)window)->GetWindow(), 0);
	
	m_settings.m_fullScreen = settings.m_fullScreen;

	u32 adapter = 0;
	u32 output = 0;
	D3D_FEATURE_LEVEL featureLevel;
	D3D_FEATURE_LEVEL acceptableLevels[] = {D3D_FEATURE_LEVEL_10_0,	D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_11_1};
	u32 createFlags = 0;
	if(settings.m_tryDebug)
	{
		m_settings.m_debug = true;
		createFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}
	if(settings.m_singleThreaded)
	{
		m_settings.m_singleThreaded = true;
		createFlags |= D3D11_CREATE_DEVICE_SINGLETHREADED;
	}
	while(m_factory->EnumAdapters(adapter, &m_adapter) != DXGI_ERROR_NOT_FOUND)
	{
		while(m_adapter->EnumOutputs(0, &m_output) != DXGI_ERROR_NOT_FOUND)
		{

			u32 modes;
			result = m_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &modes, NULL);
			if(FAILED(result))
			{
				continue;
			}

			DXGI_MODE_DESC * displayModeList = new DXGI_MODE_DESC[modes];
			result = m_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &modes, displayModeList);
			if(FAILED(result))
			{
				continue;
			}

			m_settings.m_adapterDisplayFormat = FutureDataFormat_RGBA_U8NORM;

			u32 closest = -1;
			u32 difference = 50000;
			for(u32 i = 0; i < modes; ++i)
			{
				f32 aspect = (f32)displayModeList[i].Width / (f32)displayModeList[i].Height;
				if(	displayModeList[i].Width < settings.m_minBackBufferWidth || 
					displayModeList[i].Width > settings.m_maxBackBufferWidth ||
					displayModeList[i].Height < settings.m_minBackBufferHeight || 
					displayModeList[i].Height > settings.m_maxBackBufferHeight ||
					(settings.m_forceAspectRatio != 0 && (aspect < settings.m_forceAspectRatio ? settings.m_forceAspectRatio - aspect : aspect - settings.m_forceAspectRatio) > 0.0001))
				{
					continue;
				}
				f32 diffW = displayModeList[i].Width - settings.m_targetBackBufferWidth;
				f32 diffH = displayModeList[i].Height - settings.m_targetBackBufferHeight;
				if(diffW < 0){ diffW = -diffW; }
				if(diffH < 0){ diffH = -diffH; }
				if(difference < diffW + diffH)
				{
					difference = diffW + diffH;
					closest = i;
				}
			}

			if(closest < 0)
			{
				continue;
			}

			m_settings.m_backBufferWidth = displayModeList[closest].Width;
			m_settings.m_backBufferHeight = displayModeList[closest].Height;
			m_settings.m_refreshRateNumerator = displayModeList[closest].RefreshRate.Numerator;
			m_settings.m_refreshRateDenominator = displayModeList[closest].RefreshRate.Denominator;

			delete [] displayModeList;
			displayModeList = 0;

			DXGI_SWAP_CHAIN_DESC swapDesc;

			swapDesc.BufferCount = 1;
			swapDesc.BufferDesc.Width = m_settings.m_backBufferWidth;
			swapDesc.BufferDesc.Height = m_settings.m_backBufferHeight;
			swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapDesc.BufferDesc.RefreshRate.Numerator = m_settings.m_refreshRateNumerator;
			swapDesc.BufferDesc.RefreshRate.Denominator = m_settings.m_refreshRateDenominator;
			swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapDesc.OutputWindow = ((FutureWindow*)window)->GetWindow();

			m_settings.m_multisampleCount = settings.m_multisampleCount;
			m_settings.m_multisampleQuality = settings.m_multisampleQuality;

			swapDesc.SampleDesc.Count = m_settings.m_multisampleCount;
			swapDesc.SampleDesc.Quality = m_settings.m_multisampleQuality;
	
			swapDesc.Windowed = !m_settings.m_fullScreen;

			swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			result = D3D11CreateDeviceAndSwapChain(m_adapter, D3D_DRIVER_TYPE_UNKNOWN, (HMODULE)0,
													createFlags, acceptableLevels, 4,
													D3D11_SDK_VERSION, &swapDesc, &m_swapChain, 
													&m_device, &featureLevel, &m_deviceContext );

			if(SUCCEEDED(result))
			{
				m_settings.m_driverType = FutureGraphicsDriverType_Hardware;
				break;
			}

			m_output->Release();
			m_output = NULL;
		}
		if(!m_device || !m_swapChain || !m_deviceContext)
		{
			m_adapter->Release();
			m_adapter = NULL;
		}
		else
		{
			break;
		}
	}
	
	if(!m_device || !m_swapChain || !m_deviceContext)
	{
		if(m_output)
		{
			m_output->Release();
			m_output = NULL;
		}
		if(m_adapter)
		{
			m_adapter->Release();
			m_adapter = NULL;
		}

		DXGI_SWAP_CHAIN_DESC swapDesc;

		swapDesc.BufferCount = 1;
		swapDesc.BufferDesc.Width = m_settings.m_backBufferWidth;
		swapDesc.BufferDesc.Height = m_settings.m_backBufferHeight;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.OutputWindow = ((FutureWindow*)window)->GetWindow();

		m_settings.m_multisampleCount = 1;
		m_settings.m_multisampleQuality = 0;

		swapDesc.SampleDesc.Count = m_settings.m_multisampleCount;
		swapDesc.SampleDesc.Quality = m_settings.m_multisampleQuality;
	
		swapDesc.Windowed = !m_settings.m_fullScreen;

		swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_SOFTWARE, (HMODULE)0,
												createFlags, acceptableLevels, 4,
												D3D11_SDK_VERSION, &swapDesc, &m_swapChain, 
												&m_device, &featureLevel, &m_deviceContext );
		if(FAILED(result))
		{
			DestroyDevice();
			return false;
		}
		m_settings.m_driverType = FutureGraphicsDriverType_Software;
	}

	DXGI_ADAPTER_DESC adapterDesc;
	result = m_adapter->GetDesc(&adapterDesc);
	if(FAILED(result))
	{
		DestroyDevice();
		return false;
	}

	m_settings.m_adapterInfo.m_dedicatedSystemMemory = adapterDesc.DedicatedSystemMemory;
	m_settings.m_adapterInfo.m_dedicatedVideoMemory = adapterDesc.DedicatedVideoMemory;
	m_settings.m_adapterInfo.m_deviceId = adapterDesc.DeviceId;
	m_settings.m_adapterInfo.m_revision = adapterDesc.Revision;
	m_settings.m_adapterInfo.m_sharedSystemMemory = adapterDesc.SharedSystemMemory;
	m_settings.m_adapterInfo.m_subSysId = adapterDesc.SubSysId;
	m_settings.m_adapterInfo.m_vendorId = adapterDesc.VendorId;

	size_t length;
	wcstombs_s(&length, m_settings.m_adapterInfo.m_description, adapterDesc.Description, 128);

	if(featureLevel == D3D_FEATURE_LEVEL_10_0)
	{
		m_settings.m_deviceMajorVersion = 10;
		m_settings.m_deviceMinorVersion = 0;
	}
	else if(featureLevel == D3D_FEATURE_LEVEL_10_1)
	{
		m_settings.m_deviceMajorVersion = 10;
		m_settings.m_deviceMinorVersion = 1;
	}
	else if(featureLevel == D3D_FEATURE_LEVEL_11_0)
	{
		m_settings.m_deviceMajorVersion = 11;
		m_settings.m_deviceMinorVersion = 0;
	}
	else if(featureLevel == D3D_FEATURE_LEVEL_11_1)
	{
		m_settings.m_deviceMajorVersion = 11;
		m_settings.m_deviceMinorVersion = 1;
	}
	m_settings.m_deviceType = FutureGraphicsDeviceType_DirectX;

	m_settings.m_rasterizer.m_wireframe = settings.m_rasterizer.m_wireframe;
	m_settings.m_rasterizer.m_counterClockwiseWrapping = settings.m_rasterizer.m_counterClockwiseWrapping;
	m_settings.m_rasterizer.m_cullMode = settings.m_rasterizer.m_cullMode;
	m_settings.m_rasterizer.m_depthClipping = settings.m_rasterizer.m_depthClipping;
	m_settings.m_rasterizer.m_enableScissor = settings.m_rasterizer.m_enableScissor;
	m_settings.m_rasterizer.m_enableMultisampling = settings.m_rasterizer.m_enableMultisampling;
			
	s32 rasterState = CreateRasterizerState(m_settings.m_rasterizer);
	if(rasterState < 0)
	{
		DestroyDevice();
		return false;
	}
	SetRasterizerState(rasterState);

	FutureViewport view;
	view.m_left = 0.f;
	view.m_right = (f32)m_settings.m_backBufferWidth;
	view.m_top = 0.f;
	view.m_bottom = (f32)m_settings.m_backBufferHeight;
	view.m_near = 0.f;
	view.m_far = 1.f;
	SetViewport(view);

	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_backBuffer);
	if(FAILED(result))
	{
		DestroyDevice();
		return false;
	}

	ID3D11RenderTargetView * renderTarget;
	result = m_device->CreateRenderTargetView(m_backBuffer, NULL, &renderTarget);
	if(FAILED(result))
	{
		DestroyDevice();
		return false;
	}

	m_renderTarget = new FutureDXTexture();
	m_renderTarget->m_texture = m_backBuffer;
	m_renderTarget->m_RTView = renderTarget;
	m_renderTarget->m_info.m_width = m_settings.m_backBufferWidth;
	m_renderTarget->m_info.m_height = m_settings.m_backBufferHeight;
	m_renderTarget->m_info.m_depth = 1;
	m_renderTarget->m_info.m_multisampleCount = 1;
	m_renderTarget->m_info.m_multisampleQuality = 0;
	m_renderTarget->m_info.m_arraySize = 1;
	m_renderTarget->m_info.m_generateMipMap = false;
	m_renderTarget->m_info.m_mipLevels = 1;
	m_renderTarget->m_info.m_pixelFormat = FutureDataFormat_RGBA_U8NORM;
	m_renderTarget->m_info.m_type = FutureTextureType_2D;
	m_renderTarget->m_info.m_usage = FutureHardwareResourceUsage_Default;
	m_renderTarget->m_info.m_target = FutureTextureTarget_RenderTarget;

	if(settings.m_createDefaultDepthBuffer)
	{
		FutureTextureInfo depthInfo;
		depthInfo.m_width = m_settings.m_backBufferWidth;
		depthInfo.m_height = m_settings.m_backBufferHeight;
		depthInfo.m_depth = 1;
		depthInfo.m_multisampleCount = 1;
		depthInfo.m_multisampleQuality = 0;
		depthInfo.m_arraySize = 1;
		depthInfo.m_generateMipMap = false;
		depthInfo.m_mipLevels = 1;
		depthInfo.m_pixelFormat = FutureDataFormat_D_F32;
		depthInfo.m_type = FutureTextureType_2D;
		depthInfo.m_usage = FutureHardwareResourceUsage_Default;
		depthInfo.m_target = FutureTextureTarget_DepthStencil;

		FutureInitialTextureData initialTextureData;
		if(!CreateTexture(depthInfo, initialTextureData, (IFutureTexture**)&m_depthStencil))
		{
			DestroyDevice();
			return false;
		}

		/*D3D11_TEXTURE2D_DESC depthDesc;

		depthDesc.Width = ;
		depthDesc.Height = m_settings.m_backBufferHeight;
		depthDesc.MipLevels = 1;
		depthDesc.ArraySize = 1;
		depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthDesc.SampleDesc.Count = 1;
		depthDesc.SampleDesc.Quality = 0;
		depthDesc.Usage = D3D11_USAGE_DEFAULT;
		depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthDesc.CPUAccessFlags = 0;
		depthDesc.MiscFlags = 0;

		result = pState()->m_d3d11Device->CreateTexture2D(&depthDesc, NULL, &m_depthStencil);

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		pState()->m_d3d11Device->CreateDepthStencilView( pState()->m_d3d11DepthStencil, &descDSV, &pState()->m_d3d11DepthStencilView );*/
	}

	m_deviceContext->OMSetRenderTargets(1, &m_renderTarget->m_RTView, m_depthStencil ? m_depthStencil->m_DSView : NULL);

	if(settings.m_createDefaultDepthStencil)
	{
		s32 stencilState = CreateDepthStencilState(settings.m_stencilInfo);
		if(stencilState >= 0)
		{
			SetDepthStencilState(stencilState);
		}
		SetRasterizerState(rasterState);


		m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	}
}

bool    FutureDXGraphicsSystem::RecreateDevice(IFutureWindow * window, const FutureGraphicsDeviceCreationSettings & settings);\
{

}

void    FutureDXGraphicsSystem::DestroyDevice()
{

	if(m_deviceContext )
	{
		m_deviceContext->ClearState();
	}
	if(m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, NULL);
	}

	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;

	if(m_depthStencil)
	{
		m_depthStencil->Release();
		m_depthStencil = NULL;
	}
	if(m_renderTarget)
	{
		m_renderTarget->Release();
		m_renderTarget = NULL;
	}
	if(m_backBuffer)
	{
		m_backBuffer->Release();
		m_backBuffer = NULL;
	}
	if(m_factory)
	{
		m_factory->Release();
		m_factory = NULL;
	}
	if(m_adapter)
	{
		m_adapter->Release();
		m_adapter = NULL;
	}
	if(m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = NULL;
	}
	if(m_device)
	{
		m_device->Release();
		m_device = NULL;
	}
	if(m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = NULL;
	}

	m_rasterStates.Clear();
	m_rasterInfo.Clear();
	m_depthStencilStates.Clear();
	m_depthStencilInfo.Clear();
	m_blendStates.Clear();
	m_blendInfo.Clear();
	m_samplerStates.Clear();
	m_samplerInfo.Clear();

	CallDeviceLost();
}

bool						FutureDXGraphicsSystem::HasDevice()
{
	return m_device != NULL;
}

void *						FutureDXGraphicsSystem::GetDevice()
{
	return m_device;
}

FutureGraphicsSettings *	FutureDXGraphicsSystem::GraphicsSettings();
{
	return m_settings;
}
   
bool						FutureDXGraphicsSystem::IsFeatureSupported(FutureDeviceSupport feature)
{
	switch(feature)
	{
		case FutureDeviceSupport_CoreFeatures:
			return true;
		case FutureDeviceSupport_Multisample:
			return m_settings.m_multisampleCount > 1;
		case FutureDeviceSupport_TextureCubemap:
			return true;
		case FutureDeviceSupport_RenderToTexture:
			return true;
		case FutureDeviceSupport_Depth_Stencil:
			return true;
		case FutureDeviceSupport_VertexShader:
			return true;
		case FutureDeviceSupport_PixelShader:
			return true;
		case FutureDeviceSupport_VertexBuffer:
			return true;
		case FutureDeviceSupport_IndexBuffer:
			return true;
		case FutureDeviceSupport_PixelBuffer:
			return true;
		case FutureDeviceSupport_NonUniformTexture:
			return true;
		case FutureDeviceSupport_Instancing:
			return true;
		case FutureDeviceSupport_RenderTarget:
			return true;
		case FutureDeviceSupport_GeometryShader:
			return true;
		case FutureDeviceSupport_Texture1D:
			return true;
		case FutureDeviceSupport_Texture2D:
			return true;
		case FutureDeviceSupport_Texture3D:
			return true;
		case FutureDeviceSupport_TextureArrays:
			return true;
		case FutureDeviceSupport_TextureSamplers:
			return true;
		case FutureDeviceSupport_ShaderSubroutine:
			return true;
		case FutureDeviceSupport_TesslationShaders:
			return m_settings.m_deviceMajorVersion >= 11;
		case FutureDeviceSupport_ComputeShaders:
			return m_settings.m_deviceMajorVersion >= 11;
		case FutureDeviceSupport_VertexCustomAttributes:
			return true;
		case FutureDeviceSupport_MipMap:
			return true;
		case FutureDeviceSupport_GenerateMipMap:
			return true;
		case FutureDeviceSupport_TwoSidedStencil:
			return true;
		case FutureDeviceSupport_HardwareVideo:
			return true;
		case FutureDeviceSupport_Stereoscopic:
			return (m_settings.m_deviceMajorVersion >= 11 && m_settings.m_deviceMinorVersion >= 1);
		case FutureDeviceSupport_FullScreen:
			return true;
		case FutureDeviceSupport_ResolutionChange:
			return true;
		case FutureDeviceSupport_Threading:
			return !m_settings.m_singleThreaded;
	}
	return false;
}

u32							FutureDXGraphicsSystem::GetDeviceCapability(FutureDeviceCapabilityType feature)
{
	switch(feature)
	{
		case FutureDeviceCapability_MaxTexture1DDimension:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_REQ_TEXTURE1D_U_DIMENSION : D3D11_REQ_TEXTURE1D_U_DIMENSION;
		case FutureDeviceCapability_MaxTexture2DDimension:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_REQ_TEXTURE2D_U_OR_V_DIMENSION : D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;
		case FutureDeviceCapability_MaxTexture3DDimension:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_REQ_TEXTURE3D_U_V_OR_W_DIMENSION : D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION;
		case FutureDeviceCapability_MaxTextureArraySize:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_REQ_TEXTURE3D_U_V_OR_W_DIMENSION : D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION;
		case FutureDeviceCapability_MaxMultiSamples:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_MAX_MULTISAMPLE_SAMPLE_COUNT : D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
		case FutureDeviceCapability_MaxActiveTextures:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_COMMONSHADER_INPUT_RESOURCE_REGISTER_COUNT : D3D11_COMMONSHADER_INPUT_RESOURCE_REGISTER_COUNT;
		case FutureDeviceCapability_MaxTextureCubeDimension:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_REQ_TEXTURECUBE_DIMENSION : D3D11_REQ_TEXTURECUBE_DIMENSION;
		case FutureDeviceCapability_MaxRenderTargets:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT : D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
		case FutureDeviceCapability_MaxRenderTargetDimension:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_REQ_RENDER_TO_BUFFER_WINDOW_WIDTH : D3D11_REQ_RENDER_TO_BUFFER_WINDOW_WIDTH;
		case FutureDeviceCapability_MaxTextureBufferSize:
			return 4294967296;
		case FutureDeviceCapability_MaxTextureLODBias:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_MIP_LOD_BIAS_MAX : D3D11_MIP_LOD_BIAS_MAX;
		case FutureDeviceCapability_MaxIndices:
			return 4294967295;
		case FutureDeviceCapability_MaxVertices:
			return 4294967295;
		case FutureDeviceCapability_MaxComputeShaderStorageBlocks:
			return m_settings.m_deviceMajorVersion == 10 ? D3D11_CS_TGSM_REGISTER_COUNT : D3D11_CS_TGSM_REGISTER_COUNT;
		case FutureDeviceCapability_MaxComputeShaderUniformBlocks:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT : D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
		case FutureDeviceCapability_MaxComputeShaderWorkGroups:
			return m_settings.m_deviceMajorVersion == 10 ? D3D11_CS_4_X_THREAD_GROUP_MAX_THREADS_PER_GROUP : D3D11_CS_THREAD_GROUP_MAX_THREADS_PER_GROUP;
		case FutureDeviceCapability_MaxComputeShaderWorkGroupSize:
			return m_settings.m_deviceMajorVersion == 10 ? D3D11_CS_4_X_BUCKET00_MAX_NUM_THREADS_PER_GROUP : D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION;
		case FutureDeviceCapability_MaxPixelShaderInputComponents:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_PS_INPUT_REGISTER_COUNT : D3D11_PS_INPUT_REGISTER_COUNT;
		case FutureDeviceCapability_MaxPixelShaderUniformComponents:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT : D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
		case FutureDeviceCapability_MaxPixelShaderTextures:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_COMMONSHADER_SAMPLER_REGISTER_COUNT : D3D11_COMMONSHADER_SAMPLER_REGISTER_COUNT;
		case FutureDeviceCapability_MaxGeometryShaderInputComponents:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_GS_INPUT_REGISTER_COUNT : D3D11_GS_INPUT_REGISTER_COUNT;
		case FutureDeviceCapability_MaxGeometryShaderOutputComponents:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_GS_OUTPUT_ELEMENTS : D3D11_GS_OUTPUT_ELEMENTS;
		case FutureDeviceCapability_MaxGeometryShaderUniformComponents:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT : D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
		case FutureDeviceCapability_MaxPreTesslationShaderStorageBlocks:
			return m_settings.m_deviceMajorVersion == 10 ? 0 : D3D11_DS_INPUT_CONTROL_POINT_REGISTER_COUNT;
		case FutureDeviceCapability_MaxPostTesslationShaderStorageBlocks:
			return m_settings.m_deviceMajorVersion == 10 ? 0 : D3D11_HS_CONTROL_POINT_PHASE_INPUT_REGISTER_COUNT;
		case FutureDeviceCapability_MaxVertexShaderAttributes:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_VS_INPUT_REGISTER_COUNT : D3D11_VS_INPUT_REGISTER_COUNT;
		case FutureDeviceCapability_MaxVertexShaderTextures:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_COMMONSHADER_SAMPLER_REGISTER_COUNT : D3D11_COMMONSHADER_SAMPLER_REGISTER_COUNT;
		case FutureDeviceCapability_MaxVertexShaderUniformComponents:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT : D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
		case FutureDeviceCapability_MaxVertexShaderOutputComponents:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_VS_OUTPUT_REGISTER_COUNT : D3D11_VS_OUTPUT_REGISTER_COUNT;
		case FutureDeviceCapability_MaxViewPortWidth:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_VIEWPORT_BOUNDS_MAX : D3D11_VIEWPORT_BOUNDS_MAX;
		case FutureDeviceCapability_MaxViewPortHeight:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_VIEWPORT_BOUNDS_MAX : D3D11_VIEWPORT_BOUNDS_MAX;
		case FutureDeviceCapability_MaxViewPortDepth:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_MAX_DEPTH : D3D11_MAX_DEPTH;
		case FutureDeviceCapability_MaxViewPorts:
			return m_settings.m_deviceMajorVersion == 10 ? D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE : D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
		case FutureDeviceCapability_BufferMapAlignment:
			return m_settings.m_deviceMajorVersion == 10 ? D3D11_RAW_UAV_SRV_BYTE_ALIGNMENT : D3D11_RAW_UAV_SRV_BYTE_ALIGNMENT;
	}
	return 0;
}

IFutureWindow *				FutureDXGraphicsSystem::Window();

void						FutureDXGraphicsSystem::AddDeviceCallback(IFutureDeviceCallback * deviceCallback);
void						FutureDXGraphicsSystem::RemoveDeviceCallback(IFutureDeviceCallback * deviceCallback);

    
s32         FutureDXGraphicsSystem::CreateBlendState(const FutureBlendInfo info);
s32         FutureDXGraphicsSystem::CreateDepthStencilState(const FutureDepthStencilInfo info)
{
	D3D11_DEPTH_STENCIL_DESC stencilDesc;
	stencilDesc.DepthEnable = info.m_enableDepthMap;
	stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	stencilDesc.DepthFunc = (D3D11_COMPARISON_FUNC)info.m_comparisonFunction;

	stencilDesc.StencilEnable = info.m_enableStencil;
	stencilDesc.StencilReadMask = info.m_readMask;
	stencilDesc.StencilWriteMask = info.m_writeMask;

	stencilDesc.FrontFace.StencilFailOp = (D3D11_STENCIL_OP)info.m_frontStencil.m_onFail;
	stencilDesc.FrontFace.StencilDepthFailOp = (D3D11_STENCIL_OP)info.m_frontStencil.m_onFailDepth;
	stencilDesc.FrontFace.StencilPassOp = (D3D11_STENCIL_OP)info.m_frontStencil.m_onPassBoth;
	stencilDesc.FrontFace.StencilFunc = (D3D11_COMPARISON_FUNC)info.m_frontStencil.m_comparisonFunction;

	stencilDesc.BackFace.StencilFailOp = (D3D11_STENCIL_OP)info.m_backStencil.m_onFail;
	stencilDesc.BackFace.StencilDepthFailOp = (D3D11_STENCIL_OP)info.m_backStencil.m_onFailDepth;
	stencilDesc.BackFace.StencilPassOp = (D3D11_STENCIL_OP)info.m_backStencil.m_onPassBoth;
	stencilDesc.BackFace.StencilFunc = (D3D11_COMPARISON_FUNC)info.m_backStencil.m_comparisonFunction;

	ID3D11DepthStencilState * state;
	HRESULT result = m_device->CreateDepthStencilState(&stencilDesc, &state);
	if(FAILED(result))
	{
		return -1;
	}

	FutureDepthStencilInfo stencil;
	stencil.m_enableDepthMap = info.m_enableDepthMap;
	stencil.m_comparisonFunction = info.m_comparisonFunction;

	stencil.m_enableStencil = info.m_enableStencil;
	stencil.m_readMask = info.m_readMask;
	stencil.m_writeMask = info.m_writeMask;

	stencil.m_frontStencil.m_onFail = info.m_frontStencil.m_onFail;
	stencil.m_frontStencil.m_onFailDepth = info.m_frontStencil.m_onFailDepth;
	stencil.m_frontStencil.m_onPassBoth = info.m_frontStencil.m_onPassBoth;
	stencil.m_frontStencil.m_comparisonFunction = info.m_frontStencil.m_comparisonFunction;

	stencil.m_backStencil.m_onFail = info.m_backStencil.m_onFail;
	stencil.m_backStencil.m_onFailDepth = info.m_backStencil.m_onFailDepth;
	stencil.m_backStencil.m_onPassBoth = info.m_backStencil.m_onPassBoth;
	stencil.m_backStencil.m_comparisonFunction = info.m_backStencil.m_comparisonFunction;
	
	m_depthStencilStates.Add(state);
	m_depthStencilInfo.Add(stencil);

	return m_rasterStates.Size() - 1;
}

s32         FutureDXGraphicsSystem::CreateRasterizerState(const FutureRasterizerInfo info)
{

	//create rasterizer	
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.CullMode = (D3D11_CULL_MODE)info.m_cullMode;
	rasterDesc.FillMode = info.m_wireframe ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = info.m_counterClockwiseWrapping;
	rasterDesc.DepthBias = false;
	rasterDesc.DepthBiasClamp = 0;
	rasterDesc.SlopeScaledDepthBias = 0;
	rasterDesc.DepthClipEnable = info.m_depthClipping;
	rasterDesc.ScissorEnable = info.m_enableScissor;
	rasterDesc.MultisampleEnable = info.m_enableMultisampling;
	rasterDesc.AntialiasedLineEnable = true;

	ID3D11RasterizerState * rasterState;
	HRESULT result = m_device->CreateRasterizerState(&rasterDesc, &rasterState);
	if(FAILED(result) || !rasterState)
	{
		return -1;
	}

	FutureRasterizerInfo newInfo;
	newInfo.m_wireframe = info.m_wireframe;
	newInfo.m_counterClockwiseWrapping = info.m_counterClockwiseWrapping;
	newInfo.m_cullMode = info.m_cullMode;
	newInfo.m_depthClipping = info.m_depthClipping;
	newInfo.m_enableScissor = info.m_enableScissor;
	newInfo.m_enableMultisampling = info.m_enableMultisampling;

	m_rasterStates.Add(rasterState);
	m_rasterInfo.Add(newInfo);

	return m_rasterStates.Size() - 1;
}

s32         FutureDXGraphicsSystem::CreateTextureSamplerState(const FutureTextureSamplerInfo info);
    
bool        FutureDXGraphicsSystem::GetBlendStateInfo(FutureBlendInfo & info, s32 id);
bool        FutureDXGraphicsSystem::GetDepthStencilStateInfo(FutureDepthStencilInfo  & info, s32 id);
bool        FutureDXGraphicsSystem::GetRasterizerStateInfo(FutureRasterizerInfo & info, s32 id);
bool        FutureDXGraphicsSystem::GetTextureSamplerStateInfo(FutureTextureSamplerInfo & info, s32 id);
    
bool        FutureDXGraphicsSystem::CreateBuffer(const FutureHardwareBufferInfo & info, 
									const FutureInitialBufferData & data, 
									IFutureHardwareBuffer ** buffer);
bool        FutureDXGraphicsSystem::CreateShader(const FutureShaderInfo & info, 
									const FutureInitialShaderData & data,
									IFutureShader ** shader);
bool        FutureDXGraphicsSystem::CreateTexture(const FutureTextureInfo info, 
									const FutureInitialTextureData & data,
									IFutureTexture ** texture);
bool        FutureDXGraphicsSystem::CreateMips(IFutureTexture * texture);
    
bool        FutureDXGraphicsSystem::IsFeatureSupported(FutureDeviceSupport feature);
u32         FutureDXGraphicsSystem::GetCapability(FutureDeviceCapabilityType type);
    
bool        FutureDXGraphicsSystem::GetViewport(FutureViewport & viewport)
{
	viewport.m_left = m_viewport.m_left;
	viewport.m_right = m_viewport.m_right;
	viewport.m_top = m_viewport.m_top;
	viewport.m_bottom = m_viewport.m_bottom;
	viewport.m_near = m_viewport.m_near;
	viewport.m_far = m_viewport.m_far;
	return true;
}
bool        FutureDXGraphicsSystem::SetViewport(const FutureViewport & viewport)
{
	m_viewport.m_left = viewport.m_left;
	m_viewport.m_right = viewport.m_right;
	m_viewport.m_top = viewport.m_top;
	m_viewport.m_bottom = viewport.m_bottom;
	m_viewport.m_near = viewport.m_near;
	m_viewport.m_far = viewport.m_far;

	D3D11_VIEWPORT vp;
	vp.Width = m_viewport.m_right - m_viewport.m_left;
	vp.Height = m_viewport.m_top - m_viewport.m_bottom;
	vp.MinDepth = m_viewport.m_near;
	vp.MaxDepth = m_viewport.m_far;
	vp.TopLeftX = m_viewport.m_left;
	vp.TopLeftY = m_viewport.m_top;
	m_deviceContext->RSSetViewports(1, &vp);
	return true;
}
    
    
bool        FutureDXGraphicsSystem::ClearDepthStencil(IFutureTexture * depthStencil, f32 depthClear = 0.f, u8 stencilClear = 0);
bool        FutureDXGraphicsSystem::ClearDepthBuffer(IFutureTexture * depthStencil, f32 clearValue = 0.f);
bool        FutureDXGraphicsSystem::ClearStencil(IFutureTexture * depthStencil, u8 clearValue = 0);
bool        FutureDXGraphicsSystem::ClearRenderTarget(IFutureTexture * renderTarget);
bool        FutureDXGraphicsSystem::ClearState();
    
bool        FutureDXGraphicsSystem::GetRenderTarget(IFutureTexture ** renderTarget);
bool        FutureDXGraphicsSystem::SetRenderTarget(IFutureTexture * renderTarget);
    
bool        FutureDXGraphicsSystem::GetDepthStencil(IFutureTexture ** depthStencil);
bool        FutureDXGraphicsSystem::SetDepthStencil(IFutureTexture * depthStencil);
    
bool        FutureDXGraphicsSystem::GetShader(FutureShaderType type, IFutureShader ** shader);
    
bool        FutureDXGraphicsSystem::SetBlendState(s32 state);
bool        FutureDXGraphicsSystem::SetDepthStencilState(s32 state);
bool        FutureDXGraphicsSystem::SetRasterizerState(s32 state)
{
	if(state == m_currentRasterState)
	{
		return true;
	}
	ID3D11RasterizerState * rasterState = m_rasterStates[state];
	if(!rasterState)
	{
		return false;
	}
	m_deviceContext->RSSetState(rasterState);
	m_currentRasterState = state;
	return true;
}
    
u32         FutureDXGraphicsSystem::GetBlendState();
u32         FutureDXGraphicsSystem::GetDepthStencilState();
u32         FutureDXGraphicsSystem::GetRasterizerState();
    
bool        FutureDXGraphicsSystem::GetVertexBuffer(IFutureHardwareBuffer ** buffer);
bool        FutureDXGraphicsSystem::GetIndexBuffer(IFutureHardwareBuffer ** buffer);

bool        FutureDXGraphicsSystem::SetVertexBuffer(IFutureHardwareBuffer * buffer);
bool        FutureDXGraphicsSystem::SetIndexBuffer(IFutureHardwareBuffer * buffer);
bool		FutureDXGraphicsSystem::SetPrimitiveType(FuturePrimitiveType primType);

bool        FutureDXGraphicsSystem::BeginRender();
bool        FutureDXGraphicsSystem::Render();
bool        FutureDXGraphicsSystem::EndRender();


void		FutureDXGraphicsSystem::CallDeviceCreated();
void		FutureDXGraphicsSystem::CallDeviceLost();
void		FutureDXGraphicsSystem::CallDevicePreReset();
void		FutureDXGraphicsSystem::CallDeviceReset();
void		FutureDXGraphicsSystem::CallDevicePreChange();
void		FutureDXGraphicsSystem::CallDeviceChanged();
