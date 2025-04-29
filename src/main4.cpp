#include "world/World.h"
#include "render/Renderer.h"
#include "rigid/RigidBody.h"

using namespace tachyon;

int main() {
    World world(256, 10);
    Renderer renderer;

    // Create bodies...
    RigidBody* bodyA = new RigidBody();
    bodyA->position = Vector3(0.0f, 0.0f, 0.0f);
    bodyA->velocity = Vector3(1.0f, 0.0f, 0.0f);
    bodyA->inverseMass = 1.0f;
    bodyA->isAwake = true;
    bodyA->boundingRadius = 1.0f;
    bodyA->acceleration = Vector3(0.0f, -9.8f, 0.0f);
    world.addBody(bodyA);

    RigidBody* bodyB = new RigidBody();
    bodyB->position = Vector3(1.5f, 0.0f, 0.0f);
    bodyB->velocity = Vector3(-1.0f, 0.0f, 0.0f);
    bodyB->inverseMass = 1.0f;
    bodyB->isAwake = true;
    bodyB->boundingRadius = 1.0f;
    bodyB->acceleration = Vector3(0.0f, -9.8f, 0.0f);
    world.addBody(bodyB);

    real duration = 0.016f; // 60 FPS

    // 🚀 Main simulation loop
    for (int frame = 0; frame < 300; ++frame) {  // Simulate ~5 seconds
        world.update(duration);
        renderer.render(world);
    }

    return 0;
}
