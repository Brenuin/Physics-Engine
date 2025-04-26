#pragma once
#include <vector>
#include "particles/particle.h"

void initializeParticles(std::vector<tachyon::Particle>& particles,
                         std::vector<int>& flashFrames,
                         int boxSize,
                         bool enableRandomVelocity);
