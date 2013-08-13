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

/*! \file 	type.h
 *	\brief		Contains whole program defines and macros
 *
 *	\details 	Contains macros and typedefs used by the entire program.
 *				Many of these defines are compile time configurations meant
 *				to enable or disable entire feature sets as well create different
 *				Debug, Profile, and Release configurations (ie. small and fast for
 *				release, fast but large for profile, and slow and large for debug).
 *				This allows for purely debugging features to be completely removed
 *				in release builds for a faster, small program.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */

#ifndef FUTURE_CORE_TYPE_H
#define FUTURE_CORE_TYPE_H

#include <future/core/type/platform.h>
#include <future/core/type/language.h>
#include <stdint.h>

#ifndef FUTURE_VERSION_CODE
#	define FUTURE_VERSION_MAJOR 0	//! Future Engine's major version number
#	define FUTURE_VERSION_MINOR 35	//! Future Engine's minor version number
#	define FUTURE_VERSION_CODE (FUTURE_VERSION_MAJOR << 16) | (FUTURE_VERSION_MINOR) //! Future Engine's combined version code
 			/*!	This code is used to make sure all libraries, systems, and resources were compiled with the same version of
 			 *	the engine. Future Engine may run old libraries within the same major version but there is no gaurantee the
 			 *	library will function properly. Libraries compiled with a different major version should assert and fial to run.
 			 *	Resources should operate similarly to libraries but are generally more finicky, resources compiled with newer
 			 *	versions of Future Engine or a different major version will not be loaded. Resources with a different, and lower
 			 *	minor version will attempt to be loaded.
 			 */
#endif

//! Typedefs defining primitive datatypes used by Future Engine
//!	If these datatypes are defined somewhere else, you can define FUTURE_PRIMITIVE_DEFINITIONS to prevent these from being defined
#ifndef FUTURE_PRIMITIVE_DEFINITIONS

	typedef uint8_t 	u8;		//! An unsigned 8 bit value (unsigned char)
	typedef uint16_t	u16;	//! An unsigned 16 bit value (unsigned short)
	typedef uint32_t	u32;	//! An unsigned 32 bit value (unsigned int)
	typedef uint64_t	u64;	//! An unsigned 64 bit value (unsigned long long)

	typedef int8_t		s8; 	//! A signed 8 bit value (char)
	typedef int16_t		s16;	//! A signed 16 bit value (short)
	typedef int32_t		s32;	//! A signed 32 bit value (int)
	typedef int64_t		s64;	//! A signed 64 bit value (long long)

	typedef float		f32;	//! A 32 bit floating point value
	typedef double		f64;	//! A 64 bit floating point value

#	define FUTURE_PRIMITIVE_DEFINITIONS
#endif

// version definition
#if defined(_DEBUG)
#	define FUTURE_DEBUG 	1		//!	This is a debug build so include all the extra debugging features
#	define FUTURE_PROFILE 	0
#	define FUTURE_RELEASE 	0
#elif defined(_PROFILE)
#	define FUTURE_DEBUG 	0
#	define FUTURE_PROFILE 	1		//! This is a profile build so compile for release but include some of the debugging features
#	define FUTURE_RELEASE 	0
#elif defined(_RELEASE)
#	define FUTURE_DEBUG 	0
#	define FUTURE_PROFILE 	0
#	define FUTURE_RELEASE 	1		// A build meant to be published and released, no debugging features
#else
#	error A valid build configuration is not defined!
#endif

/****************************************************************************************************/
	// DEBUGGING DEFINES

//! If true, then extra steps will taken with each memory allocation to track it, allowing for profiling information and leak detection
#ifndef FUTURE_TRACK_MEMORY	
#	define FUTURE_TRACK_MEMORY (FUTURE_DEBUG || (defined(_PROFILE_MEMORY)) || FUTURE_PROFILE)
#endif
	
//! If true then Managed objects will keep track of variables pointing to it instead of just the number of variables
#ifndef FUTURE_TRACK_STRONG_POINTERS
#	define FUTURE_TRACK_STRONG_POINTERS (FUTURE_DEBUG || (defined(_TRACK_STRONG_POINTERS)) || FUTURE_PROFILE)
#endif
	
//! If true, the thread pool will keep track of the amount of time spent handling internal operations on the main thread
#ifndef FUTURE_PROFILE_THREAD_POOL
#	define FUTURE_PROFILE_THREAD_POOL (FUTURE_DEBUG || (defined(_PROFILE_THREAD_POOL)) || FUTURE_PROFILE)
#endif
	

/****************************************************************************************************/
	// CONFIG DEFINES

//! Determines if Managed objects should use smart pointers
//! Without this, strong and weak pointer do not perform any debugging, have very little error checking
//! and will not auto delete objects. It is recommended that you use smart pointers. Though it is possible
//! to allow smart pointers in debug builds and print a warning when an object is auto deleted, this way you
//! can track memory leaks and manually delete objects then turn smart pointers off for release builds
#ifndef FUTURE_USE_SMART_POINTERS
#	if defined(_SMART_POINTERS)
#		define FUTURE_USE_SMART_POINTERS _SMART_POINTERS
#	else
#		define FUTURE_USE_SMART_POINTERS 1
#	endif
#endif

//! Enables or disables multithreaded support. 
//! If disabled, FutureThread will throw errors if a second thread is created. All free thread checks are 
//! also removed. Race conditions, memory curruption and lots of other bad things will happen if used incorrectly.
//! Greatly increases performance if only using one thread but should always be enabled if using more than one.
#ifndef FUTURE_ENABLE_MULTITHREADED
#	define FUTURE_ENABLE_MULTITHREADED 1
#endif

//! The number of default threads the thread pool should create
#ifndef FUTURE_DEFAULT_THREAD_COUNT
#	define FUTURE_DEFAULT_THREAD_COUNT 6
#endif


//! Enables or disables event dispatching.
//! If this is set to TRUE then events will be dispatched to listeners. if FUTURE_ENABLE_ASYNCHRONOUS_EVENT_DISPATCHING
//! is also true then events will be fired immediately. If FUTURE_ENABLE_ASYNCHRONOUS_EVENT_DISPATCHING is false then
//! events will be help in a list until the next postSync phase where they will be fired synchronously on the main thread
//! If this is false, events must be polled.
#ifndef FUTURE_ENABLE_EVENT_DISPATCHING
#	define FUTURE_ENABLE_EVENT_DISPATCHING 1
#endif

//! Enables or disables event polling.
//! Both this and FUTURE_ENABLE_EVENT_DISPATCHING can be true allowing for both dispatching and polling, each has it's own
//! benifit. Polling requires the notification center or the event dispatcher to be asked if it has an event each frame. 
//! Events will be listed as available on the frame following when they actually happened. This will ensure that all pollers
//! have a chance to poll for the event. This also means that events will be received one frame after they occured. The
//! dispatcher will hold on to the event until the postSynch phase of the frame following the creation of the event. 
#ifndef FUTURE_ENABLE_EVENT_POLLING
#	define FUTURE_ENABLE_EVENT_POLLING 1
#endif

//! Enables or disables asynchronous event dispatching.
//! If this is set to 1 then event dispatchers will immediatly send events to all listeners. This is much faster
//! and usually more efficient that polling for events but requires more work on the programmers part as events may
//! be fired on different threads, resulting in potentially important events taking place while in the middle of processing
//! something that event may effect. Requires FUTURE_ENABLE_EVENT_DISPATCHING to be true
#ifndef FUTURE_ENABLE_ASYNCHRONOUS_EVENT_DISPATCHING
#	define FUTURE_ENABLE_ASYNCHRONOUS_EVENT_DISPATCHING FUTURE_ENABLE_EVENT_DISPATCHING
#endif

#if FUTURE_ENABLE_ASYNCHRONOUS_EVENT_DISPATCHING && !FUTURE_ENABLE_EVENT_DISPATCHING
#	error Asynchronous event dispatching requires that event dispatching be enabled
#endif

/****************************************************************************************************/
	// UTILITY DEFINES


//! Returns the number of elements in an array
#ifndef FUTURE_ARRAY_LENGTH
#	define	FUTURE_ARRAY_LENGTH(a)			(size)(sizeof(a)/sizeof(a[0]))
#endif

//! Returns the index of the element in the array, element must be a pointer within the array
#ifndef FUTURE_ARRAY_INDEX
#	define	FUTURE_ARRAY_INDEX(a, element)	(size)(((size)((ptr)element)-(size)((ptr)a))/sizeof(a[element]))
#endif

//! Deletes an object but ensure that the object exists first
#ifndef FUTURE_SAFE_DELETE
#	define FUTURE_SAFE_DELETE( r ) if(r){delete(r);}
#	define FUTURE_SAFE_DELETE_ARRAY(p) if (p) {delete[](p);}
#	define FUTURE_SAFE_RELEASE( r ) if(r){(r)->Release();}
#endif

//! A custom check sum used to ensure memory is not corrupted
#ifndef FUTURE_CHECKSUM		
#	define FUTURE_CHECKSUM	0xF07012E9
#endif

//! Convert the argument into a string
#ifndef TOSTRING
#	define STRINGIFY(x)	#x
#	define TOSTRING(x)	STRINGIFY(x)
#endif


#endif
