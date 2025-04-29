#include "collision/ContactResolver.h"

namespace tachyon {

    void ContactResolver::resolveContacts(RigidBodyContact* contactArray, unsigned numContacts, real duration) {
        iterationsUsed = 0;
        while (iterationsUsed < iterations && iterationsUsed < numContacts) {
            contactArray[iterationsUsed].resolve(duration);
            ++iterationsUsed;
        }
    }
    

} // namespace tachyon
