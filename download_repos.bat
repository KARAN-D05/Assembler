@echo off
setlocal enabledelayedexpansion
title KARAN-D05 - Repo Downloader

set "REPO[1]=Computing_Machinery_from_Scratch"
set "REPO[2]=Assembler"
set "REPO[3]=Gate-Level-Perceptron"
set "REPO[4]=8-Bit-Computer"
set "REPO[5]=Artificial-Neuron"
set "REPO[6]=portmap-HDL"

set "BASE_URL=https://github.com/KARAN-D05"
set "RAW_URL=https://raw.githubusercontent.com/KARAN-D05"
set "BRANCH=main"

:MENU
cls
echo ============================================
echo   KARAN-D05  ^|  Repository Downloader
echo ============================================
echo.
echo   1.  Computing_Machinery_from_Scratch
echo   2.  Assembler
echo   3.  Gate-Level-Perceptron
echo   4.  8-Bit-Computer
echo   5.  Artificial-Neuron
echo   6.  portmap-HDL
echo   7.  Utils  (filetree.lua + README)
echo   A.  Download ALL repos + utils
echo   Q.  Quit
echo.
echo  Enter one number, several (e.g. 1 3 5),
echo  A for all, or Q to quit.
echo ============================================
echo.
set /p "CHOICE=  Your choice: "

if /i "%CHOICE%"=="Q" (
    echo.
    echo  Goodbye!
    timeout /t 2 >nul
    exit /b 0
)

if /i "%CHOICE%"=="A" (
    set "CHOICE=1 2 3 4 5 6 7"
)

set "DOWNLOADED=0"
set "FAILED=0"

for %%T in (%CHOICE%) do (

    if "%%T"=="7" (
        echo.
        echo  Downloading utils ^(filetree.lua + README^) ...
        if not exist "utils" mkdir utils
        curl -L -o "utils\filetree.lua" "%RAW_URL%/portmap-HDL/%BRANCH%/utils/filetree.lua" --silent
        if !ERRORLEVEL! EQU 0 (
            curl -L -o "utils\README.md" "%RAW_URL%/portmap-HDL/%BRANCH%/utils/README.md" --silent
            if !ERRORLEVEL! EQU 0 (
                echo  Done. Saved to utils\
                set /a DOWNLOADED+=1
            ) else (
                echo  Failed to download utils\README.md.
                set /a FAILED+=1
            )
        ) else (
            echo  Failed to download utils\filetree.lua. Check your internet connection.
            set /a FAILED+=1
        )
    ) else (
        set "VALID=0"
        for /L %%I in (1,1,6) do (
            if "%%T"=="%%I" set "VALID=1"
        )
        if "!VALID!"=="0" (
            echo.
            echo  "%%T" is not a valid option -- skipping.
        ) else (
            set "RNAME=!REPO[%%T]!"
            set "ZIP_URL=!BASE_URL!/!RNAME!/archive/refs/heads/!BRANCH!.zip"
            set "OUT_FILE=!RNAME!.zip"
            echo.
            echo  Downloading !RNAME! ...
            curl -L -o "!OUT_FILE!" "!ZIP_URL!" --silent
            if !ERRORLEVEL! EQU 0 (
                echo  Done. Saved as !OUT_FILE!
                set /a DOWNLOADED+=1
            ) else (
                echo  Failed to download !RNAME!. Check your internet connection.
                set /a FAILED+=1
            )
        )
    )
)

echo.
echo ============================================
echo   Done!  Downloaded: %DOWNLOADED%   Failed: %FAILED%
echo ============================================
echo.
pause
goto MENU
