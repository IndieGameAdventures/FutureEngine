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

#ifndef FUTURE_CORE_LANGUAGE_H
#define FUTURE_CORE_LANGUAGE_H

#include <future/core/type/platform.h>

/*!
 *	\brief		A list of possible languages supported by Future Engine
 *
 *	\details 	Used almost exclusively by FutureResourceManager and FutureApplication to determine
 *				what localized version of an asset to load. Languages are listed in order of total
 *				native speaker. Use the resource manager tool to assign localized assets
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		July 2013
 */
enum FutureLanguage
{
	FutureLanguage_Default,		//! This will be the language the original assets were created in, can be set in the tools

	FutureLanguage_Mandarin,
	FutureLanguage_Spanish,
	FutureLanguage_English,
	FutureLanguage_Russian,
	FutureLanguage_Japanese,
	FutureLanguage_German,
	FutureLanguage_French,
	FutureLanguage_Cantonese,
	FutureLanguage_Hindi,
	FutureLanguage_Arabic,
	FutureLanguage_Portuguese,
	FutureLanguage_Bengali,
	FutureLanguage_Indonesian,
	FutureLanguage_Vietnamese,
	FutureLanguage_Korean,
	FutureLanguage_Turkish,
	FutureLanguage_Italian,
	FutureLanguage_Thai,
	FutureLanguage_Polish,
	FutureLanguage_Romanian,
	FutureLanguage_Dutch,

	FutureLanguage_Max,
};

#endif
