#include "systems/Aero.h"
#include "core/Matrix4.h"

namespace tachyon {

Aero::Aero(const Matrix3& tensor_, const Vector3& position_, const Vector3* windspeed_)
    : tensor(tensor_), position(position_), windspeed(windspeed_) {}

void Aero::updateForce(RigidBody* body, real duration) {
    if (body->inverseMass == 0) return;

    Vector3 worldPos = body->transformMatrix * position;
    Vector3 velocity = body->velocity + body->rotation % position;
    Vector3 relativeVelocity = velocity - *windspeed;

    Matrix3 bodyOrientation = body->transformMatrix.toMatrix3();  // you may define this
    Matrix3 bodyOrientationInv = bodyOrientation.transpose();
    Vector3 bodyVel = bodyOrientationInv * relativeVelocity;

    Vector3 bodyForce = tensor * bodyVel;
    Vector3 worldForce = bodyOrientation * bodyForce;

    body->addForceAtPoint(worldForce, worldPos);
}

}
