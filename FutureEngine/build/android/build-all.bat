@echo off

if not defined NDK_ROOT (
	echo Please define NDK_ROOT to your local copy of the Android NDK
	goto EOF
)

echo Building FutureCore...
FutureCore/build.bat

:EOF
echo End of File