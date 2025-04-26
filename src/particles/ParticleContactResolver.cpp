#include "particles/ParticleContactResolver.h"

using namespace tachyon;

ParticleContactResolver::ParticleContactResolver(unsigned iterations)
    : iterations(iterations), iterationsUsed(0) {}

void ParticleContactResolver::setIterations(unsigned newIterations) {
    iterations = newIterations;
}

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned numContacts, float duration) {
    iterationsUsed = 0;

    while (iterationsUsed < iterations) {
        float max = 0;
        unsigned maxIndex = numContacts;

        for (unsigned i = 0; i < numContacts; i++) {
            float sepVel = contactArray[i].calculateSeparatingVelocity();
            if (sepVel < max) {
                max = sepVel;
                maxIndex = i;
            }
        }

        if (maxIndex == numContacts) break;

        contactArray[maxIndex].resolve(duration);
        iterationsUsed++;
    }
}
