#pragma once
#include "particles/Particle.h"
#include "particles/ParticleContact.h"
#include "core/percision.h"

namespace tachyon {

    class ParticleLink {
    public:
        Particle* particle[2];
    protected:
        real currentLength() const;
    public:
        virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const = 0;
    };
    
    } // namespace tachyon
    