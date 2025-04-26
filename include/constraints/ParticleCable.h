#pragma once
#include "ParticleLink.h"
#include "core/percision.h"
namespace tachyon {
class ParticleCable : public ParticleLink {
public:
    real maxLength;
    real restitution;

    virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const;
    virtual ~ParticleCable();

};
}