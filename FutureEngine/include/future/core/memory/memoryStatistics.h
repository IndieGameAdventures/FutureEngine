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
*	FutureMemoryStatistics contains useful statistics on memory
*	
*/

#ifndef FUTURE_CORE_MEMORY_STATISTICS_H
#define FUTURE_CORE_MEMORY_STATISTICS_H

#include <future/core/type/type.h>

struct FutureMemoryStatistics
{
public:
		u32 		m_currentBytes;
		u32			m_currentAllocations;
		u32			m_totalBytes;
		u32			m_totalAllocations;
		f32			m_totalTimeForAllocations;

		u32			m_averageAllocationSize;
		f32			m_averageTimeForAllocation;
};
	

#endif