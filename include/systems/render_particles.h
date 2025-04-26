#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include "particles/particle.h"

namespace tachyon {
    void renderParticles(const std::vector<Particle>& particles, const std::vector<int>& flashFrames, bool flashOnCollision, GLFWwindow* window, float pointSize);
}
