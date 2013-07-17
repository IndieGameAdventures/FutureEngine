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
*	Implementation of FutureManagedObject
*/
#include <future/core/debug/debug.h>
#include <future/core/memory/memory.h>
#include <future/core/object/pointer/proxy.h>
#include <future/core/object/managedobject.h>
#include <future/core/object/singleton.h>

FuturePoolAllocator *	FutureProxyBase::ms_poolAllocator = NULL;
u32						FutureProxyBase::ms_proxyCount = 0;

FutureManagedObject::FutureManagedObject() 
: m_proxy(NULL)
{}

FutureManagedObject::FutureManagedObject(const FutureManagedObject& managed) 
: m_proxy(NULL)
{}

FutureManagedObject::~FutureManagedObject() 
{ 
    if(m_proxy) 
	{           
		delete m_proxy; 
        m_proxy = NULL; 
    }
}

FutureManagedObject& FutureManagedObject::operator=(const FutureManagedObject& managed) 
{
	// we don't want to copy anything so this new object has its own proxy
    return *this; 
}

FutureProxyBase * FutureManagedObject::Proxy() const 
{
    return m_proxy;
}

void FutureManagedObject::SetProxy(FutureProxyBase * proxy) 
{
    FUTURE_ASSERT_MSG(!m_proxy || !proxy, L"Object can only have one proxy");
    m_proxy = proxy;
}

void FutureManagedObject::PrintReferences()
{
#if FUTURE_USE_SMART_POINTERS
	FUTURE_ASSERT(m_proxy);
	m_proxy->PrintReferences();
#endif
}

