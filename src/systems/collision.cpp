#include "systems/collision.h"

namespace tachyon {
    void resolveCollisions(std::vector<Particle>& particles, std::vector<int>& flashFrames, bool flashOnCollision, float timeStep) {
        const unsigned maxContacts = 164;
        ParticleContact contactArray[maxContacts];
        unsigned contactCount = 0;

        for (size_t i = 0; i < particles.size(); ++i) {
            for (size_t j = i + 1; j < particles.size(); ++j) {
                Vector3 posA = particles[i].getPosition();
                Vector3 posB = particles[j].getPosition();
                float radius = particles[i].radius;

                if ((posA - posB).magnitude() < 2 * radius && contactCount < maxContacts) {
                    ParticleContact& contact = contactArray[contactCount++];
                    contact.particle[0] = &particles[i];
                    contact.particle[1] = &particles[j];
                    Vector3 normal = posA - posB;
                    normal.normalize();
                    contact.contactNormal = normal;
                    contact.restitution = 1.0f;
                    contact.penetration = 2 * radius - (posA - posB).magnitude();

                    if (flashOnCollision) {
                        flashFrames[i] = 5;
                        flashFrames[j] = 5;
                    }
                }
            }
        }

        if (contactCount > 0) {
            ParticleContactResolver resolver(10);
            resolver.resolveContacts(contactArray, contactCount, timeStep);
        }
    }
}
