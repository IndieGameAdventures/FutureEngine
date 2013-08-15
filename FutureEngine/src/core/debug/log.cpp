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


#include <future/core/type/type.h>
#include <future/core/debug/debug.h>
#include <future/core/util/stream.h>
#include <future/core/util/container/array.h>
#include <future/core/thread/criticalsection/criticalsection.h>

#if FUTURE_PLATFORM_ANDROID
#	include <android/log.h>
#endif

#if FUTURE_PLATFORM_IPHONE || FUTURE_PLATFORM_MAC || FUTURE_PLATFORM_LINUX
#	include <syslog.h>
 	bool isLogOpen = false;
#endif

// Default log function to be used unless another function is specified
void FutureLogFunctionDefault(FutureMessageSeverness severness, const char * file, u32 line, const char * message)
{
	const char * se;
	switch(severness)
	{
	case FutureMessageSeverness_Verbose:
		se = "VERBOSE";
		break;
	case FutureMessageSeverness_Info:
		se = "INFO";
		break;
	case FutureMessageSeverness_Debug:
		se = "DEBUG";
		break;
	case FutureMessageSeverness_Warning:
		se = "WARNING";
		break;
	case FutureMessageSeverness_Error:
		se = "ERROR";
		break;
	case FutureMessageSeverness_Fatal:
		se = "FATAL";
		break;
	}

#if FUTURE_PLATFORM_ANDROID
	switch(severness)
	{
	case FutureMessageSeverness::MESSAGE_VERBOSE:
		__android_log_print(ANDROID_LOG_VERBOSE, file, "%s: [%s:%d] '%s'", se, file, line, message);
		break;
	case FutureMessageSeverness::MESSAGE_INFO:
		__android_log_print(ANDROID_LOG_INFO, file, "%s: [%s:%d] '%s'", se, file, line, message);
		break;
	case FutureMessageSeverness::MESSAGE_DEBUG:
		__android_log_print(ANDROID_LOG_DEBUG, file, "%s: [%s:%d] '%s'", se, file, line, message);
		break;
	case FutureMessageSeverness::MESSAGE_WARNING:
		__android_log_print(ANDROID_LOG_WARN, file, "%s: [%s:%d] '%s'", se, file, line, message);
		break;
	case FutureMessageSeverness::MESSAGE_ERROR:
		__android_log_print(ANDROID_LOG_ERROR, file, "%s: [%s:%d] '%s'", se, file, line, message);
		break;
	}
#elif FUTURE_PLATFORM_MAC || FUTURE_PLATFORM_IPHONE || FUTURE_PLATFORM_LINUX
	if(!isLogOpen)
	{
		isLogOpen = true;
		openlog("FutureLog", (LOG_CONS|LOG_PERROR), LOG_DEAMON);
	}
	syslog("%s: [%s:%d] '%s'", se, file, line, message);
#else
	printf("%s: [%s:%d] '%s'\n", se, file, line, message);
#endif
}

void FlushToStreamNoLock(IFutureOStream * stream);

FutureLogFunction futureLogFunction = FutureLogFunctionDefault;

#if FUTURE_DEBUG
FutureMessageSeverness minimumSeverness = FutureMessageSeverness_Info;
#elif FUTURE_PROFILE
FutureMessageSeverness minimumSeverness = FutureMessageSeverness_Warning;
#else
FutureMessageSeverness minimumSeverness = FutureMessageSeverness_Error;
#endif

struct LogMessage
{
	FutureMessageSeverness 	m_severness;
	const char				m_file[64];
	u32						m_line;
	const char				m_message[512];
};
FutureArray<LogMessage>	m_messages = FutureArray<LogMessage>();
FutureCriticalSection	m_criticalSection = FutureCriticalSection();
u32						m_maxBufferSize = 512;
IFutureOStream *		m_stream = NULL;
u32						m_logCount[FutureMessageSeverness_Fatal + 1] = {0, 0, 0, 0, 0, 0};

// Sets the log function to use
void FutureLog::SetLogFunction(FutureLogFunction logFunction)
{
	FUTURE_ASSERT(logFunction);
	futureLogFunction = logFunction;
}

// Logs a message
void FutureLog::Log(FutureMessageSeverness severness, const char * file, u32 line, ...)
{
	m_logCount[severness]++;

	if(severness < minimumSeverness)
	{
		return;
	}

	va_list val;
	va_start(val, line);

	char buffer[512];
	const char * message = va_arg(val, const char *);
	int count = vsprintf(buffer, message, val);
	if(count > FUTURE_ARRAY_LENGTH(buffer) || count < 0)
	{
		// We can't assert here as we might be in an assert function
		FUTURE_DEBUG_HALT();
	}

	va_end(val);


	// Remove the path from the file name
	file = strtchr(file, '\\' );
	file = (const char *)((size_t)file + sizeof(char));

	LogMessage m;
	m.m_severness = severness;
	strcpy(m.m_file, file);
	m.m_line = line;
	strcpy(m.m_message, buffer);

	m_criticalSection.Lock();
	if(m_messages.Size() >= maxBufferSize)
	{
		if(m_stream)
		{
			FlushToStreamNoLock(m_stream);
		}
		m_message.Clear();
	}
	m_message.Add(m);
	m_criticalSection.Unlock();

	futureLogFunction(severness, file, line, buffer);
}

// Sets the minimum shown severness
void FutureLog::SetMinimumSeverness(FutureMessageSeverness severness)
{
	minimumSeverness = severness;
}

// Clear the messages array
void FutureLog::ClearLog()
{
	m_criticalSection.Lock();
	m_messages.Clear();
	m_criticalSection.Unlock();
}
// Lock, write, clear, Unlock
void FutureLog::FlushToStream(IFutureOStream * stream, bool clearLog = true)
{
	m_criticalSection.Lock();
	FlushToStreamNoLock(stream);
	if(clearLog)
	{
		m_messages.Clear();
	}
	m_criticalSection.Unlock();
}

// Lock, write, clear, update sizes, unlock
void FutureLog::SetMaxLogsInBuffer(u32 logsInBuffer, IFutureOStream * flushWhenFull = NULL)
{
	m_criticalSection.Lock();
	if(m_stream)
	{
		FlushToStreamNoLock(m_stream);
	}
	m_messages.Clear();
	m_maxBufferSize = logsInBuffer;
	m_stream = flushWhenFull;
	m_criticalSection.Unlock();

}
u32	FutureLog::GetMaxLogsInBuffer()
{
	return m_maxBufferSize;
}
u32	FutureLog::LogsInBuffer()
{
	return m_messages.Size();
}
u32 FutureLof::GetCount(FutureMessageSeverness severness)
{
	return m_logCount[severness];
}

// Writes the message log to the stream.
void FlushToStreamNoLock(IFutureOStream * stream)
{
	FUTURE_ASSERT(steam && steam->IsOpen())
	char buffer[1024];
	for(u32 i = 0; i < m_messages.Size(); ++i)
	{	
		const char * se;
		switch(m_messages[i].m_severness)
		{
		case FutureMessageSeverness_Verbose:
			se = "VERBOSE";
			break;
		case FutureMessageSeverness_Info:
			se = "INFO";
			break;
		case FutureMessageSeverness_Debug:
			se = "DEBUG";
			break;
		case FutureMessageSeverness_Warning:
			se = "WARNING";
			break;
		case FutureMessageSeverness_Error:
			se = "ERROR";
			break;
		case FutureMessageSeverness_Fatal:
			se = "FATAL";
			break;
		}
		sprintf(buffer, "%s: [%s:%d] '%s'\n", se, m_messages[i].m_file, m_messages[i].m_line, m_messages[i].m_message);
		stream->Write((void*)buffer, strlen(buffer));
	}
}
