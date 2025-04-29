@echo off
echo ===============================
echo Compiling Main4 (RigidBodyContactBHV World) with MinGW
echo ===============================

g++ ^
 src\main4.cpp ^
 src\rigid\RigidBody.cpp ^
 src\rigid\RigidBodyContact.cpp ^
 src\world\World.cpp ^
 src\collision\ContactResolver.cpp ^
 -o build\RigidBodyContactBHV.exe ^
 -Iinclude ^
 -Iinclude\core ^
 -Iinclude\rigid ^
 -Iinclude\collision ^
 -Iinclude\render ^
 -Isrc

if errorlevel 1 (
    echo.
    echo ❌ Compilation failed.
    pause
    exit /b
)

echo ✅ Compilation successful.

echo.
echo 🚀 Launching RigidBodyContactBHV.exe...
echo ===============================
build\RigidBodyContactBHV.exe

echo.
echo Program finished.
pause
