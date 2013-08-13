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

#ifndef FUTURE_CORE_UTILS_TIMER_H
#define FUTURE_CORE_UTILS_TIMER_H

#include <future/core/type/type.h>

/*!
 *	\brief		A static class used to get information about the current system time
 *
 *	\details 	FutureTimer contains a set of static functions used to get the current time
 *				and the difference between times. Time is given as the number of seconds that
 *				have passed since the program began. The accuracy of the timer is completely
 *				dependant on the processor clock and the number of cycles per second. The current
 *				time is calculated by dividing the total processor ticks since the beginning of
 *				the program divded by the average number of ticks per second. Time is not
 *				gauranteed to be perfectly, 100%, accurate but it is likely to be within a millisecond
 *				or two of the actual time. Time is also doomed to suffer from float inaccuracy.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */
class FutureTimer
{
public:
	//! Returns the number of seconds this program has been running
	static f32	CurrentTime();
	//! Returns the number of seconds that have passed since the start time
	static f32	TimeSince(f32 start); 

	//! Converts milliseconds into seconds, everything should be handled in seconds
	static f32	MilliToSeconds(s64 milliSeconds);
	//! Converts seconds into milliseconds, everything should be handled in seconds
	static s64	SecondsToMillis(f32 seconds);
};
	

#endif