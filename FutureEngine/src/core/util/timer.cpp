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

/*
*	Implementation of FutureTimer
*/

#include <future/core/utils/timer/timer.h>

#include <ctime>

/*******************************************************************/

f32	FutureTimer::CurrentTime()
{
	return (f32)clock() / (f32)CLOCKS_PER_SEC;
};

f32	FutureTimer::TimeSince(f32 start)
{
	return CurrentTime() - start;
}; 

f32	FutureTimer::MilliToSeconds(s64 milliSeconds)
{
	return (f32)milliSeconds / 1000.f;
};

s64	FutureTimer::SecondsToMillis(f32 seconds)
{
	return (u64)(seconds * 1000.f);
};