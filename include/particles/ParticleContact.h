#pragma once

#include "core/Vector3.h"
#include "Particle.h"
#include "core/percision.h"

namespace tachyon {
class ParticleContact {
    public:
        Particle* particle[2];
        real restitution;
        real penetration;              // <== ADD THIS LINE
        Vector3 contactNormal;

        void resolve(real duration);
        real calculateSeparatingVelocity() const;
        void resolveInterpenetration(real duration);

    private:
        void resolveVelocity(real duration);
};
}
