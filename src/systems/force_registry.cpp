// force_registry.cpp
#include <algorithm>
#include "systems/force_registry.h"

namespace tachyon {



void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg) {
    registrations.push_back({ particle, fg });
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg) {
    registrations.erase(
        std::remove_if(registrations.begin(), registrations.end(),
            [=](const ParticleForceRegistration& reg) {
                return reg.particle == particle && reg.fg == fg;
            }),
        registrations.end()
    );
}

void ParticleForceRegistry::clear() {
    registrations.clear();
}

void ParticleForceRegistry::updateForces(float duration) {
    for (auto& reg : registrations) {
        reg.fg->updateForce(reg.particle, duration);
    }
}



}
