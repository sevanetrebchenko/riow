
#include "random.h"
#include "common.h"
#include "affine_math.h"

namespace RT {

    float RandomFloat() {
        return rand() / (RAND_MAX + 1.0f);
    }

    float RandomFloat(float min, float max) {
        return min + (max - min) * RandomFloat();
    }

    glm::vec3 RandomVec3() {
        return glm::vec3(RandomFloat(), RandomFloat(), RandomFloat());
    }

    glm::vec3 RandomVec3(float min, float max) {
        return glm::vec3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
    }

    glm::vec3 RandomVec3InUnitSphere() {
        while (true) {
            // Rejection method: Pick a point in the unit cube where x, y, and z
            // fall within the range [-1.0f, 1.0f] and reject the point if it
            // falls outside the unit circle.
            glm::vec3 vector = RandomVec3(-1.0f, 1.0f);

            // Candidate vector falls outside the unit circle.
            if (LengthSquared(vector) >= 1.0f) {
                continue;
            }

            return vector;
        }
    }

    glm::vec3 RandomVec3InUnitDisk() {
        while (true) {
            // Rejection method: Pick a point in the unit cube where x, y, and z
            // fall within the range [-1.0f, 1.0f] and reject the point if it
            // falls outside the unit circle.
            glm::vec3 vector(RandomFloat(), RandomFloat(), 0.0f);

            // Candidate vector falls outside the unit circle.
            if (LengthSquared(vector) >= 1.0f) {
                continue;
            }

            return vector;
        }
    }

}
