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
*	Contains an assert system that allows the user to define their own assert
*	function. AssertCrit contains error code option to allow for end users
*	to send error reports without actually seeing the error message
*/

#ifndef FUTURE_CORE_DEBUG_ASSERT_H
#define FUTURE_CORE_DEBUG_ASSERT_H

#include <future\core\type\type.h>

//#include <stdio.h>
//#include <wchar.h>

#ifndef FUTURE_ASSERT_DEFINE
#define FUTURE_ASSERT_DEFINE

// asserts fail if value given is false
// if failed it calls g_pFnAssert to handle showing the error
// assert is not reported in release builds but assert_crit is

typedef void (*FutureAssertFunction)(string file, u32 line, ...);
typedef void (*FutureAssertCritFunction)(string file, u32 line, s32 errorNum, ...);

extern FutureAssertFunction futureAssertFunction;
extern FutureAssertCritFunction futureAssertCritFunction;

// Set the global assert handler
void FutureSetAssertFunction(FutureAssertFunction assertFunction);
void FutureSetAssertCritFunction(FutureAssertCritFunction assertCritFunction);

#if FUTURE_DEBUG || FUTURE_PROFILE
#	define FUTURE_ASSERT(check)						if(!(check)){ futureAssertFunction(WFILE, __LINE__, WIDEN(TOSTRING(check))); }
#	define FUTURE_ASSERT_MSG(check, ...)	if(!(check)){ futureAssertFunction(WFILE, __LINE__, __VA_ARGS__); }
#else
#	define FUTURE_ASSERT(check)
#	define FUTURE_ASSERT_MSG(check, ...)
#endif

#define FUTURE_ASSERT_CRIT(check, errorCode)					if(!(check)) { futureAssertCritFunction(WFILE, __LINE__, errorCode, WIDEN(TOSTRING(check))); }
#define FUTURE_ASSERT_CRIT_MSG(check, errorCode, ...)	if(!(check)) { futureAssertCritFunction(WFILE, __LINE__, errorCode, __VA_ARGS__); }

#endif

#ifndef FUTURE_STATIC_ASSERT_DEFINE
#define FUTURE_STATIC_ASSERT_DEFINE

template<bool x> struct FUTURE_STATIC_ASSERTION_FAILURE;
template<> struct FUTURE_STATIC_ASSERTION_FAILURE<true>{ enum{unused = 0}; };
template<s32 x> struct future_static_assert_test{};

// asserts at compile time instead of runtime
#define FUTURE_CASSERT(check) 	typedef future_static_assert_test<sizeof(FUTURE_STATIC_ASSERTION_FAILURE<(bool)(check)>)> future_static_assert_typedef

#endif
#endif
