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
*	Android entry point and core system
*/

#include <future/core/type/type.h>
#include <future/game/system/system.h>

#include <android_native_app_glue.h>

struct android_app* FutureAndroidApp;

int android_main(struct android_app* app)
{
    // Make sure glue isn't stripped.
    app_dummy();

	FutureMain();
    return 0;
}


FutureSystemMessage FutureGameSystemGetNextMessage()
{
	return FutureSystemMessage::Message_None;
}

void FutureGameSystemProcessMessage()
{
}