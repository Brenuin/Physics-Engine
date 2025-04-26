@echo off
echo ===============================
echo Compiling main3 with ImGui + GLFW
echo ===============================

g++ ^
 src\main3.cpp ^
 src\particles\Particle.cpp ^
 src\particles\ParticleContact.cpp ^
 src\particles\ParticleContactResolver.cpp ^
 src\particles\particle_pair_registry.cpp ^
 src\systems\force_generator.cpp ^
 src\systems\force_registry.cpp ^
 src\systems\init_particles.cpp ^
 src\systems\init_constraints.cpp ^
 src\systems\render_particles.cpp ^
 src\systems\force_setup.cpp ^
 src\systems\collision.cpp ^
 src\constraints\ParticleRod.cpp ^
 src\constraints\ParticleCable.cpp ^
 external\imgui\imgui.cpp ^
 external\imgui\imgui_draw.cpp ^
 external\imgui\imgui_tables.cpp ^
 external\imgui\imgui_widgets.cpp ^
 external\imgui\backends\imgui_impl_glfw.cpp ^
 external\imgui\backends\imgui_impl_opengl3.cpp ^
 -o build\main3.exe ^
 -Iinclude ^
 -Iinclude\core ^
 -Iinclude\particles ^
 -Iinclude\systems ^
 -Iinclude\constraints ^
 -Iexternal\imgui ^
 -Iexternal\imgui\backends ^
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
echo 🚀 Launching main3.exe...
echo ===============================
build\main3.exe

echo.
echo Program finished.
pause
