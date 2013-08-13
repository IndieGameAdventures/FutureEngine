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


#ifndef FUTURE_CORE_DEBUG_ASSERT_H
#define FUTURE_CORE_DEBUG_ASSERT_H

#include <future/core/type/type.h>

/*!
 *	\brief		Handles program asertions by calling FutureAssertFuncion or FutureAssertCritFunction
 *
 *	\details 	Class responsible for handling program assertions. FutureAssert contains two different
 *				levels of asserts, normal and critical. Normal assertions will only fire in debug and
 *				profile builds while critical assertions will also fire in release builds. Each program
 *				can define it's own assertion functions by SetAssertFunction and SetAssertCritFunction.
 *				This can be very useful and allow for sending critical error reports from client machines
 *				and providing a custom error handler to improve debugging.  FutureAssert contains default
 *				assert functions that simply send error to FutureLog and call FUTURE_DEBUG_HALT.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */
class FutureAssert
{
public:
	//!	Function Prototype for for function called to handle normal asserts
	typedef void (*FutureAssertFunction)(const char * file, u32 line, const char * message);
	//!	Function Prototype for for function called to handle normal asserts
	typedef void (*FutureAssertCritFunction)(const char * file, u32 line, s32 errorCode, const char * message);

	/*!	\brief	Fires an assertion from the provided file and line with the provided message
	 *	\detail	This function will first take the provided argument list and combine them into
	 * 			a unifed string, assuming the first additional argument is a formatted string.
	 *			This function can be called without any additional arguments.
	 *			The file, line, and formatted string are then passed to the current
	 *			FutureAssertFunction for processing. The developer may assume that this function
	 *			will never return.
	 *	\param[in]	file	The string name of the file where the assertion occured
	 *	\param[in]	line	The line number on which the assertion occured
	 *	\param[in]	...		A formated string followed by arguments for the string
	 */
	static Assert(const char * file, u32 line, ...);

	/*!	\brief	Fires a critical assertion from the provided file and line with the provided message
	 *	\detail	Functionals almost identically to Assert but operators properly in release builds.
	 *			Formats the variable argument list into a string then called the current
	 *			FutureAssertCritFunction. This function should never return
	 *	\param[in]	file	The string name of the file where the assertion occured
	 *	\param[in]	line	The line number on which the assertion occured
	 *	\param[in]	errno	The error number of the assertion. Makes debugging client machines much easier
	 *	\param[in]	...		A formated string followed by arguments for the string
	 */
	static AssertCrit(const char * file, u32 line, s32 errorCode, ...);

	/*!	\brief	Gets the currently set FutureAssertFunction
	 *	\return	The current FutureAssertFunction
	 */
 	static FutureAssertFunction GetAssertFunction();

	/*!	\brief	Gets the currently set FutureAssertCritFunction
	 *	\return	The current FutureAssertCritFunction
	 */
	static FutureAssertCritFunction GetAssertCritFunction();

	/*!	\brief	Sets the current FutureAssertFunction 
	 *	\param[in] assertFunction	The function to be called when an assert fires
	 */
	static void SetAssertFunction(FutureAssertFunction assertFunction);

	/*!	\brief	Sets the current FutureAssertCritFunction 
	 *	\param[in] assertCritFunction	The function to be called when a critical assert fires
	 */
	static void SetAssertCritFunction(FutureAssertCritFunction assertCritFunction);
};

//! \remark	If we are in debug or profile, make sure that the assert is called, in release the macro does nothing
#if FUTURE_DEBUG || FUTURE_PROFILE
	//!	If the provided check is false, this will fire an assert and provide the proper file and line, using the string value of the input as the message
#	define FUTURE_ASSERT(check)				if(!(check)){ FutureAssert::Assert(__FILE__, __LINE__, TOSTRING(check)); }
	//!	If the provided check is false, this will fire an assert and provide the proper file, line, and argument list
#	define FUTURE_ASSERT_MSG(check, ...)	if(!(check)){ FutureAssert::Assert(__FILE__, __LINE__, __VA_ARGS__); }
#else
	//!	In release builds, this function does nothing
#	define FUTURE_ASSERT(check)
#	define FUTURE_ASSERT_MSG(check, ...)
#endif

//!	If the provided check is false, this will fire a critical assert and provide the proper file and line, using the string value of the input as the message
#define FUTURE_ASSERT_CRIT(check, errorCode)			if(!(check)) { FutureAssert::AssertCrit(__FILE__, __LINE__, errorCode, TOSTRING(check)); }
//!	If the provided check is false, this will fire a critical assert and provide the proper file, line, and argument list
#define FUTURE_ASSERT_CRIT_MSG(check, errorCode, ...)	if(!(check)) { FutureAssert::AssertCrit(__FILE__, __LINE__, errorCode, __VA_ARGS__); }

#endif
