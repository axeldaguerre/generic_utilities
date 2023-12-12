@echo off

setlocal 

set buildPattern=*%1*_main.cpp

if "%~1" =="" set buildPattern=*_main.cpp

FOR %%n IN (%buildPattern%) DO (call build_single.bat	%%n)

endlocal