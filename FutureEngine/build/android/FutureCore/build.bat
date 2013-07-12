@echo off

if "%1"=="debug" (
	echo Building Android Debug FutureCore...
	set _DEBUG=1
	%~dp0\..\build-android %~dp0 debug
)
if "%1"=="profile" (
	echo Building Android Profile FutureCore...
	set _RELEASE=1
	set _PROFILE=1
	%~dp0\..\build-android %~dp0 profile
)
if "%1"=="release" (
	echo Building Android Profile FutureCore...
	set _RELEASE=1
	%~dp0\..\build-android %~dp0 release
)
if "%1"=="" (	
	echo Building Android Debug FutureCore...
	set _DEBUG=1
	%~dp0\..\build-android %~dp0 debug
	set _DEBUG=0

	echo Building Android Profile FutureCore...
	set _RELEASE=1
	set _PROFILE=1
	%~dp0\..\build-android %~dp0 profile
	set _PROFILE=0

	echo Building Android Release FutureCore...
	set _RELEASE=1
	%~dp0\..\build-android %~dp0 release
)
