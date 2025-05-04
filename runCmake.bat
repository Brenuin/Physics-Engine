@echo off
setlocal

rmdir /s /q build
mkdir build

echo ============================
echo 🔧 Configuring
echo ============================
cmake -S . -B build -G "Visual Studio 17 2022"

echo ============================
echo 🛠️ Building
echo ============================
cmake --build build --config Debug

echo ============================
echo 🚀 Running
echo ============================
build\Debug\main4.exe

pause
