#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <omp.h>
#include <vector>
#include <algorithm>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "core/globals.h"
#include "particles/Particle.h"
#include "core/Vector3.h"
#include "particles/ParticleContact.h"
#include "particles/ParticleContactResolver.h"
#include "systems/force_registry.h"
#include "particles/particle_pair_registry.h"
#include "systems/init_particles.h"
#include "systems/render_particles.h"
#include "systems/force_setup.h"
#include "systems/collision.h"
#include "constraints/ParticleCable.h"
#include "constraints/ParticleRod.h"
#include "systems/init_constraints.h"

using namespace tachyon;

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Tachyon", NULL, NULL);
    if (!window) return -1;
    glfwMakeContextCurrent(window);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glOrtho(-globalLimit - 5.0f, globalLimit + 5.0f, -globalLimit - 5.0f, globalLimit + 5.0f, 1.0f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    static float pointSize = 5.0f;
    bool enableGravity = false, enableDamping = true, enableSprings = false, enableMutualGravity = true;
    bool enableAnchoredSprings = false, enableBuoyancy = false, enableCollisions = true;
    bool flashOnCollision = true, enableRandomVelocity = false;
    bool useParticles = false, useCables = true, useRods = true;
    float timeStep = 0.01f;
    int boxSize = 3;

    std::vector<Particle> particles;
    std::vector<int> flashFrames;
    std::vector<ParticleCable> cables;
    std::vector<ParticleRod> rods;
    ParticleForceRegistry registry;
    ParticlePairForceRegistry pairRegistry;

    bool shouldCreateParticles = useParticles || useCables || useRods;
    if (shouldCreateParticles)
        initializeParticles(particles, flashFrames, boxSize, enableRandomVelocity);
    if (useCables || useRods)
        initializeConstraints(particles, cables, rods, useCables, useRods, boxSize, 2.0f);
    if (!useParticles && (useCables || useRods))
        flashFrames.resize(particles.size(), 0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Tachyon (Skyler Santos)");
        ImGui::SliderFloat("Particle Size", &pointSize, 1.0f, 20.0f);
        ImGui::Checkbox("Gravity", &enableGravity);
        ImGui::Checkbox("Damping", &enableDamping);
        ImGui::Checkbox("Mutual Gravity", &enableMutualGravity);
        ImGui::Checkbox("Springs", &enableSprings);
        ImGui::Checkbox("Anchored Springs", &enableAnchoredSprings);
        ImGui::Checkbox("Buoyancy", &enableBuoyancy);
        ImGui::Checkbox("Collisions", &enableCollisions);
        ImGui::Checkbox("Flash on Collision", &flashOnCollision);
        ImGui::Checkbox("Random Velocity", &enableRandomVelocity);
        ImGui::Checkbox("Use Particles", &useParticles);
        ImGui::Checkbox("Use Cables", &useCables);
        ImGui::Checkbox("Use Rods", &useRods);
        ImGui::SliderInt("Box Size", &boxSize, 1, 9);
        ImGui::SliderFloat("Simulation Speed", &timeStep, 0.001f, 0.5f, "%.3f", ImGuiSliderFlags_Logarithmic);

        if (ImGui::Button("Restart Simulation")) {
            particles.clear();
            flashFrames.clear();
            cables.clear();
            rods.clear();
            registry.clear();
            pairRegistry.clear();

            bool shouldCreateParticlesNow = useParticles || useCables || useRods;
            if (shouldCreateParticlesNow)
                initializeParticles(particles, flashFrames, boxSize, enableRandomVelocity);
            if (useCables || useRods)
                initializeConstraints(particles, cables, rods, useCables, useRods, boxSize, 2.0f);
            if (!useParticles && (useCables || useRods))
                flashFrames.resize(particles.size(), 0);
        }

        ImGui::End();

        // Only run sim logic if particles exist
        if (!particles.empty()) {
            for (auto& p : particles) p.clearAccumulator();
            for (auto& f : flashFrames) if (f > 0) --f;

            applyForces(particles, registry, pairRegistry, enableGravity, enableDamping,
                        enableAnchoredSprings, enableBuoyancy, enableSprings, enableMutualGravity);

            registry.updateForces(timeStep);
            pairRegistry.updateForces(timeStep);

            for (auto& p : particles) {
                p.integrate(timeStep);
                Vector3 pos = p.getPosition();
                Vector3 vel = p.getVelocity();

                if (pos.x < -globalLimit || pos.x > globalLimit) { vel.x *= -1; pos.x = std::clamp(pos.x, -globalLimit, globalLimit); }
                if (pos.y < -globalLimit || pos.y > globalLimit) { vel.y *= -1; pos.y = std::clamp(pos.y, -globalLimit, globalLimit); }
                if (pos.z < -globalLimit || pos.z > globalLimit) { vel.z *= -1; pos.z = std::clamp(pos.z, -globalLimit, globalLimit); }

                p.setVelocity(vel);
                p.setPosition(pos);
            }

            if (enableCollisions)
                resolveCollisions(particles, flashFrames, flashOnCollision, timeStep);
        }

        // Only render particles if user says so
        if (useParticles)
            renderParticles(particles, flashFrames, flashOnCollision, window, pointSize);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
