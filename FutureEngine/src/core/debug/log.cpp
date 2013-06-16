#include <future/core/debug/debug.h>
#include <stdarg.h>
#include <wchar.h>


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

	wprintf_s(L"%ls: [%ls:%d] %ls\n", se, file, line, buffer);
}


FutureLogFunction futureLogFunction = FutureLogFunctionDefault;

void FutureSetLogFunction(FutureLogFunction logFunction)
{
	FUTURE_ASSERT(logFunction);
	futureLogFunction = logFunction;
}
