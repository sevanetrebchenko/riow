
#ifndef RAYTRACER_UTILITY_MATH_H
#define RAYTRACER_UTILITY_MATH_H

#include <pch.h>
#include <raytracer/mesh.h>

namespace RT {

    void MinMaxVertex(const glm::vec3& vertex, glm::vec3& minimum, glm::vec3& maximum);

    float SignedDistancePointPlane(const glm::vec3 &point, const glm::vec4 &plane);

    enum class PointClassification {
        POINT_IN_FRONT_OF_PLANE,
        POINT_BEHIND_PLANE,
        POINT_ON_PLANE
    };

    enum class TriangleClassification {
        TRIANGLE_IN_FRONT_OF_PLANE,
        TRIANGLE_BEHIND_PLANE,
        TRIANGLE_STRADDLING_PLANE,
        TRIANGLE_COPLANAR_WITH_PLANE
    };

    PointClassification ClassifyPointToPlane(const glm::vec3& point, const glm::vec4& plane);
    TriangleClassification ClassifyTriangleToPlane(const Triangle& triangle, const glm::vec4& plane);

    template <typename T>
    T lerp(const T& first, const T& second, float t) {
        return first * t + second * (1.0f - t);
    }

    float IntegerPower(float value, int power);

    // Random utility functions.
    glm::vec3 RandomDirection(float min, float max);
    glm::vec3 RandomDirectionInUnitSphere();
    glm::vec3 RandomDirectionInHemisphere(const glm::vec3& rayDirection);

    float LengthSquared(const glm::vec3& vector);
    float DistanceSquared(const glm::vec3& first, const glm::vec3& second);

    glm::mat4 AffineInverse(const glm::mat4& matrix);

    glm::vec3 RotateAroundX(const glm::vec3& element, float degrees);
    glm::vec3 RotateAroundY(const glm::vec3& element, float degrees);
    glm::vec3 RotateAroundZ(const glm::vec3& element, float degrees);

    glm::mat4 RotateAroundX(float degrees);
    glm::mat4 RotateAroundY(float degrees);
    glm::mat4 RotateAroundZ(float degrees);

}

#endif //RAYTRACER_UTILITY_MATH_H