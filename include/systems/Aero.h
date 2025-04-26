#pragma once

#include "rigid/RigidBody.h"
#include "core/Matrix3.h"
#include "RigidBodyForceGenerator.h"

namespace tachyon {

class Aero : public RigidBodyForceGenerator {
protected:
    Matrix3 tensor;
    Vector3 position;               // in body space
    const Vector3* windspeed;      // pointer to global wind vector

public:
    Aero(const Matrix3& tensor, const Vector3& position, const Vector3* windspeed);
    virtual void updateForce(RigidBody* body, real duration) override;
};

}
