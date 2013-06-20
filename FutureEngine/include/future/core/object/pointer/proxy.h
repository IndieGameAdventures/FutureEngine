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
*	A templated proxy that is very similar to a Handle. It will  keep track of how 
*	many references that object has, this allows the object	to be automatically 
*	deleted when it is no longer referenced or goes out of scope.
*
*/

#ifndef FUTURE_CORE_MANAGED_PROXY_H
#define FUTURE_CORE_MANAGED_PROXY_H

#include <future/core/debug/debug.h>
#include <future/core/memory/memory.h>
#include <future/core/object/threadsafeobject.h>
#include <future/core/memory/allocators/poolallocator.h>

class FutureManaged;
class FutureSmartPointerBase;

//useful to have a non-templated base
class FutureProxyBase
{
public:
	virtual void PrintReferences() = 0;

protected:
	// static pool allocator to be used by all proxies
	static FuturePoolAllocator *	ms_poolAllocator;
	static u32						ms_proxyCount;
};

// MANAGED must be derived from FutureManaged or there will be problems
template <class MANAGED> 
class FutureProxy : public FutureProxyBase, public FutureThreadSafeObject
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureProxy<MANAGED>);

    FutureProxy();

	// Construct with an already created object
    FutureProxy(MANAGED * managed);

    virtual ~FutureProxy();

	// Casting to a MANAGED should return the managed object
    operator MANAGED*() const;

	// Get the actual object operator
    MANAGED & operator*() const;

	// Get the managed object so it seems like just calling functions on that
    MANAGED * operator->() const;

	//Get the managed object
	MANAGED * GetManaged();

	// Adds a strong pointer to this proxy. If not using smart pointer then this
	// function will not keep track of the strong pointer but just keep track
	// of how many there are.
    void AddStrongPointer(FutureSmartPointerBase * pointer = NULL);

	// Adds a weak pointer reference to this proxy. In order to properly remove the
	// pointer when managed is deleted, Proxy needs to keep track of all weak pointers,
	// even in release builds
    void AddWeakPointer(FutureSmartPointerBase * pointer);

	// Removes a strong pointer from this proxy. If not using smart pointers, this will
	// simply decrement the pointer count. If there are no strong pointers left, this will
	// automatically delete managed
	void RemoveStrongPointer(FutureSmartPointerBase * pointer = NULL);
	
	// Removes a weak pointer from this proxy. This happens even in release so we can
	// handle the weak pointers when managed is deleted.
	void RemoveWeakPointer(FutureSmartPointerBase * pointer);

	// Print debug information about this proxy's references
	virtual void PrintReferences();

protected:
	// Removes all weak pointers by removing the managed object from the pointer.
	// If the weak pointer is used after this function is called, it will pointer to NULL
	void RemoveAllWeakPointers();

	// keep track of references in a linked list style
	struct PointerReference
	{
		PointerReference()
		: m_next(NULL),
		  m_prev(NULL),
		  m_pointer(NULL)
		{ ; }

		PointerReference *			m_next;
		PointerReference *			m_prev;

		FutureSmartPointerBase *	m_pointer;
	};


	PointerReference *	m_weak; // Pointer to the head of the weak pointer references
	// no reason to track strong pointers except when debugging
#if FUTURE_TRACK_STRONG_POINTERS
	PointerReference *	m_strong; // Pointer to the head of the strong pointer references
#endif

	MANAGED *	m_managed;	// The object being managed MUST BE DERIVED FROM FutureManaged
    u32			m_numStrong; // The number of strong pointers
	u32			m_numWeak;	// the number of weak pointers

private:
	// proxies cannot be set equal to each other, that means the object has been
	// destroyed and recreated without the proxy or any smart pointers knowing
	FutureProxy<MANAGED>& operator=(FutureProxy<MANAGED>& managed){};
	FutureProxy(const FutureProxy<MANAGED>& managed){};
};

#include <future/core/object/pointer/proxy.inl>

#endif
