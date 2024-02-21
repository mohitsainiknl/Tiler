@echo off

set BASEDIR=%~dp0
PUSHD %BASEDIR%

REM Check if Python is installed
python --version >nul 2>&1
if %errorlevel% equ 0 (
    python ./Scripts/setup_tiler_project.py %*
) else (
    echo python is also not available.
)
