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

#ifndef FUTURE_CORE_TYPE_PLATFORM_H
#define FUTURE_CORE_TYPE_PLATFORM_H

/*! \file 	platform.h
 *	\brief		Contains a list of platform and device defines.
 *
 *	\details 	Contains a set of enums and defines that can be used to determine
 *				what platform and device FutureEngine is running on and is being
 *				compiled for. This file should be included by every file used by
 *				Future Engine.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */


/*! \brief		Enumeration of all platforms supported by Future Engine
 *
 *	\details 	These platforms are the only platforms supported by Future Engine.
 *				Some platforms are actually child-platforms under a larger platform,
 *				For example, the platform is FuturePlatform_WindowsMetro then
 *				FuturePlatform_Windows must also be defined as Metro is a
 *				child of windows. A parent platform cannot be declared on its
 *				own but must have a child declared to go with it.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		July 2013
 */
typedef enum FuturePlatform
{
	FuturePlatform_Windows			= 1,	//! Windows 7 and Windows 8 parent platform
	FuturePlatform_WindowsDesktop	= 2,	//! Windows 7 and Windows 8 Desktop application, child of Windows
	FuturePlatform_WindowsMetro		= 3,	//! Windows 8 Metro Application and Windows 8 Tablet App, child of Windows
	FuturePlatform_WindowsPhone		= 4,	//! Windows 8 Phone App, child of Windows
	FuturePlatform_NativeClient		= 5,	//! Google Native Client App (Chrome App)
	FuturePlatform_Linux			= 6,	//! Linux/Unix/Ubuntu Desktop Application and any variation thereof
	FuturePlatform_Android			= 7,	//! Android OS parent, based of off linux but not a child of it
	FuturePlatform_AndroidPhone		= 8,	//! Android Phone App, child of Android
	FuturePlatform_AndroidTablet	= 9,	//! Android Tablet App, child of Android
	FuturePlatform_Ouya				= 10,	//! Ouya Gaming Platform, child of Android
	FuturePlatform_Shield			= 11,	//! nVidia Shield Gaming Platform, child of Android
	FuturePlatform_OSX				= 12,	//! Apple Macintosh Desktop Application
	FuturePlatform_IOS				= 13,	//! Apple Mobile Device parent
	FuturePlatform_IPhone			= 14,	//! Apple IPhone App, child of IOS
	FuturePlatform_IPad				= 15,	//! Apple IPad/IPad Mini App, child of IOS

	// These platforms would be nice to add in the future but are currently not supported
	// They are listed here for future compatibility.
	FuturePlatform_Flash			= 16,	//! Unsupported! Adobe Flash Program
	FuturePlatform_PS3				= 17,	//! Unsupported! Playstation 3 Game
	FuturePlatform_PS4				= 18,	//! Unsupported! Playstation 4 Game
	FuturePlatform_XBox360			= 19,	//! Unsupported! XBox 360 Game
	FuturePlatform_XBoxOne			= 20,	//! Unsupported! XBox One Game
	FuturePlatform_PSVita			= 21,	//! Unsupported! Playstation Vita Game
	FuturePlatform_SteamBox			= 22,	//! Unsupported! Steam Box Game
} FuturePlatform;


/*! \brief		Enumeration of potential device types
 *
 *	\details 	These device types define a great deal about how the engine will work
 *				and how it should handle certain things. For example, a desktop application
 *				will have the added complexity of changing screen sizes and changing display
 *				adapters while running. A Mobile Phone App will not have to deal with this,
 *				although a phone will have to deal with different screen sizes at start up
 *				whereas a console application will not have to.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		July 2013
 */
typedef enum FutureDevice
{
	FutureDevice_Desktop	= 1,	//! Desktop application - Windows, Mac, Linux
									//! Usually the most powerful platform type but also has the widest
									//! range of possible capabilities. Keyboard and mouse
	FutureDevice_Phone		= 2,	//! A Phone App - Windows Phone, Android Phone, IPhone
									//! Generally the least powerful platform type with only touch and small screen
	FutureDevice_Tablet		= 3,	//! A Tablet App - Windows Metro, Android Tablet, IPad, 
									//! A mix between Phone and Desktop. Larger screen, touch, can have keyboard and mouse
	FutureDevice_Console	= 4,	//! Game Consoles - Ouya, Shield, PS3, PS4, PSVita, XBox360, XBoxOne, SteamBox
									//! Every one is exactly the same making it easier to develop for but smaller demographic
	FutureDevice_Web		= 5,	//! Web Application - NativeClient, Flash
									//! Least power but avaliable to everyone with internet, Facebook

} FuturePlatformType;


/*! \brief		Enumeration of endian types
 *
 *	\details 	Future Engine expects file to be read in in little endian format as most desktops use that format and 
 *				the tools will save data in the format. But Some platforms that use big endian and data needs to switch
 *				endianness before it can be used properly.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		July 2013
 */
typedef enum FutureEndian
{
	FutureEndian_Big			= 1,	//! We are on a little endian platform
	FutureEndian_Little			= 2,	//! We are on a big endian platform
} FutureEndian;

//! This is a list of preprocessor macro defines of the above enums. See those enums for info on each macro
//! They are all set to 0 for now, the current platform will be defined to 1 for easy preprocessor checking
#define FUTURE_PLATFORM_WINDOWS			0
#define FUTURE_PLATFORM_WINDOWS_DESKTOP	0
#define FUTURE_PLATFORM_WINDOWS_METRO	0
#define FUTURE_PLATFORM_WINDOWS_PHONE	0
#define FUTURE_PLATFORM_NATIVE_CLIENT	0
#define FUTURE_PLATFORM_LINUX			0
#define FUTURE_PLATFORM_ANDROID			0
#define FUTURE_PLATFORM_ANDROID_PHONE	0
#define FUTURE_PLATFORM_ANDROID_TABLET	0
#define FUTURE_PLATFORM_ANDROID_OUYA	0
#define FUTURE_PLATFORM_ANDROID_SHIELD	0
#define FUTURE_PLATFORM_OSX				0
#define FUTURE_PLATFORM_IOS				0
#define FUTURE_PLATFORM_IPHONE			0
#define FUTURE_PLATFORM_IPAD			0

//!	Unsupported platforms!!
#define FUTURE_PLATFORM_FLASH			0
#define FUTURE_PLATFORM_PS3				0
#define FUTURE_PLATFORM_PS4				0
#define FUTURE_PLATFORM_XBOX360			0
#define FUTURE_PLATFORM_XBOXONE			0
#define FUTURE_PLATFORM_PSVITA			0
#define FUTURE_PLATFORM_STEAMBOX		0


//! Device Types
#define FUTURE_DEVICE_DESKTOP			0
#define FUTURE_DEVICE_PHONE				0
#define FUTURE_DEVICE_TABLET			0
#define FUTURE_DEVICE_CONSOLE			0
#define FUTURE_DEVICE_WEB				0


//! Predefine the most likely endian, big endian platforms will redefine these
#define FUTURE_ENDIAN_LITTLE 1
#define FUTURE_ENDIAN_BIG	0

#if defined(_ANDROID) || defined(_OUYA) || defined(__ANDROID__) || defined(_SHIELD)
#	undef  FUTURE_PLATFORM_ANDROID
#	define FUTURE_PLATFORM_ANDROID 1
#	if defined(_OUYA)
#		undef  FUTURE_PLATFORM_OUYA
#		define FUTURE_PLATFORM_OUYA 1
#		undef  FUTURE_DEVICE_CONSOLE
#		define FUTURE_DEVICE_CONSOLE 1
#	endif
#	if defined(_SHIELD)
#		undef  FUTURE_PLATFORM_SHIELD
#		define FUTURE_PLATFORM_SHIELD 1
#		undef  FUTURE_DEVICE_CONSOLE
#		define FUTURE_DEVICE_CONSOLE 1
#	elif defined(_PHONE)
#		undef  FUTURE_PLATFORM_ANDROID_PHONE
#		define FUTURE_PLATFORM_ANDROID_PHONE 1
#		undef  FUTURE_DEVICE_PHONE
#		define FUTURE_DEVICE_PHONE 1
#	elif defined(_TABLET)
#		undef  FUTURE_PLATFORM_ANDROID_TABLET
#		define FUTURE_PLATFORM_ANDROID_TABLET 1
#		undef  FUTURE_DEVICE_TABLET
#		define FUTURE_DEVICE_TABLET 1
#	else
#		error Android must have a child platform defined
#	endif
#	define FUTURE_USES_PTHREAD
#elif defined(_LINUX)
#	undef  FUTURE_PLATFORM_LINUX
#	define FUTURE_PLATFORM_LINUX 1
#	undef  FUTURE_DEVICE_DESKTOP
#	define FUTURE_DEVICE_DESKTOP 1
#	define FUTURE_USES_PTHREAD
#elif defined(__APPLE__) || defined(Macintosh) || defined(macintosh)
#	include "TargetConditionals.h"
#	if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#		undef  FUTURE_PLATFORM_IOS
#		define FUTURE_PLATFORM_IOS 1
#		if defined(_PHONE)
#			undef  FUTURE_PLATFORM_IPHONE
#			define FUTURE_PLATFORM_IPHONE 1
#			undef  FUTURE_DEVICE_PHONE
#			define FUTURE_DEVICE_PHONE 1
#		elif defined(_TABLET)
#			undef  FUTURE_PLATFORM_IPAD
#			define FUTURE_PLATFORM_IPAD 1
#			undef  FUTURE_DEVICE_TABLET
#			define FUTURE_DEVICE_TABLET 1
#		else
#			error IOS must have a child platform defined
#		endif
#		if TARGET_IPHONE_SIMULATOR
#			define FUTURE_IOS_SIMULATOR
#		endif
#	elif TARGET_OS_MAC
#		undef  FUTURE_PLATFORM_MAC
#		define FUTURE_PLATFORM_MAC 1
#		undef  FUTURE_DEVICE_DESKTOP
#		define FUTURE_DEVICE_DESKTOP 1
#	else
#		error Found an unsupported Apple product!
#	endif
#	define FUTURE_USES_PTHREAD
#elif defined(_WIN32) || defined(_WINDOWS)
#	undef  FUTURE_PLATFORM_WINDOWS
#	define FUTURE_PLATFORM_WINDOWS 1
#	if defined(_WINDOWS_METRO) || defined(_TABLET)
#		undef  FUTURE_PLATFORM_WINDOWS_METRO
#		define FUTURE_PLATFORM_WINDOWS_METRO 1
#		undef  FUTURE_DEVICE_TABLET
#		define FUTURE_DEVICE_TABLET 1
#	elif defined(_PHONE)
#		undef  FUTURE_PLATFORM_WINDOWS_PHONE
#		define FUTURE_PLATFORM_WINDOWS_PHONE 1
#		undef  FUTURE_DEVICE_PHONE
#		define FUTURE_DEVICE_PHONE 1
#	else
#		undef  FUTURE_PLATFORM_WINDOWS_DESKTOP
#		define FUTURE_PLATFORM_WINDOWS_DESKTOP 1
#		undef  FUTURE_DEVICE_DESKTOP
#		define FUTURE_DEVICE_DESKTOP 1
#	endif
#elif defined(_NACL) || defined(_CHROME)
#	undef  FUTURE_PLATFORM_NATIVE_CLIENT
#	define FUTURE_PLATFORM_NATIVE_CLIENT 1
#	undef  FUTURE_DEVICE_WEB
#	define FUTURE_DEVICE_WEB 1
#	define FUTURE_ENABLE_MULTITHREADED 0 // Google Native client has no thread support
#else
#	error Failed to define a supported platform!
#endif



//! Processor defines.

//! Determine if we are compiling for a 64 or 32 bit OS
#if defined(_WIN64) || defined(_M_X64) || defined(_LP64)
#	define FUTURE_X64	//! This is a 64 bit OS
#else
#	define FUTURE_X32	//! This is a 32 bit OS
#endif

// Determine if we should use an SIMD instructions and if so, which ones.
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
#		define FUTURE_USES_NEON
#   endif
#elif defined(__PPC) || defined(__PPC__) || defined(_ARCH_PPC) || defined(__POWERPC__)
#	if defined(__ALTIVEC__) || defined(__VEC__)
#		define FUTURE_USES_ALTIVEC
#	endif
#endif

#endif
