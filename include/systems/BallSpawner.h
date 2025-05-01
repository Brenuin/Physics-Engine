#pragma once
#include "rigid/RigidBody.h"
#include <vector>
#include <random>

namespace tachyon {

// CONFIG: Adjust angular velocity limits here
static constexpr float MIN_ANGULAR_VELOCITY = -8.0f;
static constexpr float MAX_ANGULAR_VELOCITY = 8.0f;

class BallSpawner2D {
    float boxWidth, boxHeight;
    float minRadius, maxRadius;
    float minSpeed, maxSpeed;

    std::default_random_engine rng;
    std::uniform_real_distribution<float> uniform01;

public:
    BallSpawner2D(float boxW, float boxH,
                  float minR, float maxR,
                  float minSpd, float maxSpd)
        : boxWidth(boxW), boxHeight(boxH),
          minRadius(minR), maxRadius(maxR),
          minSpeed(minSpd), maxSpeed(maxSpd),
          uniform01(0.0f, 1.0f) {}

    std::vector<RigidBody*> spawnBalls(int count) {
        std::vector<RigidBody*> result;
        for (int i = 0; i < count; ++i) {
            float r = lerp(minRadius, maxRadius, random());
            float speed = lerp(minSpeed, maxSpeed, random());
            float angle = random() * 2.0f * 3.14159265f;

            Vector3 pos(
                lerp(-boxWidth + r, boxWidth - r, random()),
                lerp(-boxHeight + r, boxHeight - r, random()),
                0.0f
            );
            Vector3 vel(
                cos(angle) * speed,
                sin(angle) * speed,
                0.0f
            );

            float mass = r * r;
            float spin = lerp(MIN_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY, random());

            RigidBody* b = new RigidBody();
            b->position = pos;
            b->velocity = vel;
            b->rotation = Vector3(0.0f, 0.0f, spin);  // ✅ set angular velocity
            b->inverseMass = 1.0f / mass;
            b->linearDamping = 0.99f;
            b->angularDamping = 1.0f;
            b->boundingRadius = r;

            result.push_back(b);
        }
        return result;
    }

private:
    float random() {
        return uniform01(rng);
    }

    float lerp(float a, float b, float t) {
        return a + t * (b - a);
    }
};

} // namespace tachyon
