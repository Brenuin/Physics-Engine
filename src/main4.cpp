#include <GLFW/glfw3.h>
#include "world/World.h"
#include "render/Renderer.h"
#include "systems/BoundingBoxCollider.h"
#include "systems/BallSpawner.h"

using namespace tachyon;

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1200, 900, "RigidBody World", NULL, NULL);
    BoundingBoxCollider bounds(1200, 900, 30.0f);

    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    World world(256, 50);

    BallSpawner2D spawner(30.0f, 22.5f, 0.5f, 5.0f, 10.0f, 500.0f);  // width, height, minR, maxR, minV, maxV
    std::vector<RigidBody*> balls = spawner.spawnBalls(20);
    for (RigidBody* b : balls) {
        world.addBody(b);
    }

    Renderer renderer(1200, 900, 30.0f);
    renderer.setCameraOffset(Vector3(0, 0, 0));

    const real duration = 0.0008f;

    while (!glfwWindowShouldClose(window)) {
        world.update(duration);
        bounds.constrainBodies(world.bodies);
        renderer.beginFrame();
        renderer.renderWorld(world.bodies);
        renderer.endFrame(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
