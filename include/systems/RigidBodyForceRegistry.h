#pragma once

#include <vector>
#include <algorithm>
#include "rigid/RigidBody.h"
#include "RigidBodyForceGenerator.h"

namespace tachyon {

class RigidBodyForceRegistry {
protected:
    struct ForceRegistration {
        RigidBody* body;
        RigidBodyForceGenerator* generator;
    };

    std::vector<ForceRegistration> registrations;

public:
    void add(RigidBody* body, RigidBodyForceGenerator* fg);
    void remove(RigidBody* body, RigidBodyForceGenerator* fg);
    void clear();
    void updateForces(real duration);
};

}
