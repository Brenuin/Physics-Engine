#pragma once
#include <vector>
#include "particles/particle.h"
#include "force_registry.h"
#include "particles/particle_pair_registry.h"

namespace tachyon {
    void applyForces(std::vector<Particle>& particles,
                     ParticleForceRegistry& registry,
                     ParticlePairForceRegistry& pairRegistry,
                     bool enableGravity,
                     bool enableDamping,
                     bool enableAnchoredSprings,
                     bool enableBuoyancy,
                     bool enableSprings,
                     bool enableMutualGravity);
}
