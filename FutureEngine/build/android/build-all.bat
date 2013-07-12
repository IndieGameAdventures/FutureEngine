::@echo off

if not defined NDK_ROOT (
	echo Please define NDK_ROOT to your local copy of the Android NDK
	goto FULLEND
)

if "%1"=="clean" (
	call ./FutureCore/clean.bat %2
	call ./FutureGame/clean.bat %2
	goto FULLEND
)
if "%2"=="clean" (
	call ./FutureCore/clean.bat %1
	call ./FutureGame/clean.bat %1
	goto FULLEND
)

if "%1"=="rebuild" (
	call ./FutureCore/clean.bat %2
	call ./FutureCore/build.bat %2

	call ./FutureGame/clean.bat %2
	call ./FutureGame/build.bat %2
	goto FULLEND
)
if "%2"=="rebuild" (
	call ./FutureCore/clean.bat %1
	call ./FutureCore/build.bat %1

	call ./FutureGame/clean.bat %1
	call ./FutureGame/build.bat %1
	goto FULLEND
)

echo Building FutureCore...
call .\FutureCore\build.bat %1

echo Building FutureGame...
call .\FutureGame\build.bat %1

:FULLEND
echo finished