#include "collision/ContactResolver.h"
#include <algorithm>
#include <limits>

namespace tachyon {

void ContactResolver::resolveContacts(RigidBodyContact* contactArray, unsigned numContacts, real duration) {
    iterationsUsed = 0;

    if (numContacts == 0) return;

    while (iterationsUsed < iterations) {
        real maxVelocity = -std::numeric_limits<real>::lowest();
        unsigned maxIndex = numContacts;

        for (unsigned i = 0; i < numContacts; ++i) {
            // Skip already resolved contacts
            if (contactArray[i].penetration <= 0 && contactArray[i].contactVelocity.x >= 0) continue;

            real sepVel = contactArray[i].contactVelocity.x;

            if (sepVel < maxVelocity && (contactArray[i].penetration > 0 || sepVel < 0)) {
                maxVelocity = sepVel;
                maxIndex = i;
            }
        }

        if (maxIndex == numContacts) break; // No contacts need resolving

        contactArray[maxIndex].resolve(duration);

        // 🔒 Stop infinite loop by zeroing out penetration
        contactArray[maxIndex].penetration = 0;

        ++iterationsUsed;
    }
}

} // namespace tachyon
