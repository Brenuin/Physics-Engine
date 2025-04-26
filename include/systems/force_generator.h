#pragma once
#include "particles/Particle.h"

namespace tachyon {

// Base class for single-particle forces
class ParticleForceGenerator {
public:
    virtual void updateForce(Particle* particle, float duration) = 0;
};

// Base class for pairwise forces
class ParticlePairForceGenerator {
public:
    virtual void updateForce(Particle* a, Particle* b, float duration) = 0;
};

// Anchored spring: pulls particle toward a fixed point
class ParticleAnchoredSpring : public ParticleForceGenerator {
    Vector3* anchor;
    real springConstant;
    real restLength;

public:
    ParticleAnchoredSpring(Vector3* anchor, real springConstant, real restLength);
    void updateForce(Particle* particle, real duration) override;
};

// Simple spring between two particles
class ParticleSpring : public ParticleForceGenerator {
    Particle* other;
    real springConstant;
    real restLength;

public:
    ParticleSpring(Particle* other, real springConstant, real restLength);
    void updateForce(Particle* particle, real duration) override;
};

// Gravity: F = m * g
class ParticleGravity : public ParticleForceGenerator {
    Vector3 gravity;

public:
    ParticleGravity(const Vector3& gravity);
    void updateForce(Particle* particle, float duration) override;
};

// Drag: F = -v * (k1 * |v| + k2 * |v|²)
class ParticleDrag : public ParticleForceGenerator {
    float k1;
    float k2;

public:
    ParticleDrag(float k1, float k2);
    void updateForce(Particle* particle, float duration) override;
};

// Newtonian gravity between two particles
class ParticleMutualGravity : public ParticlePairForceGenerator {
    float G;

public:
    ParticleMutualGravity(float G);
    void updateForce(Particle* a, Particle* b, float duration) override;
};

// Buoyancy force for partially or fully submerged particles
class ParticleBuoyancy : public ParticleForceGenerator {
    real maxDepth;
    real volume;
    real waterHeight;
    real liquidDensity;

public:
    ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity = 1000.0f);
    void updateForce(Particle* particle, real duration) override;
};

} // namespace tachyon
