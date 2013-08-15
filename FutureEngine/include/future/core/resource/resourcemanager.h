/*
 *  Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */


#ifndef FUTURE_CORE_RESOURCE_MANAGER_H
#define FUTURE_CORE_RESOURCE_MANAGER_H

#include <future/core/type/type.h>
#include <future/core/memory/memory.h>
#include <future/core/util/container/array.h>
#include <future/core/resource/resource.h>
#include <future/core/object/threadsafeobject.h>

class FutureResourceManager : public FutureThreadSafeObject
{
protected:
    friend class FutureApplication;

	static void CreateInstance();
	static void DestroyInstance();

	FutureResourceManager();
	virtual ~FutureResourceManager();

public:
    FUTURE_DECLARE_MEMORY_OPERATORS(FutureResourceManager);
    
    static FutureResourceManager * GetInstance();

    typedef void (*LoadFinishedCallback)(bool success, s32 loadedId);

    bool					LoadSystemResources(LoadFinishedCallback callback);
    bool					LoadSystemResourcesSync(LoadFinishedCallback callback = NULL);
    bool					HasSystemResources();
    bool                    UnloadAll();

    bool                    PreloadGroupInfo(ResourceGroupID group);

    bool					LoadGroup(ResourceGroupID group, LoadFinishedCallback callback);
    bool					LoadGroupSync(ResourceGroupID group, LoadFinishedCallback callback = NULL);
    bool					IsGroupLoaded(ResourceGroupID group);

    bool					UnloadGroup(ResourceGroupID group, bool force = false);

    bool                    FlipGroup(ResourceGroupID groupToLoad, ResourceGroupID groupToUnload, LoadFinishedCallback callback);
    bool                    FlipGroupSync(ResourceGroupID groupToLoad, ResourceGroupID groupToUnload, LoadFinishedCallback callback = NULL);

    ResourceGroupID			GetGroupID(const char * name);
    const char *			GetGroupName(ResourceGroupID group);
    u32	            		GetNumGroupResources(ResourceGroupID group);

    bool                    LoadResource(ResourceID resource, LoadFinishedCallback callback, Language language = Language_Null);
    bool                    LoadResourceSync(ResourceID resource, LoadFinishedCallback callback = NULL, Language language = Language_Null);
    bool                    IsResourceLoaded(ResourceID resource);
    ResourceID              LoadCustomResource(const char * file, FutureResource * resource);

    bool                    UnloadResource(ResourceID resource);

    ResourceID				GetResourceID(const char * name);
    const char *			GetResourceName(ResourceID resource);

    FutureResource *		GetResource(ResourceID resource, bool loadIfNeeded = true, bool loadAsync = true);

    StringID                GetStringIDByTag(const char * tag);
    const char *            GetStringTag(StringID id);
    const char *			GetString(StringID id, Language language = Language_Null);


    ValueID                 GetValueIDByName(const char * name);
    const char *            GetValueName(ValueID id);
    ValueType               GetValueType(ValueID id);

    bool					GetBool(ValueID id);
    u8                      GetU8(ValueID id);
    u16                     GetU16(ValueID id);
    u32						GetU32(ValueID id);
    s8                      GetS8(ValueID id);
    s16                     GetS16(ValueID id);
    s32                     GetS32(ValueID id);
    f32						GetFloat(ValueID id);

    const void *			GetValue(ValueID id, u32 * bytes);
    const bool *            GetBoolArray(ValueID id, u32 * elements);
    const u8 *              GetU8Array(ValueID id, u32 * elements);
    const u16 *             GetU16Array(ValueID id, u32 * elements);
    const u32 *             GetU32Array(ValueID id, u32 * elements);
    const s8 *              GetS8Array(ValueID id, u32 * elements);
    const s16 *             GetS16Array(ValueID id, u32 * elements);
    const s32 *             GetS32Array(ValueID id, u32 * elements);
    const f32 *             GetFloatArray(ValueID id, u32 * elements);

    // Should be called by the main thread, may take some time
    void                    CleanUpResources();

protected:

    void                    EnsureResource(ResourceID resource);
    FutureResource *        CreateResource(ResourceID resource);

    struct ResourceInfo
    {
        const char *                        m_name;
        FutureResource *                    m_resource;
        FutureArray<LoadFinishedCallback>   m_loadFinishedCallbacks;
    };
    
    struct GroupInfo
    {
        const char *                        m_name;
        bool                                m_loadAttempted;
        u32                                 m_loadCounter;
        FutureArray<ResourceID>             m_resources;
        FutureArray<LoadFinishedCallback>   m_loadFinishedCallbacks;
    };

    struct StringInfo
    {
        const char *    m_tag;
        const char *    m_strings[];
    };

    struct ValueInfo
    {
        const char *    m_name;
        union
        {
            bool        m_bool;
            u8          m_u8;
            u16         m_u16;
            u32         m_u32;
            s8          m_s8;
            s16         m_s16;
            s32         m_s32;
            f32         m_f32;
            struct
            {
                u32         m_size;
                void *      m_array;
            };   
        };
        ValueType       m_type;
    };

    u32                         m_languages;
    FutureArray<ResourceInfo>   m_resources;
    FutureArray<GroupInfo>      m_groups;
    FutureArray<StringInfo>     m_strings;
    FutureArray<ValueInfo>      m_values;
};


#endif