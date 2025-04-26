#pragma once

#include "core/Vector3.h"

namespace tachyon {

class Particle {
public:
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    Vector3 forceAccum;

    real inverseMass;
    real damping;
    real radius;

    Particle();

    void integrate(real duration);
    void clearAccumulator();
    void addForce(const Vector3& force);

    void setPosition(const Vector3& p);
    void setPosition(real x, real y, real z);
    Vector3 getPosition() const;

    void setVelocity(const Vector3& v);
    void setVelocity(real x, real y, real z);
    Vector3 getVelocity() const;

    void setAcceleration(const Vector3& a);
    void setAcceleration(real x, real y, real z);
    Vector3 getAcceleration() const;

    void setDamping(real d);
    real getDamping() const;

    void setMass(real mass);
    real getMass() const;
    real getInverseMass() const;
    bool hasFiniteMass() const;
};

}
