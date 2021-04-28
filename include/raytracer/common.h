
#ifndef RAYTRACING_COMMON_H
#define RAYTRACING_COMMON_H

#include <limits>
#include <cstdlib>

#include "glm/glm.hpp"

namespace RT {

    // Constants
    const float infinity = std::numeric_limits<float>::infinity();
    const float pi = M_PI;

    glm::vec3 InterpolateColor(float dt, glm::vec3 first, glm::vec3 second);

    float Clamp(float value, float min, float max);
    float Clamp01(float value);

    // Returns true if all of the elements of the vector are sufficiently near zero.
    bool NearZero(const glm::vec3& vector);

    float IntegerPower(float value, int power);
}

#endif
