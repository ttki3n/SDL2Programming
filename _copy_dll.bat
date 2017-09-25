@echo off

call _config.bat
set platforms=(x86 x64)

echo COPY SDL2 DLL
xcopy %LIBS_PATH%SDL2\lib\x86\SDl2.dll %BUILD_PATH_WIN32% /E /Y /I /Q
xcopy %LIBS_PATH%SDL2\lib\x64\SDl2.dll %BUILD_PATH_x64% /E /Y /I /Q





echo COPY SDL2 IMAGE DLL
set sdl2_image_dll2=(SDL2_image.dll libjpeg-9.dll libpng16-16.dll zlib1.dll)
for %%d in %sdl2_image_dll2% do (
	xcopy %LIBS_PATH%SDL2Image\lib\x86\%%d    %BUILD_PATH_WIN32%    /E /Y /I /Q
)
for %%d in %sdl2_image_dll2% do (
	xcopy %LIBS_PATH%SDL2Image\lib\x64\%%d    %BUILD_PATH_x64%    /E /Y /I /Q
)




:END
pause