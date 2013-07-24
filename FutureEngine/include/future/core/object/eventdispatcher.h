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
*	An object that sends out notfications when events occur
*/

#ifndef FUTURE_CORE_OBJECT_EVENT_DISPATCHER_H
#define FUTURE_CORE_OBJECT_EVENT_DISPATCHER_H

#include <future/core/type/type.h>
#include <future/core/thread/criticalsection/criticalsection.h>
#include <future/core/utils/container/array.h>
#include <future/core/utils/event.h>

class FutureEventDispatcher
{
public:

	FutureEventDispatcher();
	virtual ~FutureEventDispatcher();

    typedef bool (*FutureEventListener)(const FutureEvent);
    
    virtual void    AddEventListener(const char * event, FutureEventListener listener, u32 priority = 0);
    virtual void    RemoveEventListener(const char * event, FutureEventListener listener, u32 priority = 0);
    
    virtual void    AddEventListener(u32 event, FutureEventListener listener, u32 priority = 0);
    virtual void    RemoveEventListener(u32 event, FutureEventListener listener, u32 priority = 0);
    
    virtual u32     GetEventId(const char * event);

    virtual bool    HasListener(const char * event);
    virtual bool    HasListener(u32 event);

    virtual void    ClearListeners(const char * event = NULL);
    virtual void    ClearListeners(u32 = 0);

    virtual void    DispatchEvent(const char * event, void * data = NULL, void * sender = NULL, void * target = NULL);
    virtual void    DispatchEvent(u32 event, void * data = NULL, void * sender = NULL, void * target = NULL);
};

#endif