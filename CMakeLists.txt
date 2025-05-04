cmake_minimum_required(VERSION 3.22)
project(physics_engine)

set(CMAKE_CXX_STANDARD 17)

# Force precise floating-point behavior (MSVC only)
add_compile_options(/fp:precise)

# GLFW include and link
include_directories("C:/Libraries/glfw-3.4.bin.WIN64/include")
link_directories("C:/Libraries/glfw-3.4.bin.WIN64/lib-vc2022")

# Your include folders
include_directories(include include/core include/rigid include/render include/world)

# Executable
add_executable(main4
    src/main4.cpp
    src/rigid/RigidBody.cpp
    src/rigid/RigidBodyContact.cpp
    src/world/World.cpp
    src/render/Renderer.cpp
    src/collision/ContactResolver.cpp
)

# Link GLFW and system libs
target_link_libraries(main4 glfw3 opengl32 gdi32)
