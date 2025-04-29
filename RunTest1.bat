@echo off
echo ===============================
echo Compiling RigidBodyContactBHV Test
echo ===============================

g++ ^
 src\tests\RigidBodyContactBHV.cpp ^
 src\rigid\RigidBody.cpp ^
 src\collision\ContactResolver.cpp ^
 src\rigid\RigidBodyContact.cpp ^
 -o build\RigidBodyContactBHV.exe ^
 -Iinclude ^
 -Iinclude\core ^
 -Iinclude\rigid ^
 -Iinclude\collision ^
 -std=c++17

if errorlevel 1 (
    echo.
    echo ❌ Compilation failed.
    pause
    exit /b
)

echo ✅ Compilation successful.

echo.
echo 🚀 Launching RigidBodyContactBHV...
echo ===============================
build\RigidBodyContactBHV.exe

echo.
echo Program finished.
pause
