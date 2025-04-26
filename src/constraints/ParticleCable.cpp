#include "constraints/ParticleCable.h"
#include "particles/ParticleContact.h"
#include "core/Vector3.h"

namespace tachyon {

real ParticleLink::currentLength() const {
    Vector3 relativePos = particle[0]->getPosition() - particle[1]->getPosition();
    return relativePos.magnitude();
}

unsigned ParticleCable::fillContact(ParticleContact* contact, unsigned limit) const {
    real length = currentLength();
    if (length < maxLength) return 0;

    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];
    Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
    normal.normalize();
    contact->contactNormal = normal;
    contact->penetration = length - maxLength;
    contact->restitution = restitution;
    return 1;
}
ParticleCable::~ParticleCable() = default;

}
