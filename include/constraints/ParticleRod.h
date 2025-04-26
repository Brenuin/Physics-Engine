#pragma once
#include "ParticleLink.h"
namespace tachyon {
class ParticleRod : public ParticleLink {
public:
    real length;

    virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const;
    virtual ~ParticleRod();

};
}