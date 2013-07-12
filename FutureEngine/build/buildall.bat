@echo OFF

::call "%VS110COMNTOOLS%vsvars32.bat"

::devenv vs9/all.sln /rebuild "Debug"
::IF ERRORLEVEL 1 GOTO L_ERROR
::devenv vs9/all.sln /rebuild "Release"
::IF ERRORLEVEL 1 GOTO L_ERROR

for %%p in (WIN32,LINUX,ANDROID) do (
		make PLATFORM=%%p clean
		if ERRORLEVEL 1 goto err
		make PLATFORM=%%p debug
		if ERRORLEVEL 1 goto err
		make PLATFORM=%%p profile
		if ERRORLEVEL 1 goto err
		make PLATFORM=%%p release
		if ERRORLEVEL 1 goto err
)

goto end

:err
pause
EXIT /B 1

:end
