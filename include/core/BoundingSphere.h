#pragma once

#include "Vector3.h"
#include "percision.h"

namespace tachyon {

class BoundingSphere {
public:
    Vector3 center;
    real radius;

    BoundingSphere() : center(), radius(1.0f) {}

    BoundingSphere(const Vector3& center, real radius)
        : center(center), radius(radius) {}

    BoundingSphere(const BoundingSphere& one, const BoundingSphere& two) {
        merge(one, two);
    }

    // Check if two spheres overlap
    bool overlaps(const BoundingSphere* other) const {
        Vector3 diff = center - other->center;
        real distanceSquared = diff.magnitudeSquared();
        real radiusSum = radius + other->radius;
        return distanceSquared < radiusSum * radiusSum;
    }

    // Calculate new bounding sphere that encloses two spheres
    void merge(const BoundingSphere& one, const BoundingSphere& two) {
        Vector3 centerOffset = two.center - one.center;
        real distanceSquared = centerOffset.magnitudeSquared();
        real radiusDiff = two.radius - one.radius;

        // Check if one completely contains the other
        if (radiusDiff * radiusDiff >= distanceSquared) {
            if (one.radius > two.radius) {
                center = one.center;
                radius = one.radius;
            } else {
                center = two.center;
                radius = two.radius;
            }
            return;
        }

        // Otherwise, compute new sphere
        real distance = real_sqrt(distanceSquared);
        radius = (distance + one.radius + two.radius) * ((real)0.5);

        if (distance > 0) {
            center = one.center + centerOffset * ((radius - one.radius) / distance);
        } else {
            center = one.center;
        }
    }

    // Return approximate "size" (for BVHNode decisions)
    real getSize() const {
        return radius;
    }
};

} // namespace tachyon
