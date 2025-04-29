#include <iostream>
#include "rigid/RigidBodyContact.h"

namespace tachyon {

void RigidBodyContact::matchAwakeState() {
    if (!body[1]) return;

    bool body0awake = body[0]->isAwake;
    bool body1awake = body[1]->isAwake;

    if (body0awake ^ body1awake) {
        if (body0awake) body[1]->isAwake = true;
        else body[0]->isAwake = true;
    }
}

void RigidBodyContact::calculateInternals(real duration) {
    if (!body[0]) return;

    if (!body[1]) contactNormal.invert();

    calculateContactBasis();

    relativeContactPosition[0] = contactPoint - body[0]->position;
    if (body[1]) {
        relativeContactPosition[1] = contactPoint - body[1]->position;
    }

    contactVelocity = calculateLocalVelocity(0, duration);
    if (body[1]) {
        contactVelocity -= calculateLocalVelocity(1, duration);
    }

    calculateDesiredDeltaVelocity(duration);
}

void RigidBodyContact::calculateContactBasis() {
    Vector3 contactTangent[2];

    if (std::fabs(contactNormal.x) > std::fabs(contactNormal.y)) {
        // Choose X axis
        real s = 1.0f / real_sqrt(contactNormal.z * contactNormal.z + contactNormal.x * contactNormal.x);

        contactTangent[0].x = contactNormal.z * s;
        contactTangent[0].y = 0;
        contactTangent[0].z = -contactNormal.x * s;

        contactTangent[1].x = contactNormal.y * contactTangent[0].x;
        contactTangent[1].y = contactNormal.z * contactTangent[0].x - contactNormal.x * contactTangent[0].z;
        contactTangent[1].z = -contactNormal.y * contactTangent[0].x;
    } else {
        // Choose Y axis
        real s = 1.0f / real_sqrt(contactNormal.z * contactNormal.z + contactNormal.y * contactNormal.y);

        contactTangent[0].x = 0;
        contactTangent[0].y = -contactNormal.z * s;
        contactTangent[0].z = contactNormal.y * s;

        contactTangent[1].x = contactNormal.y * contactTangent[0].z - contactNormal.z * contactTangent[0].y;
        contactTangent[1].y = -contactNormal.x * contactTangent[0].z;
        contactTangent[1].z = contactNormal.x * contactTangent[0].y;
    }

    contactToWorld = Matrix3();
    contactToWorld.m[0][0] = contactNormal.x;
    contactToWorld.m[0][1] = contactTangent[0].x;
    contactToWorld.m[0][2] = contactTangent[1].x;

    contactToWorld.m[1][0] = contactNormal.y;
    contactToWorld.m[1][1] = contactTangent[0].y;
    contactToWorld.m[1][2] = contactTangent[1].y;

    contactToWorld.m[2][0] = contactNormal.z;
    contactToWorld.m[2][1] = contactTangent[0].z;
    contactToWorld.m[2][2] = contactTangent[1].z;
}

Vector3 RigidBodyContact::calculateLocalVelocity(unsigned bodyIndex, real duration) {
    RigidBody* thisBody = body[bodyIndex];

    Vector3 velocity = thisBody->rotation % relativeContactPosition[bodyIndex];
    velocity += thisBody->velocity;

    Vector3 contactVelocity = contactToWorld.transpose() * velocity;

    Vector3 accVelocity = thisBody->lastFrameAcceleration * duration;
    accVelocity = contactToWorld.transpose() * accVelocity;

    accVelocity.x = 0;

    contactVelocity += accVelocity;

    return contactVelocity;
}

void RigidBodyContact::calculateDesiredDeltaVelocity(real duration) {
    const static real velocityLimit = 0.25f;

    real velocityFromAcc = 0;
    if (body[0]->isAwake) {
        velocityFromAcc += (body[0]->lastFrameAcceleration * duration) * contactNormal;
    }
    if (body[1] && body[1]->isAwake) {
        velocityFromAcc -= (body[1]->lastFrameAcceleration * duration) * contactNormal;
    }

    real thisRestitution = restitution;
    if (std::fabs(contactVelocity.x) < velocityLimit) {
        thisRestitution = 0.0f;
    }

    desiredDeltaVelocity = -contactVelocity.x - thisRestitution * (contactVelocity.x - velocityFromAcc);
}

void RigidBodyContact::resolve(real duration) {
    std::cout << "Resolve called!!" << std::endl;

    // 🛠 DEBUG PRINT
    std::cout << "=== Inside Contact::resolve ===" << std::endl;
    std::cout << "Penetration: " << penetration << std::endl;
    std::cout << "Contact Normal: (" << contactNormal.x << ", " << contactNormal.y << ", " << contactNormal.z << ")" << std::endl;

    calculateInternals(duration);

    Vector3 velocityChange[2];
    Vector3 rotationChange[2];
    Vector3 linearChange[2];
    Vector3 angularChange[2];

    applyVelocityChange(velocityChange, rotationChange);
    applyPositionChange(linearChange, angularChange, penetration);
}




void RigidBodyContact::applyVelocityChange(Vector3 velocityChange[2], Vector3 rotationChange[2]) {
    // Inverse mass sums
    real totalInverseMass = body[0]->inverseMass;
    if (body[1]) totalInverseMass += body[1]->inverseMass;

    // No impulse if both bodies have infinite mass
    if (totalInverseMass <= 0.0f) return;

    // Calculate impulse scalar
    real impulseScalar = desiredDeltaVelocity / totalInverseMass;

    // Final impulse in world space
    Vector3 impulse = contactNormal * impulseScalar;

    // Apply impulse to each body
    velocityChange[0] = impulse * body[0]->inverseMass;
    body[0]->velocity += velocityChange[0];

    if (body[1]) {
        velocityChange[1] = impulse * -body[1]->inverseMass;
        body[1]->velocity += velocityChange[1];
    }
}


void RigidBodyContact::applyPositionChange(Vector3 linearChange[2], Vector3 angularChange[2], real penetration) {
    real totalInverseMass = body[0]->inverseMass;
    if (body[1]) totalInverseMass += body[1]->inverseMass;

    if (totalInverseMass <= 0.0f) return;

    // Move the objects apart proportionally to their inverse mass
    Vector3 movePerIMass = contactNormal * (penetration / totalInverseMass);

    linearChange[0] = movePerIMass * body[0]->inverseMass;
    body[0]->position += linearChange[0];

    if (body[1]) {
        linearChange[1] = movePerIMass * -body[1]->inverseMass;
        body[1]->position += linearChange[1];
    }
}

} // namespace tachyon
