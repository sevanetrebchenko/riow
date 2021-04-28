
#include "affine_math.h"
#include "glm/gtx/transform.hpp"
#include "common.h"

namespace RT {

    float LengthSquared(const glm::vec3& vector) {
        return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
    }

    float DistanceSquared(const glm::vec3& first, const glm::vec3& second) {
        return ((second.x - first.x) * (second.x - first.x)) + ((second.y - first.y) * (second.y - first.y)) + ((second.z - first.z) * (second.z - first.z));
    }

    glm::mat4 AffineInverse(const glm::mat4& matrix) {
        // Compute inverse of translation.
        glm::vec3 translation;
        translation.x = -1 * matrix[3][0];
        translation.y = -1 * matrix[3][1];
        translation.z = -1 * matrix[3][2];

        // Compute the inverse of the affine matrix (mat3 instead of mat4).
        glm::mat3 affine(matrix);
        glm::mat4 affineInverse = glm::mat4(glm::inverse(affine));

        // Compute inverse affine transformation
        glm::mat4 translationInverse = glm::mat4(1.0f);
        translationInverse[3][0] = translation.x;
        translationInverse[3][1] = translation.y;
        translationInverse[3][2] = translation.z;
        return affineInverse * translationInverse;
    }

    glm::vec3 RotateAroundX(const glm::vec3& element, float degrees) {
        float radians = glm::radians(degrees);

        glm::vec3 result = element;

        result.y = glm::cos(radians) * element.y - glm::sin(radians) * element.z;
        result.z = glm::sin(radians) * element.y + glm::cos(radians) * element.z;

        return result;
    }

    glm::vec3 RotateAroundY(const glm::vec3& element, float degrees) {
        float radians = glm::radians(degrees);

        glm::vec3 result = element;

        result.x =  glm::cos(radians) * element.x + glm::sin(radians) * element.z;
        result.z = -glm::sin(radians) * element.x + glm::cos(radians) * element.z;

        return result;
    }

    glm::vec3 RotateAroundZ(const glm::vec3& element, float degrees) {
        float radians = glm::radians(degrees);
        glm::vec3 result = element;

        result.x = glm::cos(radians) * element.x - glm::sin(radians) * element.y;
        result.y = glm::sin(radians) * element.x + glm::cos(radians) * element.y;

        return result;
    }

    glm::mat4 RotateAroundX(float degrees) {
        float radians = glm::radians(degrees);
        return glm::rotate(radians, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glm::mat4 RotateAroundY(float degrees) {
        float radians = glm::radians(degrees);
        return glm::rotate(radians, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 RotateAroundZ(float degrees) {
        float radians = glm::radians(degrees);
        return glm::rotate(radians, glm::vec3(0.0f, 0.0f, 1.0f));
    }

}

