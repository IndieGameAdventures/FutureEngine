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
*	A set of debug functions to help get more information from bugs and to help see
*	what is going on internally
*/

#ifndef FUTURE_CORE_DEBUG_H
#define FUTURE_CORE_DEBUG_H

#include <future\core\type\type.h>

#if FUTURE_DEBUG || FUTURE_PROFILE
#	if FUTURE_PLATFORM_WINDOWS
#		define FUTURE_DEBUG_HALT()	__debugbreak()
#	else
#		include <signal.h>
#		define FUTURE_DEBUG_HALT() raise(SIGTRAP)
#	endif
#else
#	define FUTURE_DEBUG_HALT()
#endif

#include <future\core\debug\assert.h>
#include <future\core\debug\log.h>

#endif // coin_core_debug_h
