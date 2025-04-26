#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include "rigid/RigidBody.h"
#include "systems/AeroControl.h"
#include "systems/RigidBodyForceRegistry.h"
using namespace tachyon;

void drawCube(float size) {
    float s = size / 2.0f;
    glBegin(GL_QUADS);

    // Front
    glVertex3f(-s, -s,  s); glVertex3f( s, -s,  s);
    glVertex3f( s,  s,  s); glVertex3f(-s,  s,  s);

    // Back
    glVertex3f(-s, -s, -s); glVertex3f(-s,  s, -s);
    glVertex3f( s,  s, -s); glVertex3f( s, -s, -s);

    // Left
    glVertex3f(-s, -s, -s); glVertex3f(-s, -s,  s);
    glVertex3f(-s,  s,  s); glVertex3f(-s,  s, -s);

    // Right
    glVertex3f( s, -s, -s); glVertex3f( s,  s, -s);
    glVertex3f( s,  s,  s); glVertex3f( s, -s,  s);

    // Top
    glVertex3f(-s,  s, -s); glVertex3f(-s,  s,  s);
    glVertex3f( s,  s,  s); glVertex3f( s,  s, -s);

    // Bottom
    glVertex3f(-s, -s, -s); glVertex3f( s, -s, -s);
    glVertex3f( s, -s,  s); glVertex3f(-s, -s,  s);

    glEnd();
}

// Gentle upward-left wind
Vector3 wind(-0.05f, 0.05f, 0.0f);

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Aero Simulation", NULL, NULL);
    if (!window) return -1;
    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glOrtho(-100, 100, -100, 100, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    RigidBody body;
    body.setMass(2.0f);
    Matrix3 inertiaTensor;
    inertiaTensor.setDiagonal(1.0f, 1.0f, 1.0f);
    body.setInertiaTensor(inertiaTensor);
    body.velocity = Vector3(0.2f, 0.0f, 0.0f);
    body.position = Vector3(0.0f, 0.0f, 0.0f);
    body.linearDamping = 0.95f;
    body.angularDamping = 0.9f;
    body.calculateDerivedData();

    // Gentle lift behavior
    Matrix3 base, minT, maxT;
    base.setDiagonal(0.01f, 0.05f, 0.01f);
    minT.setDiagonal(0.005f, 0.02f, 0.005f);
    maxT.setDiagonal(0.02f, 0.1f, 0.02f);

    Vector3 aeroPos(0.0f, 5.0f, 0.0f); // Above center for torque
    AeroControl control(base, minT, maxT, aeroPos, &wind);
    control.setControl(1.0f);

    RigidBodyForceRegistry registry;
    registry.add(&body, &control);

    float dt = 0.1f;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -100.0f);

        body.clearAccumulators();
        registry.updateForces(dt);

        // Optional velocity clamp to avoid chaos
        const float maxSpeed = 10.0f;
        if (body.velocity.magnitude() > maxSpeed) {
            body.velocity.normalize();
            body.velocity *= maxSpeed;
        }

        body.integrate(dt);
        body.calculateDerivedData();

        Vector3 pos = body.position;
        std::cout << "Position: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

        glPushMatrix();
        glTranslatef(pos.x, pos.y, 0.0f);
        glColor3f(0.2f, 0.6f, 1.0f);
        drawCube(10.0f);
        glPopMatrix();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
