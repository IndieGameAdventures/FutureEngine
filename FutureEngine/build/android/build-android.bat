@echo off

if not defined NDK_ROOT (
	echo Please define NDK_ROOT to your local copy of the Android NDK
	goto EOF
)

if not exist %~dp0\..\..\bin\android\%2 (
	mkdir %~dp0\..\..\bin\android\%2
)

echo call %NDK_ROOT%ndk-build.cmd NDK_PROJECT_PATH=%1 NDK_APP_OUT=%~dp0\..\..\bin\android\%2 %2=1
call %NDK_ROOT%ndk-build.cmd NDK_PROJECT_PATH=%1 NDK_APP_OUT=%~dp0\..\..\bin\android\%2 %2=1
