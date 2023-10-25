@echo off
setlocal enabledelayedexpansion

set "sourceFolder=C:\MEGA_DRIVE_ROMS"
set "outputFolder=C:\MEGA_DRIVE_ROMS"

for %%A in ("%sourceFolder%\*") do (
    set "fileName=%%~nA"
    set "fileExt=%%~xA"
    set "archiveName=!fileName!!fileExt!.7z"
    "C:\Program Files\7-Zip\7z.exe" a "!outputFolder!\!archiveName!" "%%A"
)
