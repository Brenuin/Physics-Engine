#pragma once

#include "core/Vector3.h"
#include "rigid/RigidBody.h"
#include "core/percision.h"

namespace tachyon {

class RigidBodyContact {
public:
    // The two bodies involved in the contact
    RigidBody* body[2];

    // Contact normal, from body[0] to body[1]
    Vector3 contactNormal;

    // Contact point in world coordinates
    Vector3 contactPoint;

    // Depth of penetration at the contact point
    real penetration;

    // Later: For resolution
    real restitution;
    real friction;

    Vector3 contactVelocity;
    Matrix3 contactToWorld;
    Vector3 relativeContactPosition[2];
    real desiredDeltaVelocity;

    RigidBodyContact()
        : restitution(0.2f), friction(0.3f) { // default example values
        body[0] = nullptr;
        body[1] = nullptr;
    }

    // Swap bodies and invert normal (sometimes needed)
    void swapBodies() {
        contactNormal = -contactNormal;
        std::swap(body[0], body[1]);
    }

    // Match awake/sleep state
    void matchAwakeState();

    // Calculates internal data (before resolution)
    void calculateInternals(real duration);

    // Applies position changes
    void applyPositionChange(Vector3 linearChange[2], Vector3 angularChange[2], real penetration);

    // Applies velocity changes
    void applyVelocityChange(Vector3 velocityChange[2], Vector3 rotationChange[2]);

    // Resolves velocity and interpenetration
    void resolve(real duration);

private:
    void calculateContactBasis();
    void calculateDesiredDeltaVelocity(real duration);
    Vector3 calculateLocalVelocity(unsigned bodyIndex, real duration);
};

} // namespace tachyon
