@echo off

echo Cleaning Android FutureCore...
if "%1"=="debug" (
	call %~dp0\..\clean-android %~dp0 debug
)
if "%1"=="profile" (
	call %~dp0\..\clean-android %~dp0 profile
)
if "%1"=="release" (
	call %~dp0\..\clean-android %~dp0 release
)
if "%1"=="" (	
	call %~dp0\..\clean-android %~dp0 debug
	call %~dp0\..\clean-android %~dp0 profile
	call %~dp0\..\clean-android %~dp0 release
)
