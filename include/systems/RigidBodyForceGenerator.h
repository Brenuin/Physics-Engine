#pragma once

#include "rigid/RigidBody.h"

namespace tachyon {

class RigidBodyForceGenerator {
public:
    virtual ~RigidBodyForceGenerator() {}
    virtual void updateForce(RigidBody* body, real duration) = 0;
};

class GravityForce : public RigidBodyForceGenerator {
    Vector3 gravity;
public:
    GravityForce(const Vector3& gravity);
    virtual void updateForce(RigidBody* body, real duration) override;
};

class DragForce : public RigidBodyForceGenerator {
    real k1, k2;
public:
    DragForce(real k1, real k2);
    virtual void updateForce(RigidBody* body, real duration) override;
};

class SpringForce : public RigidBodyForceGenerator {
    Vector3 connectionPoint;
    RigidBody* other;
    Vector3 otherConnectionPoint;
    real springConstant;
    real restLength;
public:
    SpringForce(const Vector3& localConn, RigidBody* otherBody,
                const Vector3& otherConn, real k, real restLen);
    virtual void updateForce(RigidBody* body, real duration) override;
};

}
