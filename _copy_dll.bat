@echo off

call _config.bat

echo COPY SDL2 DLL


xcopy %LIBS_PATH%SDL2\lib\x86\SDl2.dll %BUILD_PATH_WIN32% /E /Y /I /Q
xcopy %LIBS_PATH%SDL2\lib\x64\SDl2.dll %BUILD_PATH_X64% /E /Y /I /Q

pause