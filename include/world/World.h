#pragma once

#include <vector>
#include "rigid/RigidBody.h"
#include "rigid/RigidBodyContact.h"
#include "collision/CollisionDetector.h"
#include "collision/ContactResolver.h"

namespace tachyon {

// World manages physics bodies and collisions
class World {
private:
    unsigned maxContacts;
    ContactResolver resolver;

    RigidBodyContact* contacts;    // Array of contacts
    unsigned contactsUsed;

public:
    std::vector<RigidBody*> bodies;

    World(unsigned maxContacts = 256, unsigned resolverIterations = 10);
    ~World();

    // Add a new rigid body to the world
    void addBody(RigidBody* body);

    // Run physics update: collision detection, resolution, integration
    void update(real duration);

private:
    // Detect all collisions between bodies
    void generateContacts(real duration);


    // Integrate all bodies
    void integrateBodies(real duration);
};

} // namespace tachyon
