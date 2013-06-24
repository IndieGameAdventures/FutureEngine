#include <future/core/debug/debug.h>
#include <stdarg.h>
#include <wchar.h>

#if FUTURE_PLATFORM_ANDROID
#	include <android/log.h>
#endif

// default assert to be used unless another function is specified
static void FutureLogFunctionDefault(u8 severness, string file, u32 line, string message, ...)
{
	va_list val;
	va_start(val, message);

	wchar_t buffer[2048];
	int count = vswprintf(buffer, FUTURE_ARRAY_LENGTH(buffer), message, val);
	if(count > FUTURE_ARRAY_LENGTH(buffer) || count < 0)
	{
		FUTURE_DEBUG_HALT();
	}

	va_end(val);

	wchar_t * se;
	switch(severness)
	{
	case FutureMessageSeverness::MESSAGE_VERBOSE:
		se = L"VERBOSE";
		break;
	case FutureMessageSeverness::MESSAGE_INFO:
		se = L"INFO";
		break;
	case FutureMessageSeverness::MESSAGE_DEBUG:
		se = L"DEBUG";
		break;
	case FutureMessageSeverness::MESSAGE_WARNING:
		se = L"WARNING";
		break;
	case FutureMessageSeverness::MESSAGE_ERROR:
		se = L"ERROR";
		break;
	}

	file = wcsrchr(file, '\\' );
	file = (string)((u32)file + sizeof(wchar_t));

#if FUTURE_PLATFORM_ANDROID
	char androidBuffer[2048];
	char androidFile[256];
	count = sprintf(androidBuffer, FUTURE_ARRAY_LENGTH(androidBuffer), "%ls: [%ls:%d] %ls", se, file, line, buffer);
	if(count > FUTURE_ARRAY_LENGTH(androidBuffer) || count < 0)
	{
		FUTURE_DEBUG_HALT();
	}
	count = sprintf(androidFile, FUTURE_ARRAY_LENGTH(androidFile), "%ls", file);
	if(count > FUTURE_ARRAY_LENGTH(androidFile) || count < 0)
	{
		FUTURE_DEBUG_HALT();
	}
	switch(severness)
	{
	case FutureMessageSeverness::MESSAGE_VERBOSE:
		__android_log_print(ANDROID_LOG_VERBOSE, androidFile, androidBuffer);
		break;
	case FutureMessageSeverness::MESSAGE_INFO:
		__android_log_print(ANDROID_LOG_INFO, androidFile, androidBuffer);
		break;
	case FutureMessageSeverness::MESSAGE_DEBUG:
		__android_log_print(ANDROID_LOG_DEBUG, androidFile, androidBuffer);
		break;
	case FutureMessageSeverness::MESSAGE_WARNING:
		__android_log_print(ANDROID_LOG_WARNING, androidFile, androidBuffer);
		break;
	case FutureMessageSeverness::MESSAGE_ERROR:
		__android_log_print(ANDROID_LOG_ERROR, androidFile, androidBuffer);
		break;
	}
#else
	wprintf_s(L"%ls: [%ls:%d] %ls\n", se, file, line, buffer);
#endif
}


FutureLogFunction futureLogFunction = FutureLogFunctionDefault;

void FutureSetLogFunction(FutureLogFunction logFunction)
{
	FUTURE_ASSERT(logFunction);
	futureLogFunction = logFunction;
}
