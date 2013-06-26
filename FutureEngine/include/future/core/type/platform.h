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
*	This file contains platform definitions. Here is where the platform and any other
*	platform specific type definitions need to be placed
*/

#ifndef FUTURE_CORE_TYPE_PLATFORM_H
#define FUTURE_CORE_TYPE_PLATFORM_H

//	define the platform

// start them all at 0 then redefine the correct one
#define FUTURE_PLATFORM_WINDOWS			0
#define FUTURE_PLATFORM_WINDOWS_APP		0
#define FUTURE_PLATFORM_WINDOWS_PHONE	0
#define FUTURE_PLATFORM_LINUX			0
#define FUTURE_PLATFORM_MAC				0
#define FUTURE_PLATFORM_ANDROID			0
#define FUTURE_PLATFORM_IPHONE			0
#define FUTURE_PLATFORM_OUYA			0

// predefine the most likely endian, big endian platforms will redefine these
#define FUTURE_ENDIAN_LITTLE 1
#define FUTURE_ENDIAN_BIG	0

#if defined(_ANDROID) || defined(_OUYA) || defined(__ANDROID__) || defined(__android__)
#	undef  FUTURE_PLATFORM_ANDROID
#	define FUTURE_PLATFORM_ANDROID 1
#	if defined(_OUYA)
#		undef  FUTURE_PLATFORM_OUYA
#		define FUTURE_PLATFORM_OUYA 1
#	endif
#	define FUTURE_USES_PTHREAD
#elif defined(_LINUX)
#	undef  FUTURE_PLATFORM_LINUX
#	define FUTURE_PLATFORM_LINUX 1
#	define FUTURE_USES_PTHREAD
#elif defined(__APPLE__) || defined(Macintosh) || defined(macintosh)
#	include "TargetConditionals.h"
#	if TARGET_OS_IPHONE   
#		undef  FUTURE_PLATFORM_IPHONE
#		define FUTURE_PLATFORM_IPHONE 1
#	elif TARGET_IPHONE_SIMULATOR
#		undef  FUTURE_PLATFORM_IPHONE
#		define FUTURE_PLATFORM_IPHONE 1
#		define FUTURE_IPHONE_SIMULATOR
#	elif TARGET_OS_MAC
#		undef  FUTURE_PLATFORM_MAC
#		define FUTURE_PLATFORM_MAC 1
#	else
#		error Found an unsupported Apple product!
#	endif
#	define FUTURE_USES_PTHREAD
#elif defined(_WIN32)
#	undef FUTURE_PLATFORM_WINDOWS
#	define FUTURE_PLATFORM_WINDOWS 1
#	if defined(_WINDOWS_8_METRO)
#		undef FUTURE_PLATFORM_WINDOWS_APP
#		define FUTURE_PLATFORM_WINDOWS_APP 1
#	elif defined(_WINDOWS_PHONE)
#		undef FUTURE_PLATFORM_WINDOWS_PHONE
#		define FUTURE_PLATFORM_WINDOWS_PHONE 1
#	endif
#	if defined(_WIN64)
#		define FUTURE_X64
#   endif
#else
#	error Failed to define a supported platform!
#endif


#if defined(__i386__) || defined(_M_IX86) || defined(_M_AMD64) || defined(_M_IA64) || defined(_M_X64)
#	if defined(_M_IX86_FP)
#		if _M_IX86_FP != 0 && _M_IX86_FP != 1
#			define FUTURE_USES_SSE
#		endif
#	else
#		define FUTURE_USES_SSE
#	endif
#elif defined(arm) || defined(__arm__) || defined(_M_ARM) || defined(_M_ARM_FP)
#	if defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7R__) || defined (__ARM_ARCH_7M__) || ( defined(_M_ARM) && (_M_ARM >= 7) )
#		define FUTURE_USES_NEON 1
#   endif
#elif defined(__PPC) || defined(__PPC__) || defined(_ARCH_PPC) || defined(__POWERPC__)
#	if defined(__ALTIVEC__) || defined(__VEC__)
#		defined FUTURE_USES_ALTIVEC
#	endif
#endif

#endif
