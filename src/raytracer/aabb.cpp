
#include <raytracer/aabb.h>
#include <raytracer/utility_math.h>

namespace RT {

    AABB::AABB(const glm::vec3 &minimum, const glm::vec3 &maximum) : minimum(minimum),
                                                                     maximum(maximum)
                                                                     {
    }

    AABB::~AABB() = default;

    glm::vec3 AABB::GetCenter() const {
        return (minimum + maximum) / 2.0f;
    }

    AABB Combine(const AABB &aabb1, const AABB &aabb2) {
        glm::vec3 minimum = glm::min(aabb1.minimum, aabb2.minimum);
        glm::vec3 maximum = glm::max(aabb1.maximum, aabb2.maximum);

        return AABB(minimum, maximum);
    }

    AABB GetAABB(const std::vector<glm::vec3>& vertices) {
        glm::vec3 minimum(std::numeric_limits<float>::max());
        glm::vec3 maximum(std::numeric_limits<float>::lowest());

        for (const glm::vec3& vertex : vertices) {
            MinMaxVertex(vertex, minimum, maximum);
        }

        return AABB(minimum, maximum);
    }

    AABB GetAABB(const std::vector<Triangle>& triangles) {
        glm::vec3 minimum(std::numeric_limits<float>::max());
        glm::vec3 maximum(std::numeric_limits<float>::lowest());

        for (const Triangle& triangle : triangles) {
            for (const glm::vec3& vertex : triangle.GetVertices()) {
                MinMaxVertex(vertex, minimum, maximum);
            }
        }

        return AABB(minimum, maximum);
    }

    //     // Intersection test in an AABB is detection if the interval at which the ray intersects the
    //    // bounding box axes intersects on more than one axis.
    //    bool AABB::Hit(const Ray& ray, float tMin, float tMax) const {
    //        float intersectionIntervalStart = tMin;
    //        float intersectionIntervalEnd = tMax;
    //
    //        const glm::vec3& rayOrigin = ray.GetOrigin();
    //        const glm::vec3& rayDirection = ray.GetDirection();
    //
    //        // Traverse each axis.
    //        for (int axis = 0; axis < 3; ++axis) {
    //            // Given a position x0 such that the ray Ax + tBx intersects position x0 at t0, get t0.
    //            // x0 = Ax + t0Bx
    //            // t0 = (x0 - Ax) / Bx
    //            float axisIntersectionIntervalStart = (_minimumCorner[axis] - rayOrigin[axis]) / rayDirection[axis];
    //            float axisIntersectionIntervalEnd = (_maximumCorner[axis] - rayOrigin[axis]) / rayDirection[axis];
    //
    //            if (1.0f / rayDirection[axis] < 0.0f) {
    //                std::swap(axisIntersectionIntervalStart, axisIntersectionIntervalEnd);
    //            }
    //
    //            // Get the smallest time the ray intersects out of all axes.
    //            intersectionIntervalStart = std::fmax(axisIntersectionIntervalStart, intersectionIntervalStart);
    //            intersectionIntervalEnd = std::fmin(axisIntersectionIntervalEnd, intersectionIntervalEnd);
    //
    //            if (intersectionIntervalEnd <= intersectionIntervalStart) {
    //                return false;
    //            }
    //        }
    //
    //        return true;
    //    }


}
