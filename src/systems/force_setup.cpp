#include "systems/force_setup.h"

namespace tachyon {
    void applyForces(std::vector<Particle>& particles,
                     ParticleForceRegistry& registry,
                     ParticlePairForceRegistry& pairRegistry,
                     bool enableGravity,
                     bool enableDamping,
                     bool enableAnchoredSprings,
                     bool enableBuoyancy,
                     bool enableSprings,
                     bool enableMutualGravity) {
        registry.clear();
        pairRegistry.clear();

        if (enableGravity || enableDamping || enableAnchoredSprings || enableBuoyancy) {
            for (auto& p : particles) {
                if (enableGravity) registry.add(&p, new ParticleGravity(Vector3(0, -9.81f, 0)));
                if (enableDamping) registry.add(&p, new ParticleDrag(0.01f, 0.01f));
                if (enableAnchoredSprings) registry.add(&p, new ParticleAnchoredSpring(new Vector3(0, 1, 0), 2.0f, 2.5f));
                if (enableBuoyancy) registry.add(&p, new ParticleBuoyancy(1.0f, 1.0f, 0.0f, 1000.0f));
            }
        }

        if (enableSprings) {
            size_t half = particles.size() / 2;
            for (size_t i = 0; i < half; ++i) {
                registry.add(&particles[i], new ParticleSpring(&particles[i + half], 1.0f, 1.5f));
                registry.add(&particles[i + half], new ParticleSpring(&particles[i], 1.0f, 1.5f));
            }
        }

        if (enableMutualGravity) {
            for (size_t i = 0; i < particles.size(); ++i) {
                for (size_t j = i + 1; j < particles.size(); ++j) {
                    pairRegistry.add(&particles[i], &particles[j], new ParticleMutualGravity(0.005f));
                }
            }
        }
    }
}
