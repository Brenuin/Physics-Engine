#include "systems/force_generator.h"

namespace tachyon {

// ===== Anchored Spring =====
ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3* anchor, real springConstant, real restLength)
    : anchor(anchor), springConstant(springConstant), restLength(restLength) {}

void ParticleAnchoredSpring::updateForce(Particle* particle, real duration) {
    Vector3 force = particle->getPosition() - *anchor;
    real magnitude = force.magnitude();
    magnitude = (magnitude - restLength) * springConstant;
    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}

// ===== Regular Spring =====
ParticleSpring::ParticleSpring(Particle* other, real springConstant, real restLength)
    : other(other), springConstant(springConstant), restLength(restLength) {}

void ParticleSpring::updateForce(Particle* particle, real duration) {
    Vector3 force = particle->getPosition() - other->getPosition();
    real magnitude = force.magnitude();
    magnitude = real_abs(magnitude - restLength) * springConstant;
    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}

// ===== Gravity =====
ParticleGravity::ParticleGravity(const Vector3& gravity) : gravity(gravity) {}

void ParticleGravity::updateForce(Particle* particle, float duration) {
    if (!particle->hasFiniteMass()) return;
    particle->addForce(gravity * particle->getMass());
}

// ===== Drag =====
ParticleDrag::ParticleDrag(float k1, float k2) : k1(k1), k2(k2) {}

void ParticleDrag::updateForce(Particle* particle, float duration) {
    Vector3 force = particle->getVelocity();
    float speed = force.magnitude();
    float drag = k1 * speed + k2 * speed * speed;
    force.normalize();
    force *= -drag;
    particle->addForce(force);
}

// ===== Mutual Gravity =====
ParticleMutualGravity::ParticleMutualGravity(float G) : G(G) {}

void ParticleMutualGravity::updateForce(Particle* a, Particle* b, float duration) {
    Vector3 delta = b->getPosition() - a->getPosition();
    float distSq = delta.magnitudeSquared() + 1e-6f; // prevent div by zero
    float forceMag = G / distSq / (a->getInverseMass() * b->getInverseMass());
    delta.normalize();
    Vector3 force = delta * forceMag;

    a->addForce(force);
    b->addForce(-force);
}

// ===== Buoyancy =====
ParticleBuoyancy::ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity)
    : maxDepth(maxDepth), volume(volume), waterHeight(waterHeight), liquidDensity(liquidDensity) {}

void ParticleBuoyancy::updateForce(Particle* particle, real duration) {
    real depth = particle->getPosition().y;

    if (depth >= waterHeight + maxDepth) return;

    Vector3 force(0, 0, 0);

    if (depth <= waterHeight - maxDepth) {
        force.y = liquidDensity * volume;
    } else {
        force.y = liquidDensity * volume *
                  (waterHeight + maxDepth - depth) / (2 * maxDepth);
    }

    particle->addForce(force);
}

} // namespace tachyon
