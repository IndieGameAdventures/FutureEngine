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
*	FutureSmartPointer acts as an intermediate pointer. It sends assignment operations
*	to the objects proxy for reference counting. It acts as a transparent wrapper so
*	*, &, -> and casts operate as if they were called on the original object and not
*	this wrapper class.
*
*	If FUTURE_USE_SMART_POINTERS is equal to 0 then smart pointers will not forward requests
*	to a proxy but act completely transparently with almost no overhead.
*
*	Smart pointers should be used for any objects that are referenced in multiple places, object
*	that should be deleted when they go out of scope, and any object accessed in a multithreaded
*	environment. Any object that is going to use a Smart Pointer must extend FutureManaged.
*
*	FutureEngine splits smart pointers into 2 classes, Strong pointers and Weak pointers. Strong
*	pointers have an absolute need of the object they are pointing to and will not allow the object
*	to be deleted while they are using it. Weak pointer have a weak relationship to the object
*	they are pointing to. They will not prevent the object from being deleted while they are
*	using it but will set themselves to NULL so they can no longer be used.
*/

#ifndef FUTURE_CORE_MANAGED_SMARTPOINTER_H
#define FUTURE_CORE_MANAGED_SMARTPOINTER_H

#include <future/core/debug/debug.h>
#include <future/core/memory/memory.h>
#include <future/core/object/pointer/proxy.h>

// useful to have a non-templated base
class FutureSmartPointerBase 
{};

template<class MANAGED> 
class FutureSmartPointer
{
public:
	// constructor
    FutureSmartPointer();
	// copy constructor
    FutureSmartPointer(MANAGED * managed);
    FutureSmartPointer(const FutureSmartPointer<MANAGED>& pointer);

    virtual ~FutureSmartPointer();

	// transparent operators
    operator MANAGED*() const;
    MANAGED& operator*() const;
    MANAGED* operator->() const;

	// assignment operators
    FutureSmartPointer<MANAGED>& operator=(FutureSmartPointer<MANAGED>& pointer);
    FutureSmartPointer<MANAGED>& operator=(MANAGED * managed);

    FutureProxy<MANAGED> *	Proxy() const;
	MANAGED *				GetManaged() const;
	
protected:
	// virtual functions, different for strong and weak pointers
	virtual void	AddToProxy() = 0;
	virtual void	RemoveFromProxy() = 0;
	
// If using smart pointers then FutureSmartPointer will interact with a proxy
#if FUTURE_USE_SMART_POINTERS
    FutureProxy<MANAGED> * m_proxy;
#else
	// No proxy so keep our own managed
	MANAGED * m_managed;
#endif
};

// Strong pointers must be set to null or deleted before object can be deleted
template<class MANAGED>
class FutureStrongPointer : public FutureSmartPointer<MANAGED>
{
protected:
	virtual void AddToProxy();
	virtual void RemoveFromProxy();
};

// weak pointers will auto set to NULL when object is deleted
template<class MANAGED>
class FutureWeakPointer : public FutureSmartPointer<MANAGED>
{
protected:
	virtual void AddToProxy();
	virtual void RemoveFromProxy();
};

#include <future/core/object/pointer/smartpointer.inl>

#endif
