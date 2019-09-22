@echo off
echo Remove Computer Management
echo If you do not Remove this, You can Close this Script
pause
set debug=

set nowOperating=Remove services 
for %%i in (Computer%debug%,ComputerControl%debug%) do (
sc stop %%i
sc delete %%i && echo %nowOperating%%%i[success] || echo %nowOperating%%%i[error]
)

set nowOperating=Remove services path 
rmdir /s /q "%ALLUSERSPROFILE%\Weteoes\Computer%debug%" && echo %nowOperating%[success] || echo %nowOperating%[error]

set nowOperating=Remove TEMP path 
rmdir /s /q "%TEMP%\Weteoes\Computer Management%debug%" && echo %nowOperating%[success] || echo %nowOperating%[error]

set nowOperating=Remove Regedit 
reg delete HKEY_LOCAL_MACHINE\SOFTWARE\Weteoes\Computer%debug% /f && echo %nowOperating%[success] || echo %nowOperating%[error]

set nowOperating=Remove Boot 
schtasks /delete /TN "Computer Management%debug%" /F && echo %nowOperating%[success] || echo %nowOperating%[error]

echo.
echo ---------------------------------------------
echo Remove Computer Management Success
echo ---------------------------------------------
echo.
pause