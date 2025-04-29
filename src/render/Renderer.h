#pragma once

#include "world/World.h"
#include <iostream>

namespace tachyon {

// Later you can replace with real OpenGL/ImGui drawing.
// For now: simple text output or debug visual.

class Renderer {
public:
    Renderer() = default;

    void render(const World& world) {
        std::cout << "\n=== Frame Render ===" << std::endl;

        int index = 0;
        for (const RigidBody* body : world.bodies) {
            std::cout << "Body " << index++ << ": "
                      << "Position (" << body->position.x << ", " << body->position.y << ", " << body->position.z << ") "
                      << "Velocity (" << body->velocity.x << ", " << body->velocity.y << ", " << body->velocity.z << ") "
                      << std::endl;
        }
    }
};

} // namespace tachyon
