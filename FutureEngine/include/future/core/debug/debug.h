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


/*	\file debug.h
 *	
 *	\brief		Mainly used to more easily include all debug functionality (Assert and Log).
 *	
 *	\details	This file does define the useful macro FUTURE_DEBUG_HALT which triggers a breakpoint.
 *				This is used by the default assert functions and can be used anywhere in code to pass
 *				control of the program to an attached debugger. This macro does nothing in release
 *				builds. It is suggested that the developer provide a FutureAssertCritFunction to
 *				properly handle critical asserts in release builds.
 *
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */

#ifndef FUTURE_CORE_DEBUG_H
#define FUTURE_CORE_DEBUG_H

#include <future/core/type/type.h>

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

#include <future/core/debug/assert.h>
#include <future/core/debug/log.h>

#endif
