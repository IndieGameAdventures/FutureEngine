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

/*	A singleton object. An object that extends this cal only exist once
*	in a program. Trying to create a second one will cause an error.
*
*	Singletons are can be created by manually calling CreateInstance or
*	automatically the first time GetInstance is called. Singletons must
*	be manually deleted when finished with them by calling DestroyInstance
*/

#ifndef FUTURE_CORE_OBJECTS_SINGLETON_H
#define FUTURE_CORE_OBJECTS_SINGLETON_H

#include <future/core/debug/debug.h>
#include <future/core/object/pointer/smartpointer.h>

template<class CLASS>
class FutureSingleton
{
protected:
	FutureSingleton()
	{
		FUTURE_ASSERT(ms_instance == NULL);
		ms_instance = this;
	}
	~FutureSingleton()
	{
		ms_instance = NULL;
	}
	static SPtr<CLASS> ms_instance;

public:
	inline static SPtr<CLASS> GetInstance()
	{
		if(ms_instance == NULL)
		{
			ms_instance = new CLASS();
		}
		return ms_instance;
	}

	inline static void CreateInstance()
	{
		FUTURE_ASSERT(ms_instance == NULL);
		ms_instance = new CLASS();
	}

	inline static void DestroyInstance()
	{
		FUTURE_ASSERT(ms_instance != NULL);
		ms_instance = NULL;
	}
};

#endif
