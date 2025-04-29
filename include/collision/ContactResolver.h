#pragma once

#include "rigid/RigidBodyContact.h"
#include "core/percision.h"

namespace tachyon {

class ContactResolver {
private:
    unsigned iterations;
    unsigned iterationsUsed;

public:
    ContactResolver(unsigned iterations)
        : iterations(iterations), iterationsUsed(0) {}

    // Set how many iterations to allow
    void setIterations(unsigned iterations) {
        this->iterations = iterations;
    }

    // Main entry point: resolve all contacts
    void resolveContacts(RigidBodyContact* contactArray, unsigned numContacts, real duration);
};

} // namespace tachyon
