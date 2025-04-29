#include <iostream>
#include "rigid/RigidBody.h"
#include "core/BoundingSphere.h"
#include "core/BVHNode.h"
#include "collision/CollisionDetector.h"
#include "rigid/RigidBodyContact.h"
#include "collision/ContactResolver.h"

using namespace tachyon;

int main() {
    // --- Setup two rigid bodies ---
    RigidBody bodyA;
    RigidBody bodyB;

    // Setup bodyA
    bodyA.position = Vector3(0.0f, 0.0f, 0.0f);
    bodyA.velocity = Vector3(1.0f, 0.0f, 0.0f); // Moving right
    bodyA.inverseMass = 1.0f; // mass = 1
    bodyA.linearDamping = 1.0f;
    bodyA.angularDamping = 1.0f;
    bodyA.isAwake = true; // 🔥 Important!

    // Setup bodyB
    bodyB.position = Vector3(1.5f, 0.0f, 0.0f);
    bodyB.velocity = Vector3(-1.0f, 0.0f, 0.0f); // Moving left
    bodyB.inverseMass = 1.0f; // mass = 1
    bodyB.linearDamping = 1.0f;
    bodyB.angularDamping = 1.0f;
    bodyB.isAwake = true; // 🔥 Important!  

    // Create bounding spheres
    BoundingSphere sphereA(bodyA.position, 1.0f);
    BoundingSphere sphereB(bodyB.position, 1.0f);

    // --- Print starting positions ---
    std::cout << "Before collision:" << std::endl;
    std::cout << "Body A Position: (" << bodyA.position.x << ", " << bodyA.position.y << ", " << bodyA.position.z << ")" << std::endl;
    std::cout << "Body B Position: (" << bodyB.position.x << ", " << bodyB.position.y << ", " << bodyB.position.z << ")" << std::endl;

    // --- Detect collision ---
    RigidBodyContact contact;
    unsigned contactsGenerated = CollisionDetector::sphereAndSphere(
        &bodyA, sphereA.radius,
        &bodyB, sphereB.radius,
        &contact,
        1 // Only space for 1 contact
    );

    if (contactsGenerated > 0) {
        std::cout << "\nCollision detected!" << std::endl;

        // Resolve collision
        ContactResolver resolver(10); // 1 iteration
        real duration = 0.016f;       // Simulate ~60 FPS timestep
        resolver.resolveContacts(&contact, 1, duration);


        // 🔥🔥🔥 Integrate bodies after collision resolution 🔥🔥🔥
        bodyA.integrate(duration);
        bodyB.integrate(duration);
    } else {
        std::cout << "\nNo collision detected." << std::endl;
    }

    // --- Print updated positions ---
    std::cout << "\nAfter collision resolution:" << std::endl;
    std::cout << "Body A Position: (" << bodyA.position.x << ", " << bodyA.position.y << ", " << bodyA.position.z << ")" << std::endl;
    std::cout << "Body B Position: (" << bodyB.position.x << ", " << bodyB.position.y << ", " << bodyB.position.z << ")" << std::endl;

    return 0;
}
