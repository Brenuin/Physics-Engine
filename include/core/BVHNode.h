#pragma once

#include "BoundingSphere.h"
#include "rigid/RigidBody.h"

namespace tachyon {

// Forward declare
struct PotentialContact;

template<class BoundingVolumeClass>
class BVHNode {
public:
    BVHNode* parent;
    BVHNode* children[2];
    BoundingVolumeClass volume;
    RigidBody* body;

    BVHNode();
    ~BVHNode();

    bool isLeaf() const;
    bool overlaps(const BVHNode<BoundingVolumeClass>* other) const;
    unsigned getPotentialContacts(PotentialContact* contacts, unsigned limit) const;
    unsigned getPotentialContactsWith(const BVHNode<BoundingVolumeClass>* other, PotentialContact* contacts, unsigned limit) const;
};

struct PotentialContact {
    RigidBody* body[2];
};

// ---------- IMPLEMENTATIONS ---------- //

template<class BoundingVolumeClass>
BVHNode<BoundingVolumeClass>::BVHNode()
    : parent(nullptr), body(nullptr) {
    children[0] = nullptr;
    children[1] = nullptr;
}

template<class BoundingVolumeClass>
BVHNode<BoundingVolumeClass>::~BVHNode() {
    delete children[0];
    delete children[1];
}

template<class BoundingVolumeClass>
bool BVHNode<BoundingVolumeClass>::isLeaf() const {
    return (body != nullptr);
}

template<class BoundingVolumeClass>
bool BVHNode<BoundingVolumeClass>::overlaps(const BVHNode<BoundingVolumeClass>* other) const {
    return volume.overlaps(&other->volume);
}

template<class BoundingVolumeClass>
unsigned BVHNode<BoundingVolumeClass>::getPotentialContacts(PotentialContact* contacts, unsigned limit) const {
    if (isLeaf() || limit == 0) return 0;

    return children[0]->getPotentialContactsWith(children[1], contacts, limit);
}

template<class BoundingVolumeClass>
unsigned BVHNode<BoundingVolumeClass>::getPotentialContactsWith(
    const BVHNode<BoundingVolumeClass>* other,
    PotentialContact* contacts,
    unsigned limit
) const {
    if (!overlaps(other) || limit == 0) return 0;

    if (isLeaf() && other->isLeaf()) {
        contacts->body[0] = body;
        contacts->body[1] = other->body;
        return 1;
    }

    if (other->isLeaf() || (!isLeaf() && volume.getSize() >= other->volume.getSize())) {
        return children[0]->getPotentialContactsWith(other, contacts, limit) +
               children[1]->getPotentialContactsWith(other, contacts + 1, limit - 1);
    } else {
        return getPotentialContactsWith(other->children[0], contacts, limit) +
               getPotentialContactsWith(other->children[1], contacts + 1, limit - 1);
    }
}

} // namespace tachyon
