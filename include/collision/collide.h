// collide_coarse.h

#pragma once
#include "core/Vector3.h"
#include "rigid/RigidBody.h"

namespace tachyon {

// Represents a possible contact between two rigid bodies
struct PotentialContact {
    RigidBody* body[2];
};

// Bounding Sphere for broad-phase collision detection
struct BoundingSphere {
    Vector3 center;
    real radius;

    BoundingSphere(const Vector3& center, real radius)
        : center(center), radius(radius) {}

    BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);

    bool overlaps(const BoundingSphere* other) const;
};

// Bounding Volume Hierarchy Node
template<class BoundingVolumeClass>
class BVHNode {
public:
    BVHNode* parent;
    BVHNode* children[2];
    BoundingVolumeClass volume;
    RigidBody* body;

    BVHNode()
        : parent(nullptr), body(nullptr) {
        children[0] = nullptr;
        children[1] = nullptr;
    }

    ~BVHNode();

    bool isLeaf() const {
        return body != nullptr;
    }

    bool overlaps(const BVHNode* other) const {
        return volume.overlaps(&other->volume);
    }

    unsigned getPotentialContacts(PotentialContact* contacts, unsigned limit) const {
        if (isLeaf() || limit == 0) return 0;
        return children[0]->getPotentialContactsWith(children[1], contacts, limit);
    }

    unsigned getPotentialContactsWith(const BVHNode* other, PotentialContact* contacts, unsigned limit) const {
        if (!overlaps(other) || limit == 0) return 0;

        if (isLeaf() && other->isLeaf()) {
            contacts->body[0] = body;
            contacts->body[1] = other->body;
            return 1;
        }

        if (other->isLeaf() || (!isLeaf() && volume.getSize() >= other->volume.getSize())) {
            unsigned count = children[0]->getPotentialContactsWith(other, contacts, limit);
            if (limit > count) {
                return count + children[1]->getPotentialContactsWith(other, contacts + count, limit - count);
            }
            return count;
        } else {
            unsigned count = getPotentialContactsWith(other->children[0], contacts, limit);
            if (limit > count) {
                return count + getPotentialContactsWith(other->children[1], contacts + count, limit - count);
            }
            return count;
        }
    }
};

} // namespace tachyon
