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
*	This file contains type definitions used by Future Engine. It uses 
*	platform independent keywords to ensure that these definitions will be the
*	same on all platform.
*/

#ifndef FUTURE_CORE_TYPE_H
#define FUTURE_CORE_TYPE_H

#include <future/core/type/platform.h>
#include <wchar.h>

#ifndef FUTURE_PRIMITIVE_DEFINITIONS

	typedef unsigned char 		u8;	
	typedef unsigned short 		u16;
	typedef unsigned int 		u32;
	typedef unsigned long long	u64;

	typedef signed char 		s8;
	typedef signed short 		s16;
	typedef signed long			s32;
	typedef signed long long	s64;

	typedef float				f32;
	typedef double				f64;

	typedef const wchar_t *		string;

	typedef const u32			FutureResult;
#	define FUTURE_PRIMITIVE_DEFINITIONS
#endif

// version definition
#if defined(_DEBUG)
#	define FUTURE_DEBUG 	1
#	define FUTURE_RELEASE 	0
#elif defined(_RELEASE)
#	define FUTURE_DEBUG 	0
#	define FUTURE_RELEASE 	1
#else
#	error A valid build configuration is not defined!
#endif

#if defined(_PROFILE) || FUTURE_DEBUG
#	define FUTURE_PROFILE 1
#else
#	define FUTURE_PROFILE 0
#endif

/****************************************************************************************************/
	// DEBUGGING DEFINES

// determines if memory should be tracked for debugging
#ifndef FUTURE_TRACK_MEMORY
#	define FUTURE_TRACK_MEMORY (FUTURE_DEBUG || (defined(_PROFILE_MEMORY)) || FUTURE_PROFILE)
#endif
	
// determines if FutureProxy should keep track of strong pointer, good for debugging but
// but slightly slower to disabled in release
#ifndef FUTURE_TRACK_STRONG_POINTERS
#	define FUTURE_TRACK_STRONG_POINTERS (FUTURE_DEBUG || (defined(_TRACK_STRONG_POINTERS)) || FUTURE_PROFILE)
#endif
	
// if true the FutureThreadPool will profile the time spent performing jobs
#ifndef FUTURE_PROFILE_THREAD_POOL
#	define FUTURE_PROFILE_THREAD_POOL (FUTURE_DEBUG || (defined(_PROFILE_THREAD_POOL)) || FUTURE_PROFILE)
#endif
	

/****************************************************************************************************/
	// CONFIG DEFINES

// determines if FutureManaged should use smart pointers
// Without this, strong and weak pointer do not perform any debugging, have very little error checking
// And will not auto delete objects
#ifndef FUTURE_USE_SMART_POINTERS
#	if defined(_SMART_POINTERS)
#		define FUTURE_USE_SMART_POINTERS _SMART_POINTERS
#	else
#		define FUTURE_USE_SMART_POINTERS 1
#	endif
#endif

// Enables of disables multithreaded support. If disabled, FutureThread will throw errors if a second
// thread is created and no multithread checks are done. Greatly increases performance if only using
// one thread but should always be enabled if using more than one
#ifndef FUTURE_ENABLE_MULTITHREADED
#	define FUTURE_ENABLE_MULTITHREADED (FUTURE_PLATFORM_WINDOWS || defined(FUTURE_USES_PTHREAD))
#endif

// The number of default threads to the thread pool should create
#ifndef FUTURE_DEFAULT_THREAD_COUNT
#	define FUTURE_DEFAULT_THREAD_COUNT 6
#endif

/****************************************************************************************************/
	// UTILITY DEFINES


// Returns the number of elements in an array
#ifndef FUTURE_ARRAY_LENGTH
#	define	FUTURE_ARRAY_LENGTH(a)			(size_t)(sizeof(a)/sizeof(a[0]))
#endif

// returns the index of the element in the array, element must be a pointer within the array
#ifndef FUTURE_ARRAY_INDEX
#	define	FUTURE_ARRAY_INDEX(a, element)	(size_t)(((size_t)((void*)element)-(size_t)((void*)a))/sizeof(a[element]))
#endif

// Deletes an object bur ensure that the object exists first
#ifndef FUTURE_SAFE_DELETE
#	define FUTURE_SAFE_DELETE( r ) if(r){ delete (r); }
#	define FUTURE_SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); } }
#	define FUTURE_SAFE_RELEASE( r ) if(r){ (r)->Release(); }
#endif

// A custom check sum used to ensure memory is not corrupted
#ifndef FUTURE_CHECKSUM		
#	define FUTURE_CHECKSUM	0xF07012E9
#endif

// FutureResult defines
#define FR_OK ((FutureResult)0)
#define FR_ERROR ((FutureResult)-1)
#define FR_INVALID_ARG ((FutureResult)-2)
#define FR_INVALID_PLATFORM ((FutureResult)-4)
#define FR_INDEX_OUT_OF_BOUNDS ((FutureResult)-8)
#define FR_TIMEOUT ((FutureResult)-16)

// Convert the argument into a string
#ifndef TOSTRING
#	define STRINGIFY(x)	#x
#	define TOSTRING(x)	STRINGIFY(x)
#endif

#ifndef WIDEN
#	define WIDEN2(x) L ## x
#	define WIDEN(x) WIDEN2(x)
#endif

#ifndef WFILE
#	define WFILE WIDEN(__FILE__)
#endif

#ifndef WFUNCTION
#	define WFUNCTION WIDEN(__FUNCTION__)
#endif

#endif
