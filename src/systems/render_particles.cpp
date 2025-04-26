#include "systems/render_particles.h"
#include <GL/gl.h>

namespace tachyon {
    void renderParticles(const std::vector<Particle>& particles, const std::vector<int>& flashFrames, bool flashOnCollision, GLFWwindow* window, float pointSize) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -100.0f);

        glBegin(GL_POINTS);
        for (size_t i = 0; i < particles.size(); ++i) {
            const Vector3& pos = particles[i].getPosition();
            if (flashOnCollision && flashFrames[i] > 0) {
                glColor3f(1.0f, 0.2f, 0.2f);
            } else {
                glColor3f(0.6f, 0.9f, 1.0f);
            }
            glPointSize(pointSize);
            glVertex3f(pos.x, pos.y, pos.z);
        }
        glEnd();

        glFlush();
        glfwSwapBuffers(window);
    }
}
