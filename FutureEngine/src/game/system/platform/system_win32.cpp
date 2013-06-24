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
*	Entry point on windows machines
*/

#include <future/core/type/type.h>
#include <future/game/system/system.h>

#include <Windows.h>


int main(char ** args)
{
	FutureMain();
    return 0;//futureWinMSG.wParam;
}

MSG futureWinMSG;

FutureSystemMessage FutureGameSystemGetNextMessage()
{
	if(PeekMessage(&futureWinMSG, NULL, NULL, NULL, PM_REMOVE))
	{
	}
	return FutureSystemMessage::Message_None;
}

void FutureGameSystemProcessMessage()
{
	TranslateMessage( &futureWinMSG );
	DispatchMessage( &futureWinMSG );
}