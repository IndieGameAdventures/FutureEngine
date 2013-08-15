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

// debug.h includes assert.h
#include <future/core/debug/debug.h>

// Default assert to be used unless another function is specified
void FutureAssertDefault(const char * file, u32 line, const char * message))
{
	FutureLog::Log(FutureMessageSeverness_Error, file, line, message);
	FUTURE_DEBUG_HALT();
}

// Default critical assert to be used unless another function is specified
void FutureAssertCritDefault(const char * file, u32 line, s32 errorCode, const char * message))
{
	FutureLog::Log(FutureMessageSeverness_Fatal, file, line, "Critical Error [%i] - %s", errorCode, message);
	FUTURE_DEBUG_HALT();
}

FutureAssertFunction futureAssertFunction = FutureAssertDefault;
FutureAssertCritFunction futureAssertCritFunction = FutureAssertCritDefault;

// Normal Assert Function
void FutureAssert::Assert(const char * file, u32 line, ...)
{
	va_list val;
	va_start(val, line);

	char buffer[512];	// Create a buffer for the message
	const char * message = va_arg(val, const char *);	// Get the formatted string
	// Make sure we have a valid message before continuing
	if(message)
	{
		int count = vsprintf(buffer, FUTURE_ARRAY_LENGTH(buffer), message, val);
		if(count > FUTURE_ARRAY_LENGTH(buffer) || count < 0)
		{
			FUTURE_DEBUG_HALT();
		}
	}
	else
	{
		// If we didn't recieve a message use the default one
		strcpy(buffer, "Oh No! Something bad happened!");
	}
	va_end(val);

	// Call the assert function if one exists, or call the default one
	if(futureAssertFunction)
	{
		futureAssertFunction(file, line, buffer);
	}
	else
	{
		FutureAssertDefault(file, line, buffer);
	}
}

// Critical Assert function
void FutureAssert::AssertCrit(string file, u32 line, s32 errorCode, ...)
{
	va_list val;
	va_start(val, line);

	char buffer[512];	// Create a buffer for the message
	const char * message = va_arg(val, const char *);	// Get the formatted string
	// Make sure we have a valid message before continuing
	if(message)
	{
		int count = vsprintf(buffer, FUTURE_ARRAY_LENGTH(buffer), message, val);
		if(count > FUTURE_ARRAY_LENGTH(buffer) || count < 0)
		{
			FUTURE_DEBUG_HALT();
		}
	}
	else
	{
		// If we didn't recieve a message use the default one
		strcpy(buffer, "Oh No! Something really really bad happened!");
	}
	va_end(val);

	// Call the critical assert function if one exists, or call the default one
	if(futureAssertCritFunction)
	{
		futureAssertCritFunction(file, line, errorCode, buffer);
	}
	else
	{
		FutureAssertCritDefault(file, line, errorCode, buffer);
	}
}

// Get the Assert Function
FutureAssertFunction FutureAssert::GetAssertFunction()
{
	return futureAssertFunction;
}

// Get the Critical Assert Function
FutureAssertCritFunction FutureAssert::GetAssertFunction()
{
	return futureAssertCritFunction;
}

// Set the Assert Function
void FutureAssert::SetAssertFunction(FutureAssertFunction assertFunction)
{
	FUTURE_ASSERT(assertFunction);
	futureAssertFunction = assertFunction;
}

// Set the Critical Assert Function
void FutureAssert::SetAssertCritFunction(FutureAssertCritFunction assertCritFunction)
{
	FUTURE_ASSERT(assertCritFunction);
	futureAssertCritFunction = assertCritFunction;
}