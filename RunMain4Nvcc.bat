@echo off
echo ===============================
echo Compiling main4 with NVCC and MSVC
echo ===============================

:: Initialize MSVC environment
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64

:: Compile using NVCC + MSVC linker
nvcc ^
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
  -LC:\glfw-3.4.bin.WIN64\lib-vc2022 ^
  -lglfw3 -lopengl32 -lgdi32 ^
  -luser32 -lkernel32 -lshell32 -luuid -lcomdlg32 -ladvapi32 ^
  -std=c++17 ^
  -Xcompiler "/MD /fp:precise"
  :: For debugging, uncomment below:
  :: -G -g -Xcompiler "/Zi /MD /fp:precise"

:: Handle failure
if errorlevel 1 (
    echo.
    echo ❌ Compilation failed.
    pause
    exit /b
)

echo ✅ Compilation successful.
echo.
echo Copying glfw3.dll...
copy /Y C:\glfw-3.4.bin.WIN64\lib-vc2022\glfw3.dll build\ >nul
echo.
echo 🚀 Launching main4.exe...
build\main4.exe
pause
