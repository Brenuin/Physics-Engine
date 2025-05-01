@echo off
echo ===============================
echo Compiling main4 with GLFW
echo ===============================

g++ ^
 src\main4.cpp ^
 src\rigid\RigidBody.cpp ^
 src\rigid\RigidBodyContact.cpp ^
 src\world\World.cpp ^
 src\render\Renderer.cpp ^
 src\collision\ContactResolver.cpp ^
 -o build\main4.exe ^
 -Iinclude ^
 -Iinclude\core ^
 -Iinclude\rigid ^
 -Iinclude\world ^
 -Iinclude\render ^
 -IC:\glfw-3.4.bin.WIN64\include ^
 -LC:\glfw-3.4.bin.WIN64\lib-mingw-w64 ^
 -lglfw3 -lopengl32 -lgdi32 ^
 -std=c++17

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
echo 🚀 Launching main4.exe...
build\main4.exe
pause
