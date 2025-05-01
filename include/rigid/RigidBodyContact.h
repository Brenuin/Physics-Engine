#pragma once

#include "core/Vector3.h"
#include "core/Matrix3.h"
#include "rigid/RigidBody.h"
#include "core/percision.h"

namespace tachyon {

class RigidBodyContact {
public:
    RigidBody* body[2];
    Vector3 contactNormal;
    Vector3 contactPoint;
    real penetration;
    real restitution;
    real friction;

    Vector3 contactVelocity;
    Matrix3 contactToWorld;
    Vector3 relativeContactPosition[2];
    real desiredDeltaVelocity;

    RigidBodyContact()
        : restitution(0.2f), friction(0.3f) {
        body[0] = nullptr;
        body[1] = nullptr;
    }

    void swapBodies();
    void matchAwakeState();
    void calculateInternals(real duration);
    void resolve(real duration);
    void applyVelocityChange(Vector3 velocityChange[2], Vector3 rotationChange[2]);
    void applyPositionChange(Vector3 linearChange[2], Vector3 angularChange[2], real penetration);

private:
    void calculateContactBasis();
    Vector3 calculateLocalVelocity(unsigned bodyIndex, real duration);
    void calculateDesiredDeltaVelocity(real duration);
};

} // namespace tachyon
