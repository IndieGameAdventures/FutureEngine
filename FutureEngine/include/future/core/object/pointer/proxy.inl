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
*	Implementation of FutureProxy
*
*/

template<class MANAGED>
FutureProxy<MANAGED>::FutureProxy() 
: m_managed(NULL),
	m_numStrong(0),
	m_numWeak(0),
	m_strong(NULL),
	m_weak(NULL)
{
	if(!ms_poolAllocator)
	{
		ms_poolAllocator = new FuturePoolAllocator(0, sizeof(PointerReference), 1024, false);
	}
	++ms_proxyCount;
}

// Construct with an already created object
template<class MANAGED>
FutureProxy<MANAGED>::FutureProxy(MANAGED * managed)
: m_managed(managed),
	m_numStrong(0),
	m_numWeak(0),
	m_strong(NULL),
	m_weak(NULL)
{
	// make sure the object extends FutureManaged
	FUTURE_ASSERT(dynamic_cast<FutureManaged*>(managed) != NULL);
	if(!ms_poolAllocator)
	{
		ms_poolAllocator = new FuturePoolAllocator(0, sizeof(PointerReference), 1024, false);
	}
	++ms_proxyCount;
}

template<class MANAGED>
FutureProxy<MANAGED>::~FutureProxy() 
{
	// If the proxt was deleted and there are still strong pointers then something
	// wasn't cleaned up properly
	FUTURE_ASSERT_MSG(m_numStrong == 0, L"This object still have Strong Pointers, it cannot be deleted");
	RemoveAllWeakPointers(); // Get rid of the left over weak pointers
	// if we are managing an object then set it's proxy to NULL
	if(m_managed) 
	{
        m_managed->SetProxy(NULL);
    }
    m_managed = NULL;
	--ms_proxyCount;
	if(ms_proxyCount <= 0 && ms_poolAllocator)
	{
		ms_poolAllocator->Release();
		delete ms_poolAllocator;
	}
}

// Casting to a MANAGED should return the managed object
template<class MANAGED>
inline operator FutureProxy<MANAGED>::MANAGED*() const 
{
    return m_managed; 
}

// Get the actual object operator
template<class MANAGED>
inline MANAGED & FutureProxy<MANAGED>::operator*() const 
{
    FUTURE_ASSERT(m_managed); 
    return *m_managed; 
}

// Get the managed object so it seems like just calling functions on that
template<class MANAGED>
inline MANAGED * FutureProxy<MANAGED>::operator->() const 
{
    FUTURE_ASSERT(m_managed); 
    return m_managed; 
}

//Get the managed object
template<class MANAGED>
inline MANAGED * FutureProxy<MANAGED>::GetManaged()
{
	return m_managed;
}

// Adds a strong pointer to this proxy. If not using smart pointer then this
// function will not keep track of the strong pointer but just keep track
// of how many there are.
template<class MANAGED>
void FutureProxy<MANAGED>::AddStrongPointer(FutureSmartPointerBase * pointer = NULL) 
{ 
	Lock();
#if FUTURE_TRACK_STRONG_POINTERS
    if(pointer)
	{
		// Create a new reference to the pointer and push it on top of the reference list
		PointerReference * ref = new (ms_poolAllocator->Alloc(sizeof(PointerReference))) PointerReference();
		if(m_strong)
		{
			m_strong->m_prev = ref;
		}
		ref->m_next = m_strong;
		ref->m_pPrev = NULL;
		m_strong = ref;
		m_strong->m_pointer = pointer;
	}
#endif
	++m_numStrong;
	Unlock();
}

// Adds a weak pointer reference to this proxy. In order to properly remove the
// pointer when managed is deleted, Proxy needs to keep track of all weak pointers,
// even in release builds
template<class MANAGED>
void FutureProxy<MANAGED>::AddWeakPointer(FutureSmartPointerBase * pointer) 
{
    FUTURE_ASSERT(pointer);

	Lock();
	// create the new pointer reference and add it to the top of the weak list
	PointerReference * ref = new (ms_poolAllocator->Alloc(sizeof(PointerReference))) PointerReference();
	if(m_weak)
	{
		m_weak->m_prev = ref;
	}
	ref->m_next = m_weak;
	ref->m_pPrev = NULL;
	m_weak = ref;
	m_weak->m_pointer = pointer;
		
	++m_numWeak;
	Unlock();
}

// Removes a strong pointer from this proxy. If not using smart pointers, this will
// simply decrement the pointer count. If there are no strong pointers left, this will
// automatically delete managed
template<class MANAGED>
void FutureProxy<MANAGED>::RemoveStrongPointer(FuturePointerBase * pointer = NULL) 
{ 
	Lock();
#if FUTURE_TRACK_STRONG_POINTERS
    if(pointer)
	{
		// Loop through the list until we find the pointer in our list
		for(PointerReference * ref = m_strong; ref; ref = ref->m_next)
		{
			if(ref->m_pointer == pointer)
			{
				// remove it from the list
				if(ref->m_prev)
				{
					ref->m_prev->m_next = ref->m_next;
				}
				if(ref->m_next )
				{
					ref->m_next->m_prev = ref->m_prev;
				}
				if(ref == m_strong)
				{
					m_strong = ref->m_next;
				}
				// and delete the reference
				ms_poolAllocator->Free(ref);
				break;
			}
		}
	}
#endif
	// decrement the strong pointer count
	--m_numStrong;
	// if we have a managed but no longer have anything pointing to it,
	// release and delete the object
	if(m_numStrong <= 0 && m_managed)
	{
		m_managed->Release();
		delete m_managed;
		m_managed = NULL;
	}
	Unlock();
}
	
// Removes a weak pointer from this proxy. This happens even in release so we can
// handle the weak pointers when managed is deleted.
template<class MANAGED>
void FutureProxy<MANAGED>::RemoveWeakPointer(FuturePointerBase * pointer) 
{ 
	Lock();
	FUTURE_ASSERT(pointer);
		
	// loop through and find the reference for this pointer
	for(PointerReference * ref = m_weak; ref; ref = ref->m_next)
	{
		if(ref->m_pointer == pointer)
		{
			// remove it from the list
			if(ref->m_prev)
			{
				ref->m_prev->m_next = ref->m_next;
			}
			if(ref->m_next)
			{
				ref->m_next->m_prev = ref->m_prev;
			}
			if(ref == m_weak)
			{
				m_weak = ref->m_next;
			}
			// and delete it
			ms_poolAllocator->Free(ref);
			--m_numWeak;
			return;
		}
		Unlock();
	}
		
	FUTURE_ASSERT_MSG(false, L"This Weak Pointer is not a part of this proxy");
}

// Print debug information about this proxy's references
template<class MANAGED>
void FutureProxy<MANAGED>::PrintReferences()
{
	// Print all the weak pointers
	FUTURE_LOG_DEBUG( L"\n%u weak pointers", m_NumWeak );
	FUTURE_LOG_DEBUG( L"Printing Weak Pointers" );
	for(PointerReference * ref = m_weak; ref; ref = ref->m_next )
	{
		FUTURE_LOG_DEBUG( L"\t0x%x,", *ref );
	}

	// Print all the strong pointers
	FUTURE_LOG_DEBUG( L"\n%u strong pointers", m_numStrong );
#if FUTURE_TRACK_STRONG_POINTERS
	FUTURE_LOG_DEBUG( L"Printing Strong Pointers" );
	for(PointerReference * ref = m_strong; ref; ref = ref->m_next )
	{
		FUTURE_LOG_DEBUG( L"\t0x%x,", *ref );
	}
#endif
}

// Removes all weak pointers by removing the managed object from the pointer.
// If the weak pointer is used after this function is called, it will pointer to NULL
template<class MANAGED>
void FutureProxy<MANAGED>::RemoveAllWeakPointers()
{
	PointerReference * next = NULL;
	// Loop through all the weak pointers
	for(PointerReference * ref = m_weak; ref; ref = next)
	{
		// set the object they are pointing to to NULL
		// and delete the reference
		next = ref->m_next;
		ref->m_pointer = NULL;
		ms_poolAllocator->Free(ref);
		--m_numWeak;
	}
	if(next)
	{
		ms_poolAllocator->Free(next);
	}
	// make sure we don't have any references left
	FUTURE_ASSERT(m_numWeak == 0);
}
