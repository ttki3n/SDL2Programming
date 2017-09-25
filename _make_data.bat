@echo off

call _config.bat

SET BUILD_DATA_PATH_WIN32=%BUILD_PATH_WIN32%data
SET BUILD_DATA_PATH_X64=%BUILD_PATH_X64%data

echo COPY DATA FROM 
echo %PRJ_PATH%
echo TO 
echo %BUILD_DATA_PATH_WIN32%
echo.

xcopy %PRJ_PATH%\data %BUILD_DATA_PATH_WIN32% /E /Y /I /Q

pause