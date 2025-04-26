#include "constraints/ParticleRod.h"
#include "particles/ParticleContact.h"
#include "core/Vector3.h"

namespace tachyon {

unsigned ParticleRod::fillContact(ParticleContact* contact, unsigned limit) const {
    real currentLen = currentLength();
    if (currentLen == length) return 0;

    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
    normal.normalize();

    if (currentLen > length) {
        contact->contactNormal = normal;
        contact->penetration = currentLen - length;
    } else {
        contact->contactNormal = normal * -1;
        contact->penetration = length - currentLen;
    }

    contact->restitution = 0;
    return 1;
}
ParticleRod::~ParticleRod() = default;

}
