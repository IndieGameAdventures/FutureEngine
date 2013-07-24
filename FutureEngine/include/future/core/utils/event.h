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

#ifndef FUTURE_CORE_UTIL_EVENT_H
#define FUTURE_CORE_UTIL_EVENT_H

#include <future/core/type/type.h>

class FutureEvent
{
public:
    
    string      m_name;
    u32         m_id;
    f32         m_time;
    
    void *      m_data;
    void *      m_sender;
    void *      m_target;
};

#endif