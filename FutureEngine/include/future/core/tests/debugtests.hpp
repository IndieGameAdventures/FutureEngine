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
*	Contains Units tests for Debug functions
*/

#ifndef FUTURE_CORE_TESTS_DEBUG_H
#define FUTURE_CORE_TESTS_DEBUG_H

#include <future/core/debug/debug.h>

class FutureDebugTests
{
public:
	static void TestBreakPoint()
	{
		FUTURE_DEBUG_HALT();
	}

	static void TestAssert()
	{
		FUTURE_ASSERT(5 == 5);
		FUTURE_ASSERT_MSG(4 == 10, L"Success!");
	}

	static void TestAssertCrit()
	{
		FUTURE_ASSERT_CRIT_MSG(5 == 5, 1234, L"Failure :-(");
		FUTURE_ASSERT_CRIT(4 == 10, 1235);
	}

	static void TestLog()
	{
		FUTURE_LOG_VERBOSE(L"Verbose Logging");
		FUTURE_LOG_V(L"V Logging");
		FUTURE_LOG_INFO(L"INFO Logging");
		FUTURE_LOG_I(L"I Logging");
		FUTURE_LOG_DEBUG(L"Debug Logging");
		FUTURE_LOG_D(L"D Logging");
		FUTURE_LOG_WARNING(L"WARN Logging");
		FUTURE_LOG_W(L"W Logging");
		FUTURE_LOG_ERROR(L"ERROR Logging");
		FUTURE_LOG_E(L"E Logging");
	}
};
#endif