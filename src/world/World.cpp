#include "world/World.h"
#include <cassert>

namespace tachyon {

World::World(unsigned maxContacts, unsigned resolverIterations)
    : maxContacts(maxContacts), resolver(resolverIterations)
{
    contacts = new RigidBodyContact[maxContacts];
    contactsUsed = 0;
}

World::~World() {
    delete[] contacts;
}

void World::addBody(RigidBody* body) {
    bodies.push_back(body);
}

void World::update(real duration) {
    // Reset contacts
    contactsUsed = 0;

    // Generate contacts
    generateContacts();

    // Resolve contacts
    if (contactsUsed > 0) {
        resolver.resolveContacts(contacts, contactsUsed, duration);
    }

    // Integrate motion
    integrateBodies(duration);
}

void World::generateContacts() {
    contactsUsed = 0;

    // Simple all-pairs collision check
    for (unsigned i = 0; i < bodies.size(); ++i) {
        for (unsigned j = i + 1; j < bodies.size(); ++j) {
            if (contactsUsed >= maxContacts) return;

            RigidBody* bodyA = bodies[i];
            RigidBody* bodyB = bodies[j];

            // For now: assume sphere bounding volumes
            BoundingSphere sphereA(bodyA->position, 1.0f);
            BoundingSphere sphereB(bodyB->position, 1.0f);


            contactsUsed += CollisionDetector::sphereAndSphere(
                bodyA, sphereA.radius,
                bodyB, sphereB.radius,
                &contacts[contactsUsed],
                maxContacts - contactsUsed
            );
        }
    }
}

void World::integrateBodies(real duration) {
    for (RigidBody* body : bodies) {
        if (body->isAwake) {
            body->integrate(duration);
        }
    }
}

} // namespace tachyon
