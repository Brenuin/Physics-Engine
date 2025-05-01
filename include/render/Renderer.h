#pragma once

#include <vector>
#include "rigid/RigidBody.h"
#include <GLFW/glfw3.h>

namespace tachyon {

class Renderer {
public:
    Renderer(unsigned width = 1200, unsigned height = 800, float scale = 1000.0f);

    void beginFrame();
    void renderWorld(const std::vector<RigidBody*>& bodies);
    void endFrame(GLFWwindow* window);
    void setCameraOffset(const Vector3& offset);

private:
    unsigned windowWidth, windowHeight;
    float worldToScreenScale;
    Vector3 cameraOffset;

    void drawRigidBody(RigidBody* body);
    void drawAngularVelocityVector(RigidBody* body);
};

}
