#pragma once

#include "Aero.h"

namespace tachyon {

class AeroControl : public Aero {
protected:
    Matrix3 minTensor;
    Matrix3 maxTensor;
    real controlSetting;

    Matrix3 getTensor() const;

public:
    AeroControl(const Matrix3& base, const Matrix3& min, const Matrix3& max,
                const Vector3& position, const Vector3* windspeed);

    void setControl(real value);
    virtual void updateForce(RigidBody* body, real duration) override;
};

}
