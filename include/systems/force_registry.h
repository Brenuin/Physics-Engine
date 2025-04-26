
#pragma once
#include <vector>
#include "particles/Particle.h"
#include "force_generator.h"

namespace tachyon {

class ParticleForceRegistry {
protected:
    struct ParticleForceRegistration {
        Particle* particle;
        ParticleForceGenerator* fg;
    };

    typedef std::vector<ParticleForceRegistration> Registry;
    Registry registrations;

public:
    void add(Particle* particle, ParticleForceGenerator* fg);
    void remove(Particle* particle, ParticleForceGenerator* fg);
    void clear();
    void updateForces(float duration);
};

} // namespace tachyon