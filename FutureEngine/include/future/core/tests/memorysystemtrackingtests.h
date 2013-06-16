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
*	Timer class. Static function can be used to get current time and difference
*	between time. Instanced timer can call function every so often or get time since start.
*	All time is handled in seconds.
*/

#ifndef FUTURE_CORE_UTILS_TIMER_H
#define FUTURE_CORE_UTILS_TIMER_H

#include <future/core/type/type.h>

class FutureTimer
{
public:
	static f32	CurrentTime();
	static f32	TimeSince(f32 start); 

	static f32	MilliToSeconds(s64 milliSeconds);
	static s64	SecondsToMillis(f32 seconds);

	// TODO: add timer instances
};
	

#endif