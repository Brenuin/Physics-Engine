#pragma once
#include "rigid/RigidBody.h"
#include <vector>

namespace tachyon {

class BoundingBoxCollider {
    float halfWidth;
    float halfHeight;

public:
    BoundingBoxCollider(float windowWidth, float windowHeight, float scale) {
        float aspect = windowWidth / windowHeight;
        halfWidth = aspect * scale;
        halfHeight = scale;
    }

    void constrainBodies(std::vector<RigidBody*>& bodies) const {
        for (RigidBody* body : bodies) {
            Vector3& pos = body->position;
            Vector3& vel = body->velocity;
            float r = body->boundingRadius;

            if (pos.x - r < -halfWidth) {
                pos.x = -halfWidth + r;
                vel.x *= -1;
            } else if (pos.x + r > halfWidth) {
                pos.x = halfWidth - r;
                vel.x *= -1;
            }

            if (pos.y - r < -halfHeight) {
                pos.y = -halfHeight + r;
                vel.y *= -1;
            } else if (pos.y + r > halfHeight) {
                pos.y = halfHeight - r;
                vel.y *= -1;
            }
        }
    }
};

} // namespace tachyon
