#pragma once
#include "core/Vector3.h"
#include "core/Matrix3.h"
#include "core/Matrix4.h"
#include "core/Quaternion.h"

namespace tachyon {

class RigidBody {
public:
    Vector3 position;
    Quaternion orientation;
    Vector3 velocity;
    Vector3 rotation;

    Matrix4 transformMatrix;
    Matrix3 inverseInertiaTensor;
    Matrix3 inverseInertiaTensorWorld;

    real inverseMass;
    real linearDamping;
    real angularDamping;

    Vector3 forceAccum;
    Vector3 torqueAccum;
    Vector3 acceleration;
    Vector3 lastFrameAcceleration;

    void calculateDerivedData();
    void integrate(real duration);
    void setMass(real mass);
    void setInertiaTensor(const Matrix3 &inertiaTensor);
    void addForce(const Vector3 &force);
    void addTorque(const Vector3 &torque);
    void addForceAtPoint(const Vector3 &force, const Vector3 &point);
    void clearAccumulators();
    Vector3 getVelocityAtPoint(const Vector3& localPoint) const;
private:
    void transformInertiaTensor(Matrix3 &iitWorld, const Quaternion &q, const Matrix3 &iitBody, const Matrix4 &rotMat);
};

}
