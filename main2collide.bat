@echo off
setlocal enabledelayedexpansion

:: 🔄 Locate and call the MSVC environment setup script
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

echo ==============================
echo 🔧 Compiling hello_cuda.cu...
echo ==============================

nvcc -o hello_cuda.exe hello_cuda.cu

if %ERRORLEVEL% neq 0 (
    echo ❌ Compilation failed!
    exit /b %ERRORLEVEL%
)

echo.
echo ==============================
echo 🚀 Running hello_cuda.exe...
echo ==============================
echo.

hello_cuda.exe

endlocal
pause
