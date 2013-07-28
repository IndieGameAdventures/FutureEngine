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
*	The main game system, this handles start up and shut down of the entire engine
*/

#include <future/core/debug/debug.h>
#include <future/core/system/window.h>
#include <future/core/system/application.h>

const char * FutureLanguageCodeReference[] =
{
	"zn",
	"es",
	"en",
	"hi",
	"ar",
	"pt",
	"be",
	"ru",
	"ja",
	"de",
	"id",
	"vi",
	"ko",
	"fr",
	"tr",
	"it",
	"hk",
	"th",
	"pl",
	"ro",
	"nl",
};


void FutureApplication::Initialize()
{
	FUTURE_ASSERT(m_systemController);
	m_systemController->Initialize();
}

void FutureApplication::Shutdown()
{
	FUTURE_ASSERT(m_systemController);
	m_systemController->Shutdown();
}


FutureSystemController * FutureApplication::GetSystemController()
{
	return m_systemController;
}


FutureApplication::FutureApplication()
{
	ms_instance = this;
	m_systemController = new FutureSystemController();
}

FutureApplication::~FutureApplication()
{
	delete m_systemController;
	m_systemController = NULL;
}
