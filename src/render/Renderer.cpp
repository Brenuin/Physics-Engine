#include "render/Renderer.h"
#include <GL/gl.h>
#include <cmath>
#include <algorithm>

namespace tachyon {

Renderer::Renderer(unsigned width, unsigned height, float scale)
    : windowWidth(width), windowHeight(height), worldToScreenScale(scale), cameraOffset(0, 0, 0) {}

void Renderer::beginFrame() {
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)windowWidth / (float)windowHeight;
    glOrtho(-aspect * worldToScreenScale, aspect * worldToScreenScale,
            -worldToScreenScale, worldToScreenScale,
            -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::renderWorld(const std::vector<RigidBody*>& bodies) {
    for (RigidBody* body : bodies) {
        drawRigidBody(body);
        drawAngularVelocityVector(body); // <-- Can be commented out easily
    }
}

void Renderer::endFrame(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void Renderer::setCameraOffset(const Vector3& offset) {
    cameraOffset = offset;
}

void Renderer::drawRigidBody(RigidBody* body) {
    const int segments = 32;
    float radius = body->boundingRadius;
    Vector3 pos = body->position + cameraOffset;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.4f, 0.7f, 1.0f);
    glVertex2f(pos.x, pos.y);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * 2.0f * 3.1415926535f / segments;
        glVertex2f(pos.x + cos(angle) * radius,
                   pos.y + sin(angle) * radius);
    }
    glEnd();
}

void Renderer::drawAngularVelocityVector(RigidBody* body) {
    float spinZ = body->rotation.z;
    if (std::fabs(spinZ) < 0.001f) return;

    float radius = body->boundingRadius;
    float arrowLength = std::clamp(spinZ * radius * 1.5f, -radius * 2.5f, radius * 2.5f);

    Vector3 pos = body->position + cameraOffset;
    Vector3 tail = pos;
    Vector3 head = pos + Vector3(0.0f, arrowLength, 0.0f);

    glColor3f(1.0f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(tail.x, tail.y);
    glVertex2f(head.x, head.y);
    glEnd();
}

} // namespace tachyon
