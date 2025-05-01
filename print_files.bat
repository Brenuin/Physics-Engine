@echo off
setlocal enabledelayedexpansion

echo ===============================
echo 🔍 Printing Selected Files
echo ===============================

:: ---- FLAGS (set true/false) ----

:: Core
set PRINT_Vector3=true
set PRINT_BoundingSphere=true
set PRINT_BVHNode=false
set PRINT_Matrix3=false
set PRINT_Matrix4=false
set PRINT_quaternion=false
set PRINT_globals=false
set PRINT_percision=false

:: Collision
set PRINT_CollisionDetector=true
set PRINT_ContactResolver=true

:: Rigid
set PRINT_RigidBody=true
set PRINT_RigidBodyContact=true

:: Render
set PRINT_Renderer=false

:: World
set PRINT_World=true

:: Particles
set PRINT_Particle=false
set PRINT_ParticleContact=false
set PRINT_ParticleContactResolver=false
set PRINT_particle_pair_registry=false

:: Systems
set PRINT_BallSpawner=true
set PRINT_BoundingBoxCollider=true
set PRINT_Aero=false
set PRINT_AeroControl=false
set PRINT_collision=false
set PRINT_force_generator=false
set PRINT_force_registry=false
set PRINT_force_setup=false
set PRINT_init_constraints=false
set PRINT_init_particles=false
set PRINT_render_particles=false
set PRINT_RigidBodyForceGenerator=false
set PRINT_RigidBodyForceRegistry=false

:: Constraints
set PRINT_ParticleCable=true
set PRINT_ParticleRod=true
set PRINT_ParticleLink=true

:: ---- END FLAGS ----

set SHOW=type

:: ======== Core ========
if "%PRINT_Vector3%"=="true" %SHOW% include\core\Vector3.h
if "%PRINT_BoundingSphere%"=="true" %SHOW% include\core\BoundingSphere.h
if "%PRINT_BVHNode%"=="true" %SHOW% include\core\BVHNode.h
if "%PRINT_Matrix3%"=="true" %SHOW% include\core\Matrix3.h
if "%PRINT_Matrix4%"=="true" %SHOW% include\core\Matrix4.h
if "%PRINT_quaternion%"=="true" %SHOW% include\core\quaternion.h
if "%PRINT_globals%"=="true" %SHOW% include\core\globals.h
if "%PRINT_percision%"=="true" %SHOW% include\core\percision.h

:: ======== Collision ========
if "%PRINT_CollisionDetector%"=="true" (
    %SHOW% include\collision\CollisionDetector.h
)
if "%PRINT_ContactResolver%"=="true" (
    %SHOW% include\collision\ContactResolver.h
    %SHOW% src\collision\ContactResolver.cpp
)

:: ======== Rigid ========
if "%PRINT_RigidBody%"=="true" (
    %SHOW% include\rigid\RigidBody.h
    %SHOW% src\rigid\RigidBody.cpp
)
if "%PRINT_RigidBodyContact%"=="true" (
    %SHOW% include\rigid\RigidBodyContact.h
    %SHOW% src\rigid\RigidBodyContact.cpp
)

:: ======== Render ========
if "%PRINT_Renderer%"=="true" (
    %SHOW% include\render\Renderer.h
    %SHOW% src\render\Renderer.cpp
)

:: ======== World ========
if "%PRINT_World%"=="true" (
    %SHOW% include\world\World.h
    %SHOW% src\world\World.cpp
)

:: ======== Particles ========
if "%PRINT_Particle%"=="true" (
    %SHOW% include\particles\Particle.h
    %SHOW% src\particles\Particle.cpp
)
if "%PRINT_ParticleContact%"=="true" (
    %SHOW% include\particles\ParticleContact.h
    %SHOW% src\particles\ParticleContact.cpp
)
if "%PRINT_ParticleContactResolver%"=="true" (
    %SHOW% include\particles\ParticleContactResolver.h
    %SHOW% src\particles\ParticleContactResolver.cpp
)
if "%PRINT_particle_pair_registry%"=="true" (
    %SHOW% include\particles\particle_pair_registry.h
    %SHOW% src\particles\particle_pair_registry.cpp
)

:: ======== Systems ========
if "%PRINT_BallSpawner%"=="true" (
    %SHOW% include\systems\BallSpawner.h
    %SHOW% src\systems\BallSpawner.cpp
)
if "%PRINT_BoundingBoxCollider%"=="true" (
    %SHOW% include\systems\BoundingBoxCollider.h
    %SHOW% src\systems\BoundingBoxCollider.cpp
)
if "%PRINT_Aero%"=="true" (
    %SHOW% include\systems\Aero.h
    %SHOW% src\systems\Aero.cpp
)
if "%PRINT_AeroControl%"=="true" (
    %SHOW% include\systems\AeroControl.h
    %SHOW% src\systems\AeroControl.cpp
)
if "%PRINT_collision%"=="true" (
    %SHOW% include\systems\collision.h
    %SHOW% src\systems\collision.cpp
)
if "%PRINT_force_generator%"=="true" (
    %SHOW% include\systems\force_generator.h
    %SHOW% src\systems\force_generator.cpp
)
if "%PRINT_force_registry%"=="true" (
    %SHOW% include\systems\force_registry.h
    %SHOW% src\systems\force_registry.cpp
)
if "%PRINT_force_setup%"=="true" (
    %SHOW% include\systems\force_setup.h
    %SHOW% src\systems\force_setup.cpp
)
if "%PRINT_init_constraints%"=="true" (
    %SHOW% include\systems\init_constraints.h
    %SHOW% src\systems\init_constraints.cpp
)
if "%PRINT_init_particles%"=="true" (
    %SHOW% include\systems\init_particles.h
    %SHOW% src\systems\init_particles.cpp
)
if "%PRINT_render_particles%"=="true" (
    %SHOW% include\systems\render_particles.h
    %SHOW% src\systems\render_particles.cpp
)
if "%PRINT_RigidBodyForceGenerator%"=="true" (
    %SHOW% include\systems\RigidBodyForceGenerator.h
    %SHOW% src\systems\RigidBodyForceGenerator.cpp
)
if "%PRINT_RigidBodyForceRegistry%"=="true" (
    %SHOW% include\systems\RigidBodyForceRegistry.h
    %SHOW% src\systems\RigidBodyForceRegistry.cpp
)

:: ======== Constraints ========
if "%PRINT_ParticleCable%"=="true" (
    %SHOW% include\constraints\ParticleCable.h
    %SHOW% src\constraints\ParticleCable.cpp
)
if "%PRINT_ParticleRod%"=="true" (
    %SHOW% include\constraints\ParticleRod.h
    %SHOW% src\constraints\ParticleRod.cpp
)
if "%PRINT_ParticleLink%"=="true" (
    %SHOW% include\constraints\ParticleLink.h
    %SHOW% src\constraints\ParticleLink.cpp
)

:: ======== Main Files (Always Print) ========
echo.
echo 📦 Printing main source files:
%SHOW% src\main.cpp
%SHOW% src\main2.cpp
%SHOW% src\main3.cpp
%SHOW% src\main4.cpp
%SHOW% src\rigidMain.cpp

echo ===============================
echo ✅ Done
pause
