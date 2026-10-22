@echo off
chcp 65001 >nul
"C:\Users\lsy08\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe" "%~dp0doctor.py"
set "check_result=%errorlevel%"
echo.
pause
exit /b %check_result%
