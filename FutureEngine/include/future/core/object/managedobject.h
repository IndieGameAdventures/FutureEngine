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

/*	FutureManaged keeps track of all references and deletes itself when no more strong
*	references exist.  Pointers to a managed class should be assigned by use of
*	strong and weak pointers.  Strong pointers must be set to NULL before a managed class
*	can be deleted and all weak pointers will be deleted at the time the managed class is
*	deleted.
*
*	To create a managed object the implementer must create it through the pointer class
*
*	example:
*
*	SPtr<FutureManaged> m_managed = new FutureManaged(); // creates a strong pointer
*	
*	WPtr<FutureManaged> m_managed = new FutureManaged(); // creates a weak pointer
*
*	Smart Pointers are used exactly the same way normal pointers are: *, &, ->, =
*/

#ifndef FUTURE_CORE_MANAGED_H
#define FUTURE_CORE_MANAGED_H

#include <future/core/debug/debug.h>
#include <future/core/memory/memory.h>
#include <future/core/object/pointer/proxy.h>
#include <future/core/object/pointer/smartpointer.h>
#include <future/core/object/threadsafeobject.h>

class FutureManagedObject : public FutureThreadSafeObject
{
public:
    FutureManagedObject();
    FutureManagedObject(const FutureManagedObject& managed);

    virtual ~FutureManagedObject();

	virtual void Release()
	{}

    FutureManagedObject& operator=(const FutureManagedObject& managed);

    FutureProxyBase * Proxy() const;
    void SetProxy(FutureProxyBase * proxy);

	void PrintReferences();

protected:
    FutureProxyBase *	m_proxy;
};

// strong and weak pointer defines
#ifndef SPtr
#	define SPtr	FutureStrongPointer
#endif
#ifndef WPtr
#	define WPtr FutureWeakPointer
#endif

#endif
