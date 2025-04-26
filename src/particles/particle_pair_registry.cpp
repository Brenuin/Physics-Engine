#include "particles/particle_pair_registry.h"

namespace tachyon {

void ParticlePairForceRegistry::add(Particle* a, Particle* b, ParticlePairForceGenerator* fg) {
    registrations.push_back({ a, b, fg });
}

void ParticlePairForceRegistry::updateForces(float duration) {
    for (auto& reg : registrations) {
        reg.fg->updateForce(reg.a, reg.b, duration);
    }
}

void ParticlePairForceRegistry::clear() {
    registrations.clear();
}

}
