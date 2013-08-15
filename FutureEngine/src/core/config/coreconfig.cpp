/*
 *	Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
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

#include <future/core/type/type.h>
#include <future/core/config/coreconfig.h>
#include <future/core/util/stream.h>

bool FutureCoreConfig::m_profileEnabled = FUTURE_DEBUG || FUTURE_PROFILE;
bool FutureCoreConfig::m_trackMemory = FutureCoreConfig::m_profileEnabled;
bool FutureCoreConfig::m_profileMemory = FutureCoreConfig::m_profileEnabled;
bool FutureCoreConfig::m_forceMemoryLimit = false;
u32 FutureCoreConfig::m_memoryLimit = 0;
u32 FutureCoreConfig::m_heapSize = 1024 * 1024 * 10;
u32 FutureCoreConfig::m_numPools = 5;
u32 * FutureCoreConfig::m_poolBlockSizes = {16, 32, 64, 128, 256};
u32 * FutureCoreConfig::m_poolNumBlocks = {4096, 4096, 4096, 4096, 4096};
bool FutureCoreConfig::m_multithreaded = FUTURE_ENABLE_MULTITHREADED == 1;
bool FutureCoreConfig::m_profileThreadPool = FutureCoreConfig::m_profileEnabled;
u8 FutureCoreConfig::m_defaultThreads = 6;
bool FutureCoreConfig::m_asyncSystems = false;
bool FutureCoreConfig::m_autoPopulate = true;
bool FutureCoreConfig::m_eventDispatching = true;
bool FutureCoreConfig::m_eventPolling = false;
bool FutureCoreConfig::m_eventAsync = true;
Language FutureCoreConfig::m_language = Language_NULL;
bool FutureCoreConfig::m_storeResourceNames = FUTURE_DEBUG || FUTURE_PROFILE;
bool FutureCoreConfig::m_searchResourceNames = false;


bool FutureCoreConfig::LoadConfig(IFutureIStream * stream)
{
	if(!stream->ReadCheckSum())
	{
		return false;
	}
	m_profileEnabled = stream->ReadBool();
	m_trackMemory = stream->ReadBool();
	m_profileMemory = stream->ReadBool();
	m_forceMemoryLimit = stream->ReadBool();
	m_memoryLimit = stream->ReadU32();
	m_heapSize = stream->ReadU32();
	m_poolBlockSizes = stream->ReadU32Array(&m_numPools);
	m_poolNumBlocks = stream->ReadU32Array(&m_numPools);
	m_profileThreadPool = stream->ReadBool();
	m_defaultThreads = stream->ReadU8();
	m_asyncSystems = stream->ReadBool();
	m_autoPopulate = stream->ReadBool();
	m_eventDispatching = stream->ReadBool();
	m_eventPolling = stream->ReadBool();
	m_eventAsync = stream->ReadBool();
	m_language = (Language)stream->ReadU32();
	m_storeResourceNames = stream->ReadBool();
	m_searchResourceNames = stream->ReadBool();
	return stream->ReadCheckSum();
}

bool FutureCoreConfig::DumpConfig(IFutureOStream * stream)
{
	if(!stream->WriteCheckSum())
	{
		return false;
	}
	stream->Write(m_profileEnabled);
	stream->Write(m_trackMemory);
	stream->Write(m_profileMemory);
	stream->Write(m_forceMemoryLimit);
	stream->Write(m_memoryLimit);
	stream->Write(m_heapSize);
	stream->Write(m_poolBlockSizes);
	stream->Write(m_poolNumBlocks);
	stream->Write(m_profileThreadPool);
	stream->Write(m_defaultThreads);
	stream->Write(m_asyncSystems);
	stream->Write(m_autoPopulate);
	stream->Write(m_eventDispatching);
	stream->Write(m_eventPolling);
	stream->Write(m_eventAsync);
	stream->Write((u32)m_language);
	stream->Write(m_storeResourceNames);
	stream->Write(m_searchResourceNames);
	return stream->WriteCheckSum();
}


