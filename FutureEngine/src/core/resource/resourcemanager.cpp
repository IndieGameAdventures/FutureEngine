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
*	An event that is sent out to all object listening for it
*/

#include <future/core/resource/resourcemanager.h>
#include <future/core/thread/pool/threadpool.h>
#include <future/core/thread/pool/job.h>


struct ResourceFileInfo
{
	u32		m_size;
	u32		m_buildVersion;
	u32		m_numLanguages;
	u32	*	m_languageOffsets;
};

FutureResourceManager * ms_manager = NULL;

void LoadSystemResources(void * data)
{
	FutureResourceManager::GetInstance()->LoadSystemResourcesSync((LoadFinishedCallback)data);
}

struct ResourceLoadOperation
{
	FutureResourceManager::LoadFinishedCallback		m_callback;
	ResourceID										m_resource;
	Language										m_language;
};

void LoadResource(void * data)
{
	ResourceLoadOperation * op = dynamic_cast<ResourceLoadOperation*>(data);
	if(!op)
	{
		FUTURE_ASSET_MSG(false, "Invalid data sent to resource loader");
	}
	FutureResourceManager::GetInstance()->LoadResourceSync(op->m_resource, op->m_callback, op->m_language);
	delete op;
}


void FutureResourceManager::CreateInstance()
{
	FUTURE_ASSET(!ms_manager);
	FUTURE_LOG_V("Creating Resource Manager");
	ms_manager = new FutureResourceManager();
}
void FutureResourceManager::DestroyInstance()
{
	FUTURE_ASSET(ms_manager);
	FUTURE_LOG_V("Destroying Resource Manager");
	delete ms_manager;
	ms_manager = NULL;
}
FutureResourceManager * FutureResourceManager::GetInstance()
{
	return ms_manager;
}

FutureResourceManager::FutureResourceManager()
	: m_languages(1),
	  m_resources(),
	  m_groups(),
	  m_strings(),
	  m_values()
{}

FutureResourceManager::~FutureResourceManager()
{
	UnloadAll();
	CleanUpResources();

	for(u32 i = 0; i < m_resources.Size(); ++i)
	{
		if(m_resources[i].m_name)
		{
			FUTURE_FREE(m_resources[i].m_name);
			m_resources[i].m_name = NULL;
		}
	}
	for(u32 i = 0; i < m_groups.Size(); ++i)
	{
		if(m_groups[i].m_name)
		{
			FUTURE_FREE(m_groups[i].m_name);
			m_groups[i].m_name = NULL;
		}
	}
	for(u32 i = 0; i < m_strings.Size(); ++i)
	{
		if(m_strings[i].m_tag)
		{
			FUTURE_FREE(m_strings[i].m_tag);
			m_strings[i].m_tag = NULL;
		}
		if(m_strings[i].m_strings)
		{
			for(u32 j = 0; j < m_languages; ++j)
			{
				if(m_strings[i].m_strings[j])
				{
					FUTURE_FREE(m_strings[i].m_strings[j]);
					m_strings[i].m_strings[j] = NULL;
				}
			}
			FUTURE_FREE(m_strings[i].m_strings);
			m_strings[i].m_strings = NULL;
		}
	}
	for(u32 i = 0; i < m_values.Size(); ++i)
	{
		if(m_values[i].m_name)
		{
			FUTURE_FREE(m_values[i].m_name);
			m_values[i].m_name = NULL;
		}
		if(m_values[i].m_type == ValueType_Array && m_values[i].m_array)
		{
			FUTURE_FREE(m_values[i].m_array);
			m_values[i].m_array = NULL;
		}
	}
	m_resources.Clear();
	m_groups.Clear();
	m_strings.Clear();
	m_values.Clear();
}

bool FutureResourceManager::LoadSystemResources(LoadFinishedCallback callback)
{
	FUTURE_LOG_V("Sending Load System Resources Request.");
	FUTURE_ASSERT(!HasSystemResources());
	FutureThreadJob * job = new FutureThreadJob(LoadSystemResources, callback);
	FutureThreadPool::GetInstance()->AddJob(job);
}

bool FutureResourceManager::LoadSystemResourcesSync(LoadFinishedCallback callback)
{	
	FUTURE_ASSERT(!HasSystemResources());

	FUTURE_LOG_V("Loading System Resources");

	Lock();

	bool result = true;
	FutureFileInputStream * stream = new FutureFileInputStream();
	if(!stream->Open("assets/_0.dat"));
	{
		FUTURE_ASSET_MSG(false, "Failed to open system resource file");
		result = false;
		goto Finished;
	}
	ResourceFileInfo fileInfo;
	filesInfo.m_size = stream->ReadU32();
	filesInfo.m_buildVersion = stream->ReadU32();

	FUTURE_ASSET_MSG(filesInfo.m_buildVersion != FUTURE_VERSION_CODE, "System resource file and core library have different version codes.");

	if(!FutureCoreConfig::LoadConfig(stream))
	{
		FUTURE_ASSET_MSG(false, "Failed to read config file");
		result = false;
		goto Finished;
	}

	FutureMemory::PostConfigInit();

	if(!stream->ReadCheckSum())
	{
		FUTURE_ASSET_MSG(false, "System resource file is corrupt");
		result = false;
		goto Finished;
	}

	m_languages = stream->ReadU32();

	u32 numResources = stream->ReadU32();
	m_resources.SetSize(numResources);
	for(u32 i = 0; i < numResources; ++i)
	{
		m_resources[i].m_name = stream->ReadString();
		if(!FutureCoreConfig::StoreResourceNames())
		{
			FUTURE_FREE(m_resources[i].m_name);
			m_resources[i].m_name = NULL;
		}
		m_resources[i].m_resource = NULL;
	}
	m_resources.Shrink();

	if(!stream->ReadCheckSum())
	{
		FUTURE_ASSET_MSG(false, "System resource file is corrupt");
		result = false;
		goto Finished;
	}

	u32 numGroups = stream->ReadU32();
	m_groups.SetSize(numGroups);
	for(u32 i = 0; i < numGroups; ++i)
	{
		m_groups[i].m_name = stream->ReadString();
		if(!FutureCoreConfig::StoreResourceNames())
		{
			FUTURE_FREE(m_groups[i].m_name);
			m_groups[i].m_name = NULL;
		}
		m_groups[i].m_loadAttempted = false;
		m_groups[i].m_loadCounter = 0;
		u32 numRes;
		u32 * res = stream->ReadU32Array(&numRes);
		m_groups[i].m_resources.AddMultiple(res, numRes);
	}
	m_groups.Shrink();

	if(!stream->ReadCheckSum())
	{
		FUTURE_ASSET_MSG(false, "System resource file is corrupt");
		result = false;
		goto Finished;
	}

	u32 numStrings = stream->ReadU32();
	m_strings.SetSize(numStrings);
	for(u32 i = 0; i < numGroups; ++i)
	{
		m_strings[i].m_tag = stream->ReadString();
		if(!FutureCoreConfig::StoreResourceNames())
		{
			FUTURE_FREE(m_strings[i].m_tag);
			m_strings[i].m_tag = NULL;
		}
		m_strings[i].m_strings = (char**)FUTURE_ALLOC(sizeof(char*) * m_languages, "Localized String Array");
		for(u32 j = 0; j < m_languages; ++j)
		{
			m_strings[i].m_strings[j] = stream->ReadString();
		}
	}
	m_strings.Shrink();

	if(!stream->ReadCheckSum())
	{
		FUTURE_ASSET_MSG(false, "System resource file is corrupt");
		result = false;
		goto Finished;
	}

	u32 numValues = stream->ReadU32();
	m_values.SetSize(numValues);
	for(u32 i = 0; i < numValues; ++i)
	{
		m_values[i].m_name = stream->ReadString();
		if(!FutureCoreConfig::StoreResourceNames())
		{
			FUTURE_FREE(m_values[i].m_name);
			m_values[i].m_name = NULL;
		}
		m_values[i].m_type = (ValueType)stream->ReadU32();
		switch(m_values[i].m_type)
		{
			case ValueType_Bool:
				m_values[i].m_bool = stream->ReadBool();
				break;
			case ValueType_U8:
				m_values[i].m_u8 = stream->ReadU8();
				break;
			case ValueType_U16:
				m_values[i].m_u16 = stream->ReadU16();
				break;
			case ValueType_U32:
				m_values[i].m_u32 = stream->ReadU32();
				break;
			case ValueType_S8:
				m_values[i].m_s8 = stream->ReadS8();
				break;
			case ValueType_S16:
				m_values[i].m_s16 = stream->ReadS16();
				break;
			case ValueType_S32:
				m_values[i].m_s32 = stream->ReadS32();
				break;
			case ValueType_F32:
				m_values[i].m_f32 = stream->ReadF32();
				break;
			case ValueType_Array:
				m_values[i].m_array = (void*)stream->ReadU8Array(&m_values[i].m_size);
				break;
			default:
				FUTURE_ASSET_MSG(false, "Found invalid value type: %u", m_values[i].m_type);
				result = false;
				goto Finished;
		}
	}
	m_values.Shrink();

	if(!stream->ReadCheckSum())
	{
		FUTURE_ASSET_MSG(false, "System resource file is corrupt");
		result = false;
		goto Finished;
	}

Finished:
	Unlock();

	if(stream)
	{
		if(stream->IsOpen())
		{	
			stream->Close();
		}
		delete stream;
		stream = NULL;
	}

	if(result)
	{
		FUTURE_LOG_V("Successfully loaded system resources");
	}
	else
	{
		FUTURE_ASSERT_CRIT_MSG(false, "Failed to Load System Resources!");
	}

	return result;
}

bool FutureResourceManager::HasSystemResources()
{
	bool result = false;
	Lock();
	result = m_resources.Size() > 0 && m_groups.Size() > 0;
	Unlock();
	return result;
}

bool FutureResourceManager::PreloadGroupInfo(ResourceGroupID group)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	FUTURE_ASSERT(group < m_groups.Size());
	if(IsGroupLoaded(group))
	{
		return true;
	}

	Lock();
	for(u32 i = 0; i < m_groups[group].m_resources.Size(); ++i)
	{
		if(m_groups[group].m_resources[i])
		{
			m_groups[group].m_resources[i]->AddGroupRef();
		}
	}
	Unlock();
	return true;
}

bool FutureResourceManager::LoadGroup(ResourceGroupID group, LoadFinishedCallback callback)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	FUTURE_ASSERT(group < m_groups.Size());

	if(IsGroupLoaded(group))
	{
		if(callback)
		{
			callback(true, group);
		}
		return true;
	}
	Lock();
	if(m_groups[group].m_loadAttempted)
	{
		if(callback)
		{
			m_groups[group].m_loadFinishedCallbacks.Add(callback);
		}
		Unlock();
		return true;
	}
	m_groups[group].m_loadAttempted = true;
	Unlock();

	FUTURE_LOG_V("Sending async group load request for group %u.", group);

	for(u32 i = 0; i < m_groups[group].m_resources.Size(); ++i)
	{
 		if(IsResourceLoaded(m_groups[group].m_resources[i]))
 		{
 			continue;
 		}
 		ResourceLoadOperation * op = new ResourceLoadOperation();
 		op->m_callback = NULL;
 		op->m_resource = m_groups[group].m_resources[i];
 		op->m_language = FutureCoreConfig::DefaultResourceLanguage();

		FutureThreadJob * job = new FutureThreadJob(LoadResource, op);
		FutureThreadPool::GetInstance()->AddJob(job);
	}
	return true;
}

bool FutureResourceManager::LoadGroupSync(ResourceGroupID group, LoadFinishedCallback callback)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	FUTURE_ASSERT(group < m_groups.Size());

	if(IsGroupLoaded(group))
	{
		if(callback)
		{
			callback(true, group);
		}
		return true;
	}
	Lock();
	if(m_groups[group].m_loadAttempted)
	{
		if(callback)
		{
			m_groups[group].m_loadFinishedCallbacks.Add(callback);
		}
		Unlock();
		return true;
	}
	m_groups[group].m_loadAttempted = true;
	Unlock();

	FUTURE_LOG_V("Syncronously loading resources for group %u.", group);

	for(u32 i = 0; i < m_groups[group].m_resources.Size(); ++i)
	{
 		if(IsResourceLoaded(m_groups[group].m_resources[i]))
 		{
 			continue;
 		}
 		LoadResourceSync(m_groups[group].m_resources[i], NULL);
	}

	bool result = IsGroupLoaded(group);
	if(callback)
	{
		callback(result, group);
	}
	return result;

}
bool FutureResourceManager::IsGroupLoaded(ResourceGroupID group)
{
	bool result = false;
	Lock();
	result = m_groups[group].m_loadCounter >= m_groups[group].m_resources.Size();
	Unlock();
	return result;
}

bool FutureResourceManager::UnloadGroup(ResourceGroupID group, bool force)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	FUTURE_ASSERT(group < m_groups.Size());

	FUTURE_LOG_V("Unloading group %u.", group);
	//Lock();
	for(u32 i = 0; i < m_groups[group].m_resources.Size(); ++i)
	{
		FutureResource * res = m_resources[m_groups[group].m_resources[i]].m_resource;
		if(res)
		{
			res->GroupRelease();
			if(force || res->ShouldUnload())
			{
				UnloadResource(res->Id());
			}
		}
	}
	//Unlock();
	return true;
}


bool FutureResourceManager::FlipGroup(ResourceGroupID groupToLoad, ResourceGroupID groupToUnload, LoadFinishedCallback callback)
{
	FUTURE_LOG_V("Flipping Groups %u to group %u.", groupToUnload, groupToLoad);
	PreloadGroupInfo(groupToLoad);
	UnloadGroup(groupToUnload);
	CleanUpResources();
	return LoadGroup(groupToLoad, callback);
}
bool FutureResourceManager::FlipGroupSync(ResourceGroupID groupToLoad, ResourceGroupID groupToUnload, LoadFinishedCallback callback)
{
	FUTURE_LOG_V("Flipping Groups %u to group %u.", groupToUnload, groupToLoad);
	PreloadGroupInfo(groupToLoad);
	UnloadGroup(groupToUnload);
	CleanUpResources();
	return LoadGroupSync(groupToLoad, callback);
}

ResourceGroupID FutureResourceManager::GetGroupID(const char * name)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be calleD until system resources are loaded");
	}
	if(!FutureCoreConfig::SearchResourceNames())
	{
		FUTURE_LOG_E("Attempting to search for a group by name when this funcionality has been disabled by the configuration");
		return ResourceGroupID_NULL;
	}
	FUTURE_LOG_D("Attempting to locate resource group by name. This is expensive");
	for(u32 i = 0; i < m_groups.Size(); ++i)
	{
		if(strcmp(m_groups[i].m_name, name) == 0)
		{
			return (ResourceGroupID)i;
		}
	}
	return ResourceGroupID_NULL;
}
const char * FutureResourceManager::GetGroupName(ResourceGroupID group)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	if(!FutureCoreConfig::StoreResourceNames())
	{
		FUTURE_LOG_E("Attempting to get a resource group name when this funcionality has been disabled by the configuration");
		return NULL;
	}
	return m_groups[group].m_name;
}
u32 FutureResourceManager::GetNumGroupResources(ResourceGroupID group)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	return m_groups[group].m_resources.Size();
}


bool FutureResourceManager::LoadResource(ResourceID resource, LoadFinishedCallback callback, Language language)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, L"This function cannot be called until system resources are loaded");
	}
	FUTURE_ASSERT(resource < m_resources.Size());

	EnsureResource(resource);
	FutureResource * res = m_resources[resource].m_resource;
	res->Lock();
	if(res->IsLoaded())
	{
		if(callback)
		{
			callback(true, resource);
		}
		res->Unlock();
		return true;
	}
	if(res->IsLoading())
	{
		if(callback)
		{
			res->m_loadFinishedCallbacks.Add(callback);
		}
		res->Unlock();
		return true;
	}
	res->Unlock();

	FUTURE_LOG_V("Sending load request for resource %u.", resource);

	ResourceLoadOperation * op = new ResourceLoadOperation();
	op->m_callback = callback;
	op->m_resource = resource;

	FutureThreadJob * job = new FutureThreadJob(LoadResource, op);
	FutureThreadPool::GetInstance()->AddJob(job);
}
bool FutureResourceManager::LoadResourceSync(ResourceID resource, LoadFinishedCallback callback, Language language)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	FUTURE_ASSERT(resource < m_resources.Size());

	EnsureResource(resource);
	FutureResource * res = m_resources[resource].m_resource;
	res->Lock();
	if(res->IsLoaded())
	{
		if(callback)
		{
			callback(true, resource);
		}
		res->Unlock();
		return true;
	}
	if(res->IsLoading())
	{
		if(callback)
		{
			res->m_loadFinishedCallbacks.Add(callback);
		}
		res->Unlock();
		return true;
	}

	res->m_loading = true;
	res->Unlock();

	FUTURE_LOG_V("Loading resource %u.", resource);

	bool result = true;
	char file[32];
	sprintf(file, 32, "assets/_%u.dat", resource);
	FutureFileInputStream * stream = new FutureFileInputStream();
	if(!stream->Open(file));
	{
		FUTURE_LOG_E("Failed to open resource file '%s' for resource %u", file, resource);
		result = false;
		goto Finished;
	}

	ResourceFileInfo fileInfo;
	filesInfo.m_size = stream->ReadU32();
	filesInfo.m_buildVersion = stream->ReadU32();

	FUTURE_ASSET_MSG(filesInfo.m_buildVersion != FUTURE_VERSION_CODE, "Resource file and core library have different version codes.");

	filesInfo.m_languageOffsets = stream->ReadU32Array(&filesInfo.m_numLanguages);

	if(language == Language_Null)
	{
		language = FutureCoreConfig::DefaultResourceLanguage();
	}

	stream->Skip(filesInfo.m_languageOffsets[language]);

	FUTURE_FREE(filesInfo.m_languageOffsets);

	if(!stream->ReadCheckSum())
	{
		FUTURE_LOG_E("Resource file is not valid for resource %u", resource);
		result = false;
		goto Finished;
	}

	if(!res->Load(resource, stream));
	{
		FUTURE_LOG_E("Failed to load resource %u", resource);
		result = false;
		goto Finished;
	}


	Lock();
	for(u32 g = 0; g < res->m_numGroups; ++g)
	{
		++m_groups[res->m_groups[g]].m_loadCounter;
		if(IsGroupLoaded(res->m_groups[g]) && m_groups[res->m_groups[g]].m_loadAttempted)
		{
			for(u32 i = 0; i < m_groups[res->m_groups[g]].m_loadFinishedCallbacks.Size(); ++i)
			{
				if(m_groups[res->m_groups[g]].m_loadFinishedCallbacks[i])
				{
					m_groups[res->m_groups[g]].m_loadFinishedCallbacks[i](result, res->m_groups[g]);
				}
			}
			m_groups[res->m_groups[g]].m_loadFinishedCallbacks.Clear();
		}
	}
 	Unlock();
Finished:

	res->Lock();
	res->m_valid = result;
	res->m_loaded = result;
	res->m_loading = false;
	res->Unlock();

	if(stream)
	{
		if(stream->IsOpen())
		{	
			stream->Close();
		}
		delete stream;
		stream = NULL;
	}

	if(result)
	{
		FUTURE_LOG_V("Successfully loaded resource %u", resource);
	}
	else
	{
		FUTURE_LOG_E("Successfully loaded resource %u", resource);
	}

	if(callback)
	{
		callback(result, resource);
	}
	res->Lock();
	for(u32 i = 0; i < res.m_loadFinishedCallbacks.Size(); ++i)
	{
		if(res.m_loadFinishedCallbacks[i])
		{
			res.m_loadFinishedCallbacks[i](result, resource);
		}
	}
	m_resources[resource].m_loadFinishedCallbacks.Clear();
	res->Unlock();
	return result;
}

ResourceID FutureResourceManager::LoadCustomResource(const char * file, FutureResource * res)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	FUTURE_ASSERT_MSG(res && file, "Loading a custom resource requires a valid file and resource object");

	Lock();
	if(res->ID() < m_resources.Size() && res->ID() >= 0 && m_resources[res->ID()].m_resource == res)
	{
		Unlock();
		return res->ID();
	}
	ResourceID res = m_resources.Size();
	ResourceInfo info;
	info.m_name = NULL;
    info.m_resource = res;
    m_resources.Add(info);
    Unlock();

	res->Lock();
	if(res->IsLoaded() || res->IsLoading())
	{
		res->Unlock();
		return true;
	}

	res->m_loading = true;
	res->Unlock();

	FUTURE_LOG_V("Loading custom resource %u.", resource);

	bool result = true;
	FutureFileInputStream * stream = new FutureFileInputStream();
	if(!stream->Open(file));
	{
		FUTURE_LOG_E("Failed to open custom resource file '%s'", file);
		result = false;
		goto Finished;
	}

	if(!res->Load(resource, stream));
	{
		FUTURE_LOG_E("Failed to load custom resource");
		result = false;
		goto Finished;
	}

Finished:

	res->Lock();
	res->m_valid = result;
	res->m_loaded = result;
	res->m_loading = false;
	res->Unlock();

	if(stream)
	{
		if(stream->IsOpen())
		{	
			stream->Close();
		}
		delete stream;
		stream = NULL;
	}

	if(result)
	{
		FUTURE_LOG_V("Successfully loaded custom resource");
		return resource;
	}
	else
	{
		FUTURE_LOG_E("Successfully loaded custom resource");
		return ResourceID_NULL;
	}
}

bool FutureResourceManager::IsResourceLoaded(ResourceID resource)
{
	bool result;
	Lock();
	result = m_resources[resource].m_resource && m_resources[resource].m_resource->IsLoaded();
	Unlock();
	return result;
}

bool FutureResourceManager::UnloadResource(ResourceID resource)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	FUTURE_ASSERT(resource < m_resources.Size());

	Lock();
	FutureResource * res = m_resources[resource].m_resource;
	Unlock();
	if(!res)
	{
		return true;
	}
	res->Lock();
	if(!res->IsLoaded())
	{
		res->Unlock();
		return true;
	}
	if(res->IsLoading())
	{
		FUTURE_LOG_W("Attempting to unload resource %u while it is still loading.", resource);
		res->Unlock();
		return false;
	}

	FUTURE_LOG_V("Unloading resource %u.", resource);
 	res->Unload();

 	Lock():
	for(u32 g = 0; g < res->m_numGroups; ++g)
	{
		--m_groups[res->m_groups[g]].m_loadCounter;
	}
	Unlock();

	res->m_valid = false;
	res->m_loaded = false;
	res->m_loading = false;
 	res->Unlock();
}

ResourceID FutureResourceManager::GetResourceID(const char * name)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	if(!FutureCoreConfig::SearchResourceNames())
	{
		FUTURE_LOG_E("Attempting to search for a resource by name when this functionality has been disabled by the configuration");
		return ResourceID_NULL;
	}
	FUTURE_LOG_D("Attempting to locate resource by name. This is expensive");
	for(u32 i = 0; i < m_resources.Size(); ++i)
	{
		if(strcmp(m_resources[i].m_name, name) == 0)
		{
			return (ResourceID)i;
		}
	}
	return ResourceID_NULL;
}
const char * FutureResourceManager::GetResourceName(ResourceID resource)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	if(!FutureCoreConfig::StoreResourceNames())
	{
		FUTURE_LOG_E("Attempting to get a resource name when this functionality has been disabled by the configuration");
		return NULL;
	}
	return m_resources[resource].m_name;
}

FutureResource * FutureResourceManager::GetResource(ResourceID resource, bool loadIfNeeded, bool loadAsync)
{
	Lock();
	FutureResource * res = m_resources[resource].m_resource;
	Unlock();
	if((!res || (!res->IsLoaded() && !res->IsLoading())) && loadIfNeeded)
	{
		if(loadAsync)
		{
			LoadResource(resource);
		}
		else
		{
			LoadResourceSync(resource);
		}
		Lock();
		res = m_resources[resource].m_resource;
		Unlock();
	}
	if(res)
	{
		res->AddRef();
	}
	return res;
}

StringID FutureResourceManager::GetStringIDByTag(const char * tag)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	if(!FutureCoreConfig::SearchResourceNames())
	{
		FUTURE_LOG_E("Attempting to search for a string by tag when this functionality has been disabled by the configuration");
		return StringID_NULL;
	}
	FUTURE_LOG_D("Attempting to locate string by tag. This is very expensive");
	for(u32 i = 0; i < m_string.Size(); ++i)
	{
		if(strcmp(m_string[i].m_tag, tag) == 0)
		{
			return (StringID)i;
		}
	}
	return StringID_NULL;
}
const char * FutureResourceManager::GetStringTag(StringID id)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	if(!FutureCoreConfig::StoreResourceNames())
	{
		FUTURE_LOG_E("Attempting to get a string tag when this functionality has been disabled by the configuration");
		return NULL;
	}
	return m_strings[id].m_tag;
}
const char * FutureResourceManager::GetString(StringID id, Language language)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources are loaded");
	}
	if(language == Language_Null)
	{
		language = FutureCoreConfig::DefaultResourceLanguage();
	}
	if(id >= m_strings.Size() || language >= m_languages)
	{
		FUTURE_LOG_E("Invalid string id and language combination. ID: %u, Language: %u", id, language);
		return NULL;
	}
	return m_strings[id].m_strings[language];
}

ValueID FutureResourceManager::GetValueIDByName(const char * name);
const char * FutureResourceManager::GetValueName(ValueID id);
ValueType FutureResourceManager::GetValueType(ValueID id);

bool FutureResourceManager::GetBool(ValueID id)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return false;
	}
	return m_values[id].m_bool;
}
u8 FutureResourceManager::GetU8(ValueID id)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	return m_values[id].m_u8;
}
u16 FutureResourceManager::GetU16(ValueID id)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	return m_values[id].m_u16;
}
u32 FutureResourceManager::GetU32(ValueID id)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	return m_values[id].m_u32;
}
s8 FutureResourceManager::GetS8(ValueID id)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	return m_values[id].m_s8;
}
s16 FutureResourceManager::GetS16(ValueID id)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	return m_values[id].m_s15;
}
s32 FutureResourceManager::GetS32(ValueID id)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	return m_values[id].m_s32;
}
f32 FutureResourceManager::GetFloat(ValueID id)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	return m_values[id].m_f32;
}
const void * FutureResourceManager::GetValue(ValueID id, u32 * size)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	if(size)
	{
		*size = m_values[id].m_size;
	}
	return m_values[id].m_array;
}
const bool * FutureResourceManager::GetBoolArray(ValueID id, u32 * elements)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	if(elements)
	{
		*elements = m_values[id].m_size;
	}
	return (bool*)m_values[id].m_array;
}
const u8 * FutureResourceManager::GetU8Array(ValueID id, u32 * elements)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	if(elements)
	{
		*elements = m_values[id].m_size;
	}
	return (u8*)m_values[id].m_array;
}
const u16 * FutureResourceManager::GetU16Array(ValueID id, u32 * elements)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	if(elements)
	{
		*elements = m_values[id].m_size >> 1;
	}
	return (u16*)m_values[id].m_array;
}
const u32 * FutureResourceManager::GetU32Array(ValueID id, u32 * elements)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id, u32 * elements)
		return 0;
	}
	if(elements)
	{
		*elements = m_values[id].m_size >> 2;
	}
	return (u32*)m_values[id].m_array;
}
const s8 * FutureResourceManager::GetS8Array(ValueID id, u32 * elements)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	if(elements)
	{
		*elements = m_values[id].m_size;
	}
	return (s8*)m_values[id].m_array;
}
const s16 * FutureResourceManager::GetS16Array(ValueID id, u32 * elements)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	if(elements)
	{
		*elements = m_values[id].m_size >> 1;
	}
	return (s16*)m_values[id].m_array;
}
const s32 * FutureResourceManager::GetS32Array(ValueID id, u32 * elements)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	if(elements)
	{
		*elements = m_values[id].m_size >> 2;
	}
	return (s32*)m_values[id].m_array;
}
const f32 * FutureResourceManager::GetFloatArray(ValueID id, u32 * elements)
{
	if(!HasSystemResources())
	{
		FUTURE_ASSERT_MSG(false, "This function cannot be called until system resources have finished loading");
	}
	if(id >= m_values.Size())
	{
		FUTURE_LOG_E("Recieved invalid ValueID: %u", id)
		return 0;
	}
	if(elements)
	{
		*elements = m_values[id].m_size >> 2;
	}
	return (f32*)m_values[id].m_array;
}

void FutureResourceManager::CleanUpResources()
{
	Lock();
	for(u32 i = 0; i < m_resources.Size(); ++i)
	{
		if(!m_resources[i]->m_resource)
		{
			continue;
		}
		m_resources[i]->m_resource->Lock();
		if(m_resources[i]->m_resource->ShouldUnload())
		{
			FUTURE_LOG_V("Unloading resource %u.", i);
		 	m_resources[i]->m_resource->Unload();

			for(u32 g = 0; g < m_resources[i]->m_resource->m_numGroups; ++g)
			{
				--m_groups[m_resources[i]->m_resource->m_groups[g]].m_loadCounter;
			}

			m_resources[i]->m_resource->m_valid = false;
			m_resources[i]->m_resource->m_loaded = false;
			m_resources[i]->m_resource->m_loading = false;
		}
		if(!m_resources[i]->m_resource->IsLoaded() && !m_resources[i]->m_resource->IsLoading())
		{
			m_resources[i]->m_resource->Unlock();
			delete m_resources[i]->m_resource;
			m_resources[i]->m_resource = NULL;
		}
		if(m_resources[i]->m_resource)
		{
			m_resources[i]->m_resource->Unlock();
		}
	}
	Unlock();
}

extern FutureResource * FutureAutoGenCreateResource(ResourceID resource);

void FutureResourceManager::EnsureResource(ResourceID resource)
{
	Lock();
	if(!m_resources[resource].m_resource)
	{
		m_resources[resource].m_resource = FutureAutoGenCreateResource(resource);
	}
	Unlock();
}

bool FutureResourceManager::UnloadAll()
{
{
	Lock();
	for(u32 i = 0; i < m_resources.Size(); ++i)
	{
		if(!m_resources[i]->m_resource)
		{
			continue;
		}
		m_resources[i]->m_resource->Lock();
		if(m_resources[i]->m_resource->IsLoaded())
		{
			FUTURE_LOG_V("Unloading resource %u.", i);
		 	m_resources[i]->m_resource->Unload();

			for(u32 g = 0; g < m_resources[i]->m_resource->m_numGroups; ++g)
			{
				--m_groups[m_resources[i]->m_resource->m_groups[g]].m_loadCounter;
			}

			m_resources[i]->m_resource->m_valid = false;
			m_resources[i]->m_resource->m_loaded = false;
			m_resources[i]->m_resource->m_loading = false;
		}
		m_resources[i]->m_resource->Unlock();
	}
	Unlock();
}




/*#if defined(FUTURE_TOOL)
bool FutureResourceManager::DumpSystemResources()
{
	FUTURE_ASSERT(HasSystemResources());

	FUTURE_LOG_V("Dumping System Resources");

	Lock();

	bool result = true;
	FutureFileOutputStream * stream = new FutureFileOutputStream();
	if(!stream->Open("assets/_0.dat"));
	{
		FUTURE_ASSET_MSG(false, "Failed to open system resource file");
		result = false;
		goto Finished;
	}
	stream->Write((u32)0);
	stream->Write((u32)FUTURE_VERSION_CODE);

	if(!FutureCoreConfig::DumpConfig(stream))
	{
		FUTURE_ASSET_MSG(false, "Failed to write config file");
		result = false;
		goto Finished;
	}

	stream->WriteCheckSum();
	stream->Write(m_languages);

	stream->Write(m_resources.Size());

	for(u32 i = 0; i < m_resources.Size(); ++i)
	{
		stream->Write(m_resources[i].m_name);
	}

	stream->WriteCheckSum();

	stream->Write(m_groups.Size());
	for(u32 i = 0; i < m_groups.Size(); ++i)
	{
		stream->Write(m_groups[i].m_name);
		stream->Write((u32*)m_groups[i].m_resources.a(), m_groups[i].m_resources.Size())
	}

	stream->WriteCheckSum();

	stream->Write(m_strings.Size());
	for(u32 i = 0; i < m_strings.Size(); ++i)
	{
		stream->Write(m_strings[i].m_tag);
		for(u32 j = 0; j < m_languages; ++j)
		{
			stream->Write(m_strings[i].m_strings[j]);
		}
	}

	stream->WriteCheckSum();

	stream->Write(m_values.Size());
	for(u32 i = 0; i < m_values.Size(); ++i)
	{
		stream->Write((u32)m_values[i].m_type);
		switch(m_values[i].m_type)
		{
			case ValueType_Bool:
				stream->Write(m_values[i].m_bool);
				break;
			case ValueType_U8:
				stream->Write(m_values[i].m_u8);
				break;
			case ValueType_U16:
				stream->Write(m_values[i].m_u16);
				break;
			case ValueType_U32:
				stream->Write(m_values[i].m_u32);
				break;
			case ValueType_S8:
				stream->Write(m_values[i].m_s8);
				break;
			case ValueType_S16:
				stream->Write(m_values[i].m_s16);
				break;
			case ValueType_S32:
				stream->Write(m_values[i].m_s32);
				break;
			case ValueType_F32:
				stream->Write(m_values[i].m_f32);
				break;
			case ValueType_Array:
				stream->Write(m_values[i].m_array, m_values[i].m_size);
				break;
			default:
				FUTURE_ASSET_MSG(false, "Found invalid value type: %u", m_values[i].m_type);
				result = false;
				goto Finished;
		}
	}

	stream->WriteCheckSum();

Finished:
	Unlock();

	if(stream)
	{
		if(stream->IsOpen())
		{	
			stream->Flush();
			stream->Close();
		}
		delete stream;
		stream = NULL;
	}

	if(result)
	{
		FUTURE_LOG_V("Successfully dumped system resources");
	}
	else
	{
		FUTURE_ASSERT_CRIT_MSG(false, "Failed to dump System Resources!");
	}

	return result;
}
#endif*/