#include <future/core/debug/debug.h>
#include <stdarg.h>
#include <wchar.h>

// default assert to be used unless another function is specified
static void FutureAssertDefault(string file, u32 line, ...)
{
	va_list val;
	va_start(val, line);

	wchar_t buffer[2048];
	string message = va_arg(val, string);
	int count = vswprintf(buffer, FUTURE_ARRAY_LENGTH(buffer), message, val);
	if(count > FUTURE_ARRAY_LENGTH(buffer) || count < 0)
	{
		FUTURE_DEBUG_HALT();
	}

	va_end(val);

	futureLogFunction(FutureMessageSeverness::MESSAGE_ERROR, file, line, buffer);
	FUTURE_DEBUG_HALT();
}

static void FutureAssertCritDefault(string file, u32 line, s32 errorCode, ...)
{
	va_list val;
	va_start(val, errorCode);

	wchar_t buffer[2048];
	string message = va_arg(val, string);
	int count = vswprintf(buffer, FUTURE_ARRAY_LENGTH(buffer), message, val);
	if(count > FUTURE_ARRAY_LENGTH(buffer) || count < 0)
	{
		FUTURE_DEBUG_HALT();
	}

	va_end(val);

	futureLogFunction(FutureMessageSeverness::MESSAGE_ERROR, file, line, L"Critical Error #%i! %ls\n", errorCode, buffer);
	FUTURE_DEBUG_HALT();
}


FutureAssertFunction futureAssertFunction = FutureAssertDefault;
FutureAssertCritFunction futureAssertCritFunction = FutureAssertCritDefault;

void FutureSetAssertFunction(FutureAssertFunction assertFunction)
{
	FUTURE_ASSERT(assertFunction);
	futureAssertFunction = assertFunction;
}

void FutureSetAssertCritFunction(FutureAssertCritFunction assertCritFunction)
{
	FUTURE_ASSERT(assertCritFunction);
	futureAssertCritFunction = assertCritFunction;
}