@echo off

SET PRJ_PATH=%~dp0\
SET BUILD_PATH_WIN32=%~dp0\build\win32\data

echo COPY DATA FROM 
echo %PRJ_PATH%
echo TO 
echo %BUILD_PATH_WIN32%
echo.

xcopy %PRJ_PATH%\data %BUILD_PATH_WIN32% /E /Y /I /Q

pause