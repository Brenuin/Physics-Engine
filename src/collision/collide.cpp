// collide_coarse.cpp

#include "collision/collide.h"

using namespace tachyon;

// BoundingSphere constructors

BoundingSphere::BoundingSphere(const BoundingSphere& one, const BoundingSphere& two) {
    Vector3 centerOffset = two.center - one.center;
    real distance = centerOffset.magnitude();

    if (one.radius >= distance + two.radius) {
        center = one.center;
        radius = one.radius;
    } else if (two.radius >= distance + one.radius) {
        center = two.center;
        radius = two.radius;
    } else {
        real newRadius = (distance + one.radius + two.radius) * 0.5f;
        center = one.center + centerOffset * ((newRadius - one.radius) / distance);
        radius = newRadius;
    }
}

// BoundingSphere overlap check

bool BoundingSphere::overlaps(const BoundingSphere* other) const {
    real distanceSquared = (center - other->center).magnitudeSquared();
    real radiusSum = radius + other->radius;
    return distanceSquared < radiusSum * radiusSum;
}

// BVHNode destructor

template<class BoundingVolumeClass>
tachyon::BVHNode<BoundingVolumeClass>::~BVHNode() {
    if (parent) {
        // Find sibling
        BVHNode<BoundingVolumeClass>* sibling;
        if (parent->children[0] == this) {
            sibling = parent->children[1];
        } else {
            sibling = parent->children[0];
        }

        // Move sibling into parent
        parent->volume = sibling->volume;
        parent->body = sibling->body;
        parent->children[0] = sibling->children[0];
        parent->children[1] = sibling->children[1];

        if (sibling->children[0]) sibling->children[0]->parent = parent;
        if (sibling->children[1]) sibling->children[1]->parent = parent;

        // Clean sibling
        sibling->parent = nullptr;
        sibling->body = nullptr;
        sibling->children[0] = nullptr;
        sibling->children[1] = nullptr;
        delete sibling;

        // Recalculate parent's bounding volume
        parent->recalculateBoundingVolume();
    }

    if (children[0]) {
        children[0]->parent = nullptr;
        delete children[0];
    }
    if (children[1]) {
        children[1]->parent = nullptr;
        delete children[1];
    }
}
