#include <cassert>
#include <cmath>
#include "particles/Particle.h"

#define real_pow powf

using namespace tachyon;

Particle::Particle()
    : position(), velocity(), acceleration(), forceAccum(),
      inverseMass(1.0f), damping(0.99f), radius(1.0f)
{
}

void Particle::integrate(real duration) {
    assert(duration > 0.0f);
    position.addScaledVector(velocity, duration);
    Vector3 resultingAcc = acceleration;
    resultingAcc.addScaledVector(forceAccum, inverseMass);
    velocity.addScaledVector(resultingAcc, duration);
    velocity *= real_pow(damping, duration);
    clearAccumulator();
}

void Particle::clearAccumulator() {
    forceAccum = Vector3();
}

void Particle::addForce(const Vector3& force) {
    forceAccum += force;
}

void Particle::setPosition(const Vector3& p) {
    position = p;
}

void Particle::setPosition(real x, real y, real z) {
    position = Vector3(x, y, z);
}

Vector3 Particle::getPosition() const {
    return position;
}

void Particle::setVelocity(const Vector3& v) {
    velocity = v;
}

void Particle::setVelocity(real x, real y, real z) {
    velocity = Vector3(x, y, z);
}

Vector3 Particle::getVelocity() const {
    return velocity;
}

void Particle::setAcceleration(const Vector3& a) {
    acceleration = a;
}

void Particle::setAcceleration(real x, real y, real z) {
    acceleration = Vector3(x, y, z);
}

Vector3 Particle::getAcceleration() const {
    return acceleration;
}

void Particle::setDamping(real d) {
    damping = d;
}

real Particle::getDamping() const {
    return damping;
}

void Particle::setMass(real mass) {
    inverseMass = 1.0f / mass;
}

real Particle::getMass() const {
    if (inverseMass == 0) return INFINITY;
    return 1.0f / inverseMass;
}

real Particle::getInverseMass() const {
    return inverseMass;
}

bool Particle::hasFiniteMass() const {
    return inverseMass > 0.0f;
}
