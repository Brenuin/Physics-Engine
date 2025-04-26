#pragma once
#include <vector>
#include "particles/particle.h"
#include "particles/ParticleContact.h"
#include "particles/ParticleContactResolver.h"

namespace tachyon {
    void resolveCollisions(std::vector<Particle>& particles, std::vector<int>& flashFrames, bool flashOnCollision, float timeStep);
}
