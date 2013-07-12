@echo off

if "%1"=="debug" (
	echo Building Android Debug FutureGame...
	set _DEBUG=1
	call %~dp0\..\build-android %~dp0 debug
	set _DEBUG=0
)
if "%1"=="profile" (
	echo Building Android Profile FutureGame...
	set _RELEASE=1
	set _PROFILE=1
	call %~dp0\..\build-android %~dp0 profile
	set _PROFILE=0
	set _RELEASE=0
)
if "%1"=="release" (
	echo Building Android Profile FutureGame...
	set _RELEASE=1
	call %~dp0\..\build-android %~dp0 release
	set _RELEASE=0
)
if "%1"=="" (	
	echo  
	echo Building Android Debug FutureGame...
	set _DEBUG=1
	call %~dp0\..\build-android %~dp0 debug
	set _DEBUG=0

	echo  
	echo Building Android Profile FutureGame...
	set _RELEASE=1
	set _PROFILE=1
	call %~dp0\..\build-android %~dp0 profile
	set _PROFILE=0

	echo  
	echo Building Android Release FutureGame...
	set _RELEASE=1
	call %~dp0\..\build-android %~dp0 release
	set _RELEASE=0
)


