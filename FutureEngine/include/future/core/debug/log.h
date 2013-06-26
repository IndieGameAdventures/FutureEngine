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
*	A logger class that prints out messages of varying severness.
*/

#ifndef FUTURE_CORE_DEBUG_LOG_H
#define FUTURE_CORE_DEBUG_LOG_H

class FutureMessageSeverness
{
public:
	static const u8 MESSAGE_VERBOSE = 0;
	static const u8 MESSAGE_INFO = 1;
	static const u8 MESSAGE_DEBUG = 2;
	static const u8 MESSAGE_WARNING = 3;
	static const u8 MESSAGE_ERROR = 4;
};

typedef void (*FutureLogFunction)(u8 severness, string file, u32 line, ...);
extern FutureLogFunction futureLogFunction;

// Set the global logging handler
void FutureSetLogFunction(FutureLogFunction logFunction);

#if FUTURE_DEBUG || FUTURE_PROFILE

#	define FUTURE_LOG_VERBOSE(...)	futureLogFunction(FutureMessageSeverness::MESSAGE_VERBOSE, WFILE, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_INFO(...)	futureLogFunction(FutureMessageSeverness::MESSAGE_INFO, WFILE, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_DEBUG(...)	futureLogFunction(FutureMessageSeverness::MESSAGE_DEBUG, WFILE, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_WARNING(...)	futureLogFunction(FutureMessageSeverness::MESSAGE_WARNING, WFILE, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_ERROR(...)	futureLogFunction(FutureMessageSeverness::MESSAGE_ERROR, WFILE, __LINE__, __VA_ARGS__);

#else

#	define FUTURE_LOG_VERBOSE(...)
#	define FUTURE_LOG_INFO(...)
#	define FUTURE_LOG_DEBUG(...)
#	define FUTURE_LOG_WARNING(...)
#	define FUTURE_LOG_ERROR(...)	futureLogFunction(FutureMessageSeverness::MESSAGE_ERROR, WFILE, __LINE__, __VA_ARGS__);

#endif

#define FUTURE_LOG_V	FUTURE_LOG_VERBOSE
#define FUTURE_LOG_I	FUTURE_LOG_INFO
#define FUTURE_LOG_D	FUTURE_LOG_DEBUG
#define FUTURE_LOG_W	FUTURE_LOG_WARNING
#define FUTURE_LOG_E	FUTURE_LOG_ERROR

#endif
