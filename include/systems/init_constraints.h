#pragma once

#include <vector>
#include "particles/Particle.h"
#include "constraints/ParticleCable.h"
#include "constraints/ParticleRod.h"

namespace tachyon {
    void initializeConstraints(
        std::vector<Particle>& particles,
        std::vector<ParticleCable>& cables,
        std::vector<ParticleRod>& rods,
        bool useCables,
        bool useRods,
        int gridSize,
        float spacing
    );
    
}
