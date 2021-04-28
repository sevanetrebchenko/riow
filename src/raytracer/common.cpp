
#include <cmath>
#include "common.h"

namespace RT {

    glm::vec3 InterpolateColor(float dt, glm::vec3 first, glm::vec3 second) {
        return (1.0f - dt) * first + dt * second;
    }

    float Clamp(float value, float min, float max) {
        if (value < min) {
            return min;
        }
        if (value > max) {
            return max;
        }

        return value;
    }

    float Clamp01(float value) {
        return Clamp(value, 0.0f, 1.0f);
    }

    bool NearZero(const glm::vec3& vector) {
        return fabs(vector.x) < std::numeric_limits<float>::epsilon() &&
               fabs(vector.y) < std::numeric_limits<float>::epsilon() &&
               fabs(vector.z) < std::numeric_limits<float>::epsilon();
    }

    float IntegerPower(float value, int power) {
        if (power == 0) {
            return 1.0f;
        }

        float result = value;

        while (power-- != 0) {
            result *= value;
        }

        return result;
    }

}
