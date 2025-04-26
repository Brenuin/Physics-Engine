#include "systems/RigidBodyForceRegistry.h"

namespace tachyon {

void RigidBodyForceRegistry::add(RigidBody* body, RigidBodyForceGenerator* fg) {
    registrations.push_back({ body, fg });
}

void RigidBodyForceRegistry::remove(RigidBody* body, RigidBodyForceGenerator* fg) {
    registrations.erase(std::remove_if(registrations.begin(), registrations.end(),
        [&](const ForceRegistration& reg) {
            return reg.body == body && reg.generator == fg;
        }), registrations.end());
}

void RigidBodyForceRegistry::clear() {
    registrations.clear();
}

void RigidBodyForceRegistry::updateForces(real duration) {
    for (auto& reg : registrations) {
        reg.generator->updateForce(reg.body, duration);
    }
}

}
