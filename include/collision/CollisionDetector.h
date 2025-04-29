#pragma once

#include "rigid/RigidBody.h"
#include "core/BoundingSphere.h"
#include "rigid/RigidBodyContact.h"
#include "core/percision.h"

namespace tachyon {

class CollisionDetector {
public:
    static unsigned sphereAndSphere(
        RigidBody* one, real radiusOne,
        RigidBody* two, real radiusTwo,
        RigidBodyContact* contact,
        unsigned limit
    ) {
        if (limit == 0) return 0;

        Vector3 midline = two->position - one->position;
        real size = midline.magnitude();

        if (size <= 0.0f || size >= radiusOne + radiusTwo) {
            return 0;
        }

        Vector3 normal = midline * (((real)1.0) / size);

        contact->contactNormal = normal;
        contact->contactPoint = one->position + midline * 0.5f;
        contact->penetration = (radiusOne + radiusTwo) - size;
        contact->body[0] = one;
        contact->body[1] = two;
        contact->restitution = 0.7f; // 🔥 ADD THIS LINE

        return 1;
    }
};

} // namespace tachyon
