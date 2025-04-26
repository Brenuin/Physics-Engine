#define ENABLE_GRAVITY           false
#define ENABLE_DAMPING           false
#define ENABLE_COLLISIONS        true

#define TIME_STEP       0.1f
#define PARTICLE_MASS   1.0f
#define BOX_LIMIT       80.0f

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>

#include "particles/ParticleContact.h"
#include "particles/ParticleContactResolver.h"
#include "particles/Particle.h"
#include "core/Vector3.h"
#include "systems/force_registry.h"
#include "systems/force_generator.h"
#include "systems/collision.h"
using namespace tachyon;

struct CollisionFlash {
    int framesLeft = 0;
};


void initializeTestParticles(std::vector<Particle>& particles, std::vector<CollisionFlash>& flashes) {
    float radius = 5.0f;
    float spacing = radius * 2.5f;

    for (int x = -2; x <= 2; ++x) {
        for (int y = -2; y <= 2; ++y) {
            Particle p;
            p.setPosition(x * spacing, y * spacing, 0.0f);
            float vx = ((rand() % 200) - 100) / 100.0f;
            float vy = ((rand() % 200) - 100) / 100.0f;
            p.setVelocity(vx, vy, 0.0f);
            p.setAcceleration(0.0f, 0.0f, 0.0f);
            p.setMass(PARTICLE_MASS);
            p.setDamping(0.98f);
            p.radius = radius;
            particles.push_back(p);
            flashes.push_back(CollisionFlash());
        }
    }
}


void renderScene(const std::vector<Particle>& particles, const std::vector<CollisionFlash>& flashes, GLFWwindow* window) {
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -200.0f);


    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-BOX_LIMIT, -BOX_LIMIT);
    glVertex2f(BOX_LIMIT, -BOX_LIMIT);
    glVertex2f(BOX_LIMIT, BOX_LIMIT);
    glVertex2f(-BOX_LIMIT, BOX_LIMIT);
    glEnd();

    if (!particles.empty()) {
        glPointSize(particles[0].radius * (1000.0f / BOX_LIMIT));
    }

    glBegin(GL_POINTS);
    for (size_t i = 0; i < particles.size(); ++i) {
        const Vector3& pos = particles[i].getPosition();
        if (flashes[i].framesLeft > 0)
            glColor3f(1.0f, 0.2f, 0.2f);  // Flash red on collision
        else
            glColor3f(0.9f, 0.9f, 1.0f);
        glVertex3f(pos.x, pos.y, pos.z);
    }
    glEnd();

    glFlush();
    glfwSwapBuffers(window);
}


int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(1000, 800, "Collision Visualizer", NULL, NULL);
    if (!window) return -1;
    glfwMakeContextCurrent(window);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glOrtho(-100, 100, -80, 80, 1.0f, 300.0f);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    std::vector<Particle> particles;
    std::vector<CollisionFlash> flashes;
    initializeTestParticles(particles, flashes);

    ParticleForceRegistry registry;
    if (ENABLE_DAMPING) {
        ParticleDrag drag(0.01f, 0.01f);
        for (auto& p : particles) {
            registry.add(&p, new ParticleDrag(drag));
        }
    }

    while (!glfwWindowShouldClose(window)) {
        for (auto& p : particles) p.clearAccumulator();
        registry.updateForces(TIME_STEP);

        for (auto& f : flashes) if (f.framesLeft > 0) f.framesLeft--;

        for (auto& p : particles) {
            p.integrate(TIME_STEP);

            Vector3 pos = p.getPosition();
            Vector3 vel = p.getVelocity();
            float r = p.radius;

            if (pos.x - r < -BOX_LIMIT || pos.x + r > BOX_LIMIT) {
                vel.x *= -1;
                pos.x = std::clamp(pos.x, -BOX_LIMIT + r, BOX_LIMIT - r);
            }
            if (pos.y - r < -BOX_LIMIT || pos.y + r > BOX_LIMIT) {
                vel.y *= -1;
                pos.y = std::clamp(pos.y, -BOX_LIMIT + r, BOX_LIMIT - r);
            }

            p.setVelocity(vel);
            p.setPosition(pos);
        }

        if (ENABLE_COLLISIONS) {
            std::vector<int> flashFrames(flashes.size());
            for (size_t i = 0; i < flashes.size(); ++i)
                flashFrames[i] = flashes[i].framesLeft;

            resolveCollisions(particles, flashFrames, true, TIME_STEP);

            for (size_t i = 0; i < flashes.size(); ++i)
                flashes[i].framesLeft = flashFrames[i];
        }

        renderScene(particles, flashes, window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
