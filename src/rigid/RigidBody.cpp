#include "rigid/RigidBody.h"

using namespace tachyon;

void RigidBody::calculateDerivedData() {
    orientation.normalize();
    transformMatrix = Matrix4::fromPositionOrientation(position, orientation);
    transformInertiaTensor(inverseInertiaTensorWorld, orientation, inverseInertiaTensor, transformMatrix);
}
void RigidBody::transformInertiaTensor(Matrix3 &iitWorld, const Quaternion &q, const Matrix3 &iitBody, const Matrix4 &rotMat) {
    Matrix3 tform = rotMat.toMatrix3();

    real t4 = tform.m[0][0]*iitBody.m[0][0] + tform.m[0][1]*iitBody.m[1][0] + tform.m[0][2]*iitBody.m[2][0];
    real t9 = tform.m[0][0]*iitBody.m[0][1] + tform.m[0][1]*iitBody.m[1][1] + tform.m[0][2]*iitBody.m[2][1];
    real t14 = tform.m[0][0]*iitBody.m[0][2] + tform.m[0][1]*iitBody.m[1][2] + tform.m[0][2]*iitBody.m[2][2];

    real t28 = tform.m[1][0]*iitBody.m[0][0] + tform.m[1][1]*iitBody.m[1][0] + tform.m[1][2]*iitBody.m[2][0];
    real t33 = tform.m[1][0]*iitBody.m[0][1] + tform.m[1][1]*iitBody.m[1][1] + tform.m[1][2]*iitBody.m[2][1];
    real t38 = tform.m[1][0]*iitBody.m[0][2] + tform.m[1][1]*iitBody.m[1][2] + tform.m[1][2]*iitBody.m[2][2];

    real t52 = tform.m[2][0]*iitBody.m[0][0] + tform.m[2][1]*iitBody.m[1][0] + tform.m[2][2]*iitBody.m[2][0];
    real t57 = tform.m[2][0]*iitBody.m[0][1] + tform.m[2][1]*iitBody.m[1][1] + tform.m[2][2]*iitBody.m[2][1];
    real t62 = tform.m[2][0]*iitBody.m[0][2] + tform.m[2][1]*iitBody.m[1][2] + tform.m[2][2]*iitBody.m[2][2];

    iitWorld.m[0][0] = t4 * tform.m[0][0] + t9 * tform.m[0][1] + t14 * tform.m[0][2];
    iitWorld.m[0][1] = t4 * tform.m[1][0] + t9 * tform.m[1][1] + t14 * tform.m[1][2];
    iitWorld.m[0][2] = t4 * tform.m[2][0] + t9 * tform.m[2][1] + t14 * tform.m[2][2];

    iitWorld.m[1][0] = t28 * tform.m[0][0] + t33 * tform.m[0][1] + t38 * tform.m[0][2];
    iitWorld.m[1][1] = t28 * tform.m[1][0] + t33 * tform.m[1][1] + t38 * tform.m[1][2];
    iitWorld.m[1][2] = t28 * tform.m[2][0] + t33 * tform.m[2][1] + t38 * tform.m[2][2];

    iitWorld.m[2][0] = t52 * tform.m[0][0] + t57 * tform.m[0][1] + t62 * tform.m[0][2];
    iitWorld.m[2][1] = t52 * tform.m[1][0] + t57 * tform.m[1][1] + t62 * tform.m[1][2];
    iitWorld.m[2][2] = t52 * tform.m[2][0] + t57 * tform.m[2][1] + t62 * tform.m[2][2];
}


void RigidBody::integrate(real duration) {
    if (inverseMass <= 0.0f) return;

    lastFrameAcceleration = acceleration;
    lastFrameAcceleration += forceAccum * inverseMass;

    velocity += lastFrameAcceleration * duration;
    velocity *= pow(linearDamping, duration);

    Vector3 angularAcceleration = inverseInertiaTensorWorld * torqueAccum;;
    rotation += angularAcceleration * duration;
    rotation *= pow(angularDamping, duration);

    position += velocity * duration;
    orientation.addScaledVector(rotation, duration);
    calculateDerivedData();
    clearAccumulators();
}

void RigidBody::setMass(real mass) {
    inverseMass = 1.0f / mass;
}

void RigidBody::setInertiaTensor(const Matrix3 &inertiaTensor) {
    inverseInertiaTensor = inertiaTensor.inverse();
}

void RigidBody::addForce(const Vector3 &force) {
    forceAccum += force;
}

void RigidBody::addTorque(const Vector3 &torque) {
    torqueAccum += torque;
}

void RigidBody::addForceAtPoint(const Vector3 &force, const Vector3 &point) {
    Vector3 pt = point - position;
    forceAccum += force;
    torqueAccum += pt.vectorProduct(force);
}

void RigidBody::clearAccumulators() {
    forceAccum.clear();
    torqueAccum.clear();
}

Vector3 RigidBody::getVelocityAtPoint(const Vector3& localPoint) const {
    return velocity + rotation % localPoint; 
}