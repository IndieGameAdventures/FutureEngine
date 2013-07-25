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
*	Implementation of FutureEventDispatcher
*/

#include <future/core/debug/debug.h>

FutureEventDispatcher::FutureEventDispatcher()
	: m_events()
{}

FutureEventDispatcher::~FutureEventDispatcher()
{
	for(u32 i = 0; i < m_events.Length(); ++i)
	{
		m_events[i].m_listeners.Clear();
	}
	m_events.Clear();
}


void    FutureEventDispatcher::AddEventListener(const char * event, FutureEventListener listener)
{
	AddEventListener(GetEventId(event), listener);
}

void    FutureEventDispatcher::RemoveEventListener(const char * event, FutureEventListener listener)
{
	RemoveEventListener(GetEventId(event), listener);
}

void    FutureEventDispatcher::AddEventListener(s32 event, FutureEventListener listener)
{
	m_events[event].m_listeners.Add(listener);
}
void    FutureEventDispatcher::RemoveEventListener(s32 event, FutureEventListener listener)
{
	m_events[event].m_listeners.Remove(listener);
}

s32     FutureEventDispatcher::AddEvent(const char * event)
{
	DispatchEvent e = DispatchEvent();
	e.m_name = strcpy(event);
	m_events.Add(e);
	return m_events.Length();
}
s32     FutureEventDispatcher::GetEventId(const char * event)
{
	for(s32 i = 0; i < m_events.Length(); ++i)
	{
		if(strcmp(m_events[i].m_name, event) == 0)
		{
			return i;
		}
	}
	return AddEvent(event);
}

bool   	FutureEventDispatcher::HasListener(const char * event)
{
	return HasListener(GetEventId(event));
}
bool    FutureEventDispatcher::HasListener(s32 event)
{
	return m_events[event].m_listeners.Length() > 0;
}

void    FutureEventDispatcher::ClearListeners(const char * event)
{
	ClearListeners(GetEventId(event));
}
void    FutureEventDispatcher::ClearListeners(s32 event)
{
	m_events[event].m_listeners.Clear();
}

void    FutureEventDispatcher::DispatchEvent(const char * event, void * data, void * sender, void * target)
{
	DispatchEvent(GetEventId(event), data, sender, target);
}
void    FutureEventDispatcher::DispatchEvent(s32 event, void * data, void * sender, void * target)
{
	FutureEvent e = FutureEvent();
	e.m_name = strcpy(m_events[event].m_name;
    e.m_id = event;
    e.m_time = FutureTimer::CurrentTime();
    e.m_data = m_data;
    e.m_sender = (sender != NULL ? sender : this);
    e.m_target = target;

    for(s32 i = 0; i < m_events[event].m_listeners.Length(); ++i)
    {
    	m_events[event].m_listeners[i](e);
    }
}