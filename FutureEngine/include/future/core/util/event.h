/*
 *	Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
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

#ifndef FUTURE_CORE_UTIL_EVENT_H
#define FUTURE_CORE_UTIL_EVENT_H

#include <future/core/type/type.h>
#include <future/core/memory/memory.h>

// Forward Declares
class FutureEventDispatcher;
class FutureSceneNode;

/*!
 *	\brief		A class containing the base data used by all events.
 *
 *	\details 	This class is created by a FutureEventDispatcher and sent out to all registered
 *				listeners that the event applies to. The listener can set m_continueDispatching
 *				to false and the event will not be sent to any other listeners.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		August 2013
 */
class FutureEvent
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureEvent);
    
    bool								m_continueDispatching;	//! This event will continue to propogate through it's listeners until this is set to false.

    const u32    						m_eventType;			//!	The type id of the event, assigned by the EventManager
    const f32        					m_createTime;			//! The time in seconds that this event was created
    
    const void *      					m_data;					//!	Any custom data that was sent with the event
    const WPtr<FutureSceneNode>      	m_sender;				//!	The scene node that created this event, NULL if a non-SceneNode created the event
    const WPtr<FutureSceneNode>      	m_target;				//! The scene node target of the event, (the node that clicked on, or the node that is being destroyed), may be NULL
    const WPtr<FutureEventDispatcher>	m_dispatcher;			//! The event dispatcher that sent out this event, might be the EventManager
};

#endif