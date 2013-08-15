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

#ifndef FUTURE_CORE_DEBUG_LOG_H
#define FUTURE_CORE_DEBUG_LOG_H

// Forward declares
class IFutureOStream;

/*!
 *	\brief		Enum describing the severness of a log message
 *
 *	\details 	Provide 6 different levels of log message severeness. The severeness of a
 *				message is set when calling FutureLog::Log. The message will be ignored if
 *				FutureLog::MinimumSeverness is greater than the provided severeness. By 
 *				Default, all messages except Verbose are logged during debug builds, messages
 *				greater than Warning are logged on profile builds, and only Error and Fatal
 *				messages are logged on release builds.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */
typedef enum FutureMessageSeverness
{
	FutureMessageSeverness_Verbose 	= 0,	//! Specifies a message that is essentially unneeded, useful for logging function calls and extra details
	FutureMessageSeverness_Info 	= 1,	//!	Specifies an informative message, useful for tracking important variables and extended debugging
	FutureMessageSeverness_Debug 	= 2,	//!	Specified a debug message, useful for logging information used to fix bugs and log weak warnings
	FutureMessageSeverness_Warning	= 3,	//! A general warning message, used to log a potential error or a situation that might cause problems, low memory, overflows, unexpected input
	FutureMessageSeverness_Error	= 4,	//! An error message that is not fatal. Used for normal asserts. Useful for logging events that will keep the game from running properly but will still allow the game to run and for logging potential developer error (invalid function params)
	FutureMessageSeverness_Fatal	= 5,	//! A fatal error message. This is reserved for game crashing issues and is used by AssertCrit.
} FutureMessageSeverness;

/*!
 *	\brief		Logs messages to a platform specific log
 *
 *	\details 	Logs messages of varying severness to a platform specific log. Logs are as follows:
 *				-Android	- Logcat; 
 *				-iOS		- Apple System Log; 
 *				-Mac		- Apple System Log; 
 *				-Linux 		- Standard Out; 
 *				-Windows 	- Standard Out; 
 *				Any of there default logs can be changed by providing a custom log function with SetLogFunction.
 *				The log can also be cleared or flushed to an output stream at any time.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		July 2013
 */
class FutureLog
{
	//!	Function Prototype for function called to handle logging a message
	typedef void (*FutureLogFunction)(u8 severness, const char * file, u32 line, const char * message);

	/*!	\brief	Sets the current FutureLogFunction 
	 *	\param[in] logFunction	The function to be called when a message needs to be logged
	 */
	static void SetLogFunction(FutureLogFunction logFunction);

	/*!	\brief	Logs a message with the provided severness, file, line, and message
	 *	\detail	This function will first take the provided argument list and combine them into
	 * 			a unifed string, assuming the first additional argument is a formatted string.
	 *			The file, line, and formatted string are then passed to the current
	 *			FutureLogFunction for processing.
	 *	\param[in]	severness	The severness of the message as defined by FutureMessageSeverness
	 *	\param[in]	file		The string name of the file where the message is coming from
	 *	\param[in]	line		The line number on which Log was called
	 *	\param[in]	...			A formated string to be logged followed by arguments for the message
	 */
	static void Log(FutureMessageSeverness severness, const char * file, u32 line, ...);

	//! \brief	Sets the minimum severness required to be logged. Anything less than this will be ignored
	static void	SetMinimumSeverness(FutureMessageSeverness severness);

	//! \brief	Clears all buffered log messages
	static void	ClearLog();

	/*! \brief	Sends all current buffered log messages to the provided stream.
	 *	\detail	Writes all currently buffered log messages the stream by calling
	 *			IFutureOStream::Write(const char *) with the log message followed
	 *			by '\n'.
	 *	\param	stream	The stream to write to. The stream must be open before passing it to this function
	 *	\param	clearLog	If this flag is true, ClearLog will be called after writing the log buffer to the stream
	 */
	static void	FlushToStream(IFutureOStream * stream, bool clearLog = true);

	/*! \brief	Sets the maximum number of log messages that be stored at any given time
	 *	\detail	The maximum number of log messaged controls the size of the log buffer.The default value for
	 *			Debug and Profile builds is 512 while the default for release builds is 256 to cut down as much as
	 *			possible on memory usage. If the program is spending a lot of time writing the log buffer to a file,
	 *			it might speed things up to expand the log buffer size. If the log buffer reaches provided maximum it
	 *			Will clear itself. If a valid ostream has been provided before the log is cleared, the buffer will be
	 *			flushed to the stream before being cleared. Also note that changing the buffer size will
	 *			clear the current buffer.
	 *	\param	logsInBuffer	The maximum number of log messages that can be stored in the current buffer.
	 *	\param	flushWhenFull	Sets the stream to write to when the log is full. The stream must be open when passed to this function
	 */
	static void	SetMaxLogsInBuffer(u32 logsInBuffer, IFutureOStream * flushWhenFull = NULL);
	//! \brief	Gets the current maximum number of logs that can be stored in the log buffer
	static u32	GetMaxLogsInBuffer();
	//! \brief	Gets the current number of log messages in the buffer
	static u32	LogsInBuffer();

	//! \brief	Gets the total number of logs made with the specified severness
	static u32 	GetCount(FutureMessageSeverness severness);
};

//! These macros provide easy access to the logging functions but automatically setting severeness, file, and line.
//!	The lower severness macros do nothing in release builds to prevent the program from building uneeded strings
#if FUTURE_DEBUG || FUTURE_PROFILE
#	define FUTURE_LOG_VERBOSE(...)	FutureLog::Log(FutureMessageSeverness_Verbose, __FILE__, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_INFO(...)		FutureLog::Log(FutureMessageSeverness_Info, __FILE__, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_DEBUG(...)	FutureLog::Log(FutureMessageSeverness_Debug, __FILE__, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_WARNING(...)	FutureLog::Log(FutureMessageSeverness_Warning, __FILE__, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_ERROR(...)	FutureLog::Log(FutureMessageSeverness_Error, __FILE__, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_FATAL(...)	FutureLog::Log(FutureMessageSeverness_Fatal, __FILE__, __LINE__, __VA_ARGS__);
#else
#	define FUTURE_LOG_VERBOSE(...)
#	define FUTURE_LOG_INFO(...)
#	define FUTURE_LOG_DEBUG(...)
#	define FUTURE_LOG_WARNING(...)
#	define FUTURE_LOG_ERROR(...)	FutureLog::Log(FutureMessageSeverness_Error, __FILE__, __LINE__, __VA_ARGS__);
#	define FUTURE_LOG_FATAL(...)	FutureLog::Log(FutureMessageSeverness_Fatal, __FILE__, __LINE__, __VA_ARGS__);
#endif

//! Shortcuts to the above macros
#ifndef LOG_V
#	define LOG_V	FUTURE_LOG_VERBOSE
#endif
#ifndef LOG_I
#	define LOG_I	FUTURE_LOG_INFO
#endif
#ifndef LOG_D
#	define LOG_D	FUTURE_LOG_DEBUG
#endif
#ifndef LOG_W
#	define LOG_W	FUTURE_LOG_WARNING
#endif
#ifndef LOG_E
#	define LOG_E	FUTURE_LOG_ERROR
#endif
#ifndef LOG_F
#	define LOG_F	FUTURE_LOG_FATAL
#endif

#endif
