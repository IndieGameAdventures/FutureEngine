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

#include <future/core/resource/resource.h>
#include <future/core/util/stream.h>

FutureResource::FutureResource()
	: m_id(ResourceID_Null),
	  m_numGroups(0),
	  m_groups(NULL),
	  m_valid(false),
	  m_loaded(false),
	  m_loading(false),
	  m_refs(0),
	  m_groupRefs(0)
{}

FutureResource::~FutureResource()
{
	FUTURE_ASSERT_MSG(m_refs == 0 && m_groupRefs == 0, "This resource is being deleted while before all references have been removed.");
	if(m_groups)
	{
		delete m_groups;
		m_groups = NULL;
	}
}

bool FutureResource::IsInGroup(ResourceGroupID group) const
{
	for(u32 i = 0; i < m_numGroups; ++i)
	{
		if(m_groups[i] == group)
		{
			return true;
		}
	}
	return false;
}

bool FutureResource::Load(ResourceID id, IFutureInputStream * stream)
{
	if(m_loaded)
	{
		return false;
	}
	m_id = (ResourceID)stream->ReadU32();
	if(m_id != id)
	{
		return false;
	}

	m_groups = (ResourceGroupID*)stream->ReadU32Array(&m_numGroups);

	return stream->ReadCheckSum();
}

bool FutureResource::Unload()
{
	return m_loaded;
}

bool FutureResource::Dump(IFutureOutputStream * stream)
{	
	if(!m_loaded)
	{
		return false;
	}
	if(!stream->Write((u32)m_id))
	{
		return false;
	}
	if(m_groups)
	{
		if(!stream->Write((u32*)m_groups, m_numGroups))
		{
			return false;
		}
	}
	else
	{
		u32 temp = (u32)ResourseGroupID_Null;
		if(!stream->Write(&temp, 1))
		{
			return false;
		}
	}

	return stream->WriteCheckSum();
}

void FutureResource::AddRef()
{
	Lock():
	++m_refs;
	Unlock();
}
void FutureResource::Release()
{
	Lock():
	--m_refs;
	Unlock();
}

void FutureResource::AddGroupRef()
{
	Lock():
	++m_groupRefs;
	Unlock();
}
void FutureResource::GroupRelease()
{
	Lock():
	--m_groupRefs;
	Unlock();
}

bool FutureResource::ShouldUnload()
{
	return m_groupRefs == 0 && m_refs == 0;
}
