@echo off
IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

set CommonCompilerFlags=-MTd -nologo -fp:fast -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505  -FC -Z7
set CommonLinkerFlags=  user32.lib gdi32.lib winmm.lib

REM call cl -Zi -W4 -EHsc -nologo  -wd4100 -wd4996 -wd4189 -wd4505 ..\code\delete_empties.cpp -Fedelete_empties_msvc_debug.exe /link user32.lib
REM call cl -W4 -EHsc -nologo  -wd4100 -wd4996 -wd4189 -wd4505 ..\code\delete_empties.cpp -Fedelete_empties_msvc_release.exe /link user32.lib

call cl -Zi -W4 -EHsc -nologo  -wd4100 -wd4996 -wd4189 -wd4505 ..\code\win32_copy_files_from_folder.cpp -Fewin32_copy_files_from_folder_msvc_debug.exe /link user32.lib
call cl -W4 -EHsc -nologo  -wd4100 -wd4996 -wd4189 -wd4505 ..\code\win32_copy_files_from_folder.cpp -Fewin32_copy_files_from_foldermsvc_release.exe /link user32.lib

call cl -Zi -W4 -EHsc -nologo  -wd4100 -wd4996 -wd4189 -wd4505 ..\code\win32_create_7zip_files_from_file.cpp -Fewin32_create_7zip_files_from_file_msvc_debug.exe /link user32.lib
call cl -W4 -EHsc -nologo  -wd4100 -wd4996 -wd4189 -wd4505 ..\code\win32_create_7zip_files_from_file.cpp -Fewin32_create_7zip_files_from_filemsvc_release.exe /link user32.lib


popd
