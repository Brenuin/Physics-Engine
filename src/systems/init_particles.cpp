#include "systems/init_particles.h"
#include "Vector3.h"

using namespace tachyon;

void initializeParticles(std::vector<Particle>& particles, std::vector<int>& flashFrames, int boxSize, bool enableRandomVelocity) {
    float radius = 0.05f;
    float spacing = radius * 2.1f;

    for (int x = -boxSize; x <= boxSize; ++x) {
        for (int y = -boxSize; y <= boxSize; ++y) {
            for (int z = -boxSize; z <= boxSize; ++z) {
                Particle p;
                p.setPosition(x * spacing, y * spacing, z * spacing);

                if (enableRandomVelocity) {
                    float vx = 15*((rand() % 200) - 100) / 200.0f;
                    float vy = 15*((rand() % 200) - 100) / 200.0f;
                    float vz = 15*((rand() % 200) - 100) / 200.0f;
                    p.setVelocity(vx, vy, vz);
                } else {
                    p.setVelocity(0.0f, 0.0f, 0.0f);
                }

                p.setAcceleration(0.0f, 0.0f, 0.0f);
                p.setMass(1.0f);
                p.setDamping(0.99f);
                p.radius = radius;

                particles.push_back(p);
                flashFrames.push_back(0);
            }
        }
    }
}
