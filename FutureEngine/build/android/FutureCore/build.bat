@echo off

if not defined NDK_ROOT (
	echo Please define NDK_ROOT to your local copy of the Android NDK
	goto EOF
)

chdir .

if "%1"=="debug" (
	echo Building Debug FutureCore...
	%NDK_ROOT%ndk-build.cmd NDK_PROJECT_PATH=. NDK_APP_OUT=.\..\..\bin\android\debug
)
if "%1"=="profile" (
	echo Building Profile FutureCore...
	%NDK_ROOT%ndk-build.cmd NDK_PROJECT_PATH=. NDK_APP_OUT=.\..\..\bin\android\profile
)
if "%1"=="release" (
	echo Building Profile FutureCore...
	%NDK_ROOT%ndk-build.cmd NDK_PROJECT_PATH=. NDK_APP_OUT=.\..\..\bin\android\release
)
if "%1"=="" (	
	echo Building Debug FutureCore...
	mkdir %~dp0\..\..\..\bin\android\debug
	%NDK_ROOT%ndk-build.cmd NDK_PROJECT_PATH=%~dp0 NDK_APP_OUT=%~dp0\..\..\..\bin\android\debug

	echo Building Profile FutureCore...
	mkdir %~dp0\..\..\..\bin\android\profile
	%NDK_ROOT%ndk-build.cmd NDK_PROJECT_PATH=%~dp0 NDK_APP_OUT=%~dp0\..\..\..\bin\android\profile

	echo Building Profile FutureCore...
	mkdir %~dp0\..\..\..\bin\android\release
	%NDK_ROOT%ndk-build.cmd NDK_PROJECT_PATH=%~dp0 NDK_APP_OUT=%~dp0\..\..\..\bin\android\release
)
cd ..
:EOF
echo End of File