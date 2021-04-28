
#ifndef RAYTRACING_RANDOM_H
#define RAYTRACING_RANDOM_H

#include "glm/glm.hpp"

namespace RT {

    // Returns random number in range: [0, 1)
    float RandomFloat();

    // Returns random number in range: [min, max)
    float RandomFloat(float min, float max);

    // Returns random vec3 with all values in range: [0, 1)
    glm::vec3 RandomVec3();

    // Returns random vec3 with all values in range: [min, max)
    glm::vec3 RandomVec3(float min, float max);

    glm::vec3 RandomVec3InUnitSphere();
    glm::vec3 RandomVec3InUnitDisk();
}

#endif //RAYTRACING_RANDOM_H
