#include "systems/AeroControl.h"
#include "core/Matrix4.h"

namespace tachyon {

AeroControl::AeroControl(const Matrix3& base, const Matrix3& min, const Matrix3& max,
                         const Vector3& position, const Vector3* windspeed)
    : Aero(base, position, windspeed), minTensor(min), maxTensor(max), controlSetting(0.0f) {}

void AeroControl::setControl(real value) {
    controlSetting = value;
}

Matrix3 AeroControl::getTensor() const {
    Matrix3 result;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            result.m[row][col] =
                tensor.m[row][col] * (1.0f - controlSetting) +
                maxTensor.m[row][col] * controlSetting;
        }
    }

    return result;
}


void AeroControl::updateForce(RigidBody* body, real duration) {
    if (body->inverseMass == 0) return;

    Matrix3 currentTensor = getTensor();

    Vector3 worldPos = body->transformMatrix * position;
    Vector3 velocity = body->velocity + body->rotation % position;
    Vector3 relativeVelocity = velocity - *windspeed;

    Matrix3 bodyOrientation = body->transformMatrix.toMatrix3();
    Matrix3 bodyOrientationInv = bodyOrientation.transpose();
    Vector3 bodyVel = bodyOrientationInv * relativeVelocity;

    Vector3 bodyForce = currentTensor * bodyVel;
    Vector3 worldForce = bodyOrientation * bodyForce;

    body->addForceAtPoint(worldForce, worldPos);
}

}
