#include "systems/init_constraints.h"

namespace tachyon {

    void initializeConstraints(
        std::vector<Particle>& particles,
        std::vector<ParticleCable>& cables,
        std::vector<ParticleRod>& rods,
        bool useCables,
        bool useRods,
        int gridSize,
        float spacing
    ) {
        // Create particles if none exist
        if (particles.empty()) {
            for (int y = 0; y < gridSize; ++y) {
                for (int x = 0; x < gridSize; ++x) {
                    Particle p;
                    p.setPosition(Vector3(x * spacing, y * spacing, 0.0f));
                    p.setVelocity(Vector3(0, 0, 0));
                    p.setDamping(0.99f);
                    p.setMass(1.0f);
                    particles.push_back(p);
                }
            }
        }

        // Add constraints between those particles
        for (int i = 0; i < particles.size(); ++i) {
            int row = i / gridSize;
            int col = i % gridSize;

            // Horizontal rod
            if (useRods && col < gridSize - 1) {
                ParticleRod rod;
                rod.particle[0] = &particles[i];
                rod.particle[1] = &particles[i + 1];
                rod.length = spacing;
                rods.push_back(rod);
            }

            // Vertical cable
            if (useCables && row < gridSize - 1) {
                ParticleCable cable;
                cable.particle[0] = &particles[i];
                cable.particle[1] = &particles[i + gridSize];
                cable.maxLength = spacing * 1.1f;
                cable.restitution = 0.3f;
                cables.push_back(cable);
            }
        }
    }

}
