@echo off
IF NOT EXIST .\build mkdir .\build
pushd .\build

set CommonCompilerFlags=-MTd -nologo -fp:fast -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505  -FC -Z7
set CommonLinkerFlags=  user32.lib gdi32.lib winmm.lib

call cl -Zi -W4 -EHsc -nologo  -wd4100 -wd4996 -wd4189 -wd4505 ../%1 -Fe%1_msvc_dm.exe /link user32.lib
call cl -W4 -EHsc -nologo  -wd4100 -wd4996 -wd4189 -wd4505 ../%1 -Fe%1_msvc_rm.exe /link user32.lib

popd