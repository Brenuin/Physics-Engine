#pragma once
#include <vector>
#include "Particle.h"
#include "systems/force_generator.h"

namespace tachyon {

class ParticlePairForceGenerator;

class ParticlePairForceRegistry {
protected:
    struct PairForceRegistration {
        Particle* a;
        Particle* b;
        ParticlePairForceGenerator* fg;
    };
    std::vector<PairForceRegistration> registrations;

public:
    void add(Particle* a, Particle* b, ParticlePairForceGenerator* fg);
    void updateForces(float duration);
    void clear();
};

}
    