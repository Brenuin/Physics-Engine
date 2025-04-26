@echo off
echo ===============================
echo Compiling ParticleCollisionTest with GLFW
echo ===============================

g++ ^
 src\main2.cpp src\Particle.cpp src\ParticleContact.cpp src\ParticleContactResolver.cpp ^
 src\force_generator.cpp src\particle_pair_registry.cpp src\force_registry.cpp src\collision.cpp ^
 -o build\ParticleCollisionTest.exe ^
 -Iinclude ^
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
echo 🚀 Launching ParticleCollisionTest...
echo ===============================
build\ParticleCollisionTest.exe

echo.
echo Program finished.
pause
