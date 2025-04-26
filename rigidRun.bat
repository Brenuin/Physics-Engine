@echo off
echo ===============================
echo Compiling Rigid Aero Simulation with GLFW
echo ===============================

g++ ^
 src\rigidMain.cpp ^
 src\rigid\RigidBody.cpp ^
 src\systems\AeroControl.cpp ^
 src\systems\RigidBodyForceRegistry.cpp ^
 src\systems\RigidBodyForceGenerator.cpp ^
 src\systems\Aero.cpp ^
 -o build\RigidAeroSim.exe ^
 -Iinclude ^
 -Iinclude\core ^
 -Iinclude\rigid ^
 -Iinclude\systems ^
 -IC:\glfw-3.4.bin.WIN64\include ^
 -LC:\glfw-3.4.bin.WIN64\lib-mingw-w64 ^
 -lglfw3 -lopengl32 -lgdi32

if errorlevel 1 (
    echo.
    echo ❌ Compilation failed.
    pause
    exit /b
)

echo ✅ Compilation successful.

echo.
echo Copying glfw3.dll...
copy /Y C:\glfw-3.4.bin.WIN64\lib-mingw-w64\glfw3.dll build\ >nul

echo.
echo 🚀 Launching Rigid Aero Simulation...
echo ===============================
build\RigidAeroSim.exe

echo.
echo Program finished.
pause
