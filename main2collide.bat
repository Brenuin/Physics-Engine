@echo off
echo ===============================
echo Compiling main2 with updated structure
echo ===============================

g++ ^
 src\main2.cpp ^
 src\particles\Particle.cpp ^
 src\particles\ParticleContact.cpp ^
 src\particles\ParticleContactResolver.cpp ^
 src\particles\particle_pair_registry.cpp ^
 src\systems\force_generator.cpp ^
 src\systems\force_registry.cpp ^
 src\systems\collision.cpp ^
 -o build\main2.exe ^
 -Iinclude ^
 -Iinclude\core ^
 -Iinclude\particles ^
 -Iinclude\systems ^
 -Iinclude\constraints ^
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
echo 🚀 Launching main2.exe...
echo ===============================
build\main2.exe

echo.
echo Program finished.
pause
