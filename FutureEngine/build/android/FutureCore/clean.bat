@echo off

echo Cleaning FutureCore...
%NDK_ROOT%ndk-build.cmd NDK_APP_OUT=./../../../bin/android/debug/ clean
%NDK_ROOT%ndk-build.cmd NDK_APP_OUT=./../../../bin/android/profile/ clean
%NDK_ROOT%ndk-build.cmd NDK_APP_OUT=./../../../bin/android/release/ clean

:EOF
echo End of File