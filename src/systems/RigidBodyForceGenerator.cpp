#include "systems/RigidBodyForceGenerator.h"

namespace tachyon {

GravityForce::GravityForce(const Vector3& gravity_) : gravity(gravity_) {}

void GravityForce::updateForce(RigidBody* body, real duration) {
    if (body->inverseMass == 0) return;
    body->addForce(gravity * (1.0f / body->inverseMass));
}

DragForce::DragForce(real k1_, real k2_) : k1(k1_), k2(k2_) {}

void DragForce::updateForce(RigidBody* body, real duration) {
    Vector3 force = body->velocity;
    real speed = force.magnitude();
    real dragCoeff = k1 * speed + k2 * speed * speed;
    force.normalize();
    force *= -dragCoeff;
    body->addForce(force);
}

// --- SpringForce ---
SpringForce::SpringForce(const Vector3& localConn, RigidBody* otherBody,
                         const Vector3& otherConn, real k, real restLen)
    : connectionPoint(localConn), other(otherBody),
      otherConnectionPoint(otherConn), springConstant(k), restLength(restLen) {}

void SpringForce::updateForce(RigidBody* body, real duration) {
    Vector3 worldA = body->transformMatrix * connectionPoint;
    Vector3 worldB = other->transformMatrix * otherConnectionPoint;
    Vector3 force = worldA - worldB;
    real length = force.magnitude();
    real delta = length - restLength;
    real magnitude = -springConstant * delta;
    force.normalize();
    force *= magnitude;
    body->addForceAtPoint(force, worldA);
}

}
