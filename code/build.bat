@echo off
IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

set CommonCompilerFlags=-MTd -nologo -fp:fast -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505  -FC -Z7
set CommonLinkerFlags=  user32.lib gdi32.lib winmm.lib

call cl -Zi -W4 -EHsc -nologo  -wd4100 -wd4996 -wd4189 -wd4505 ..\code\console_name.cpp -Feconsole_template_msvc_debug.exe /link user32.lib


popd
