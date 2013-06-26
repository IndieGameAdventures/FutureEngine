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
*	Implementation of FutureSmartPointer
*
*/

// If using smart pointers, all functions will use proxy
#if FUTURE_USE_SMART_POINTERS
template<class MANAGED> 
FutureSmartPointer<MANAGED>::FutureSmartPointer() 
	: m_proxy(NULL) 
{}

template<class MANAGED> 
FutureSmartPointer<MANAGED>::FutureSmartPointer(MANAGED * managed) 
	: m_proxy(NULL) 
{
	if(!managed)
	{
		return;
	}
    if(!managed->Proxy())
	{
        // This is the first pointer to access
        // the object so create its proxy
        managed->SetProxy(new FutureProxy<MANAGED>(managed));
    }
    m_proxy = reinterpret_cast<FutureProxy<MANAGED>*>(managed->Proxy());
	AddToProxy();
}

template<class MANAGED> 
FutureSmartPointer<MANAGED>::FutureSmartPointer(const FutureSmartPointer<MANAGED>& pointer) 
{
    m_proxy = pointer.m_proxy;
    if(m_proxy) 
	{
        AddToProxy();
    }
}

template<class MANAGED> 
FutureSmartPointer<MANAGED>::~FutureSmartPointer() 
{ 
    if(m_proxy) 
	{
        RemoveFromProxy(); 
    }
}

template<class MANAGED> 
inline FutureSmartPointer<MANAGED>::operator MANAGED*() const 
{
    return m_proxy->operator MANAGED*();
}

template<class MANAGED> 
inline MANAGED& FutureSmartPointer<MANAGED>::operator*() const 
{ 
    return m_proxy->operator*(); 
}

template<class MANAGED> 
inline MANAGED* FutureSmartPointer<MANAGED>::operator->() const 
{ 
    return m_proxy->operator->(); 
}

template<class MANAGED> 
inline FutureSmartPointer<MANAGED>& FutureSmartPointer<MANAGED>::operator=(FutureSmartPointer<MANAGED>& pointer) 
{ 
    return operator=((MANAGED*)pointer); 
}

template<class MANAGED> 
inline FutureSmartPointer<MANAGED>& FutureSmartPointer<MANAGED>::operator=(MANAGED * managed) 
{
	if(m_proxy)
	{
		if(m_proxy->GetManaged() != managed)
		{
			RemoveFromProxy();
		}
		else
		{
			return *this;
		}
	}

    if(managed)
	{
        if(!managed->Proxy()) 
		{
            managed->SetProxy(new FutureProxy<MANAGED>(managed));
        }
        m_proxy = (FutureProxy<MANAGED>*)(managed->Proxy());
        AddToProxy();
    }
    return *this; 
}

template<class MANAGED> 
inline FutureProxy<MANAGED> * FutureSmartPointer<MANAGED>::Proxy() const
{ 
    return m_proxy;
}
	
template<class MANAGED> 
inline MANAGED * FutureSmartPointer<MANAGED>::GetManaged() const
{ 
    return m_proxy->GetManaged();
}


#else

template<class MANAGED> 
FutureSmartPointer<MANAGED>::FutureSmartPointer() 
: m_managed(NULL) 
{}

template<class MANAGED> 
FutureSmartPointer<MANAGED>::FutureSmartPointer(MANAGED * managed) 
: m_managed(managed) 
{
}

template<class MANAGED> 
FutureSmartPointer<MANAGED>::FutureSmartPointer(const FutureSmartPointer<MANAGED>& pointer) 
{
    m_managed = pointer.GetManaged();
}

template<class MANAGED> 
FutureSmartPointer<MANAGED>::~FutureSmartPointer() 
{ 
	m_managed = NULL;
}

template<class MANAGED> 
inline operator FutureSmartPointer<MANAGED>::MANAGED*() const 
{
    return m_managed;
}

template<class MANAGED> 
inline MANAGED& FutureSmartPointer<MANAGED>::operator*() const 
{ 
    FUTURE_ASSERT(m_managed); 
    return *m_managed;
}

template<class MANAGED> 
inline MANAGED* FutureSmartPointer<MANAGED>::operator->() const 
{ 
    FUTURE_ASSERT(m_managed); 
    return m_managed;
}

template<class MANAGED> 
inline FutureSmartPointer<MANAGED>& FutureSmartPointer<MANAGED>::operator=(FutureSmartPointer<MANAGED>& pointer) 
{ 
    return operator=((MANAGED*)pointer); 
}

template<class MANAGED> 
inline FutureSmartPointer<MANAGED>& FutureSmartPointer<MANAGED>::operator=(MANAGED * managed) 
{
	m_managed = managed;
    return *this; 
}

template<class MANAGED> 
inline FutureProxy<MANAGED> * FutureSmartPointer<MANAGED>::Proxy() const
{ 
    return NULL;
}
	
template<class MANAGED> 
inline MANAGED * FutureSmartPointer<MANAGED>::GetManaged() const
{ 
    return m_managed;
}

#endif

template<class MANAGED> 
FutureStrongPointer<MANAGED>::FutureStrongPointer() 
	: FutureSmartPointer<MANAGED>() 
{}

template<class MANAGED> 
FutureStrongPointer<MANAGED>::FutureStrongPointer(MANAGED * managed) 
	: FutureSmartPointer<MANAGED>(managed) 
{}

template<class MANAGED> 
FutureStrongPointer<MANAGED>::FutureStrongPointer(const FutureSmartPointer<MANAGED>& pointer) 
	: FutureSmartPointer<MANAGED>(pointer) 
{}

template<class MANAGED> 
inline void FutureStrongPointer<MANAGED>::AddToProxy()
{
	if(FutureSmartPointer<MANAGED>::Proxy())
	{
		FutureSmartPointer<MANAGED>::Proxy()->AddStrongPointer(this);
	}
}
template<class MANAGED> 
inline void FutureStrongPointer<MANAGED>::RemoveFromProxy()
{
	if(FutureSmartPointer<MANAGED>::Proxy())
	{
		FutureSmartPointer<MANAGED>::Proxy()->RemoveStrongPointer(this);
	}
}

template<class MANAGED> 
FutureWeakPointer<MANAGED>::FutureWeakPointer() 
	: FutureSmartPointer<MANAGED>() 
{}

template<class MANAGED> 
FutureWeakPointer<MANAGED>::FutureWeakPointer(MANAGED * managed) 
	: FutureSmartPointer<MANAGED>(managed) 
{}

template<class MANAGED> 
FutureWeakPointer<MANAGED>::FutureWeakPointer(const FutureSmartPointer<MANAGED>& pointer) 
	: FutureSmartPointer<MANAGED>(pointer) 
{}
template<class MANAGED> 
inline void FutureWeakPointer<MANAGED>::AddToProxy()
{
	if(FutureSmartPointer<MANAGED>::Proxy())
	{
		FutureSmartPointer<MANAGED>::Proxy()->AddWeakPointer(this);
	}
}
template<class MANAGED> 
inline void FutureWeakPointer<MANAGED>::RemoveFromProxy()
{
	if(FutureSmartPointer<MANAGED>::Proxy())
	{
		FutureSmartPointer<MANAGED>::Proxy()->RemoveWeakPointer(this);
	}
}
