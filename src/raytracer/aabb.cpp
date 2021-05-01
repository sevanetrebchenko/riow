
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

    AABB::AABB(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) {
        std::vector<glm::vec3> vertices;

        // [-0.5, 0.5] centered at (0, 0, 0)
        vertices.emplace_back(-0.5f, -0.5f, -0.5f);
        vertices.emplace_back(-0.5f, -0.5f, 0.5f);
        vertices.emplace_back(-0.5f, 0.5f, -0.5f);
        vertices.emplace_back(-0.5f, 0.5f, 0.5f);
        vertices.emplace_back(0.5f, -0.5f, -0.5f);
        vertices.emplace_back(0.5f, -0.5f, 0.5f);
        vertices.emplace_back(0.5f, 0.5f, -0.5f);
        vertices.emplace_back(0.5f, 0.5f, 0.5f);

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 scaleMatrix = glm::scale(scale);
        glm::mat4 rotationXMatrix = glm::rotate(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotationYMatrix = glm::rotate(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotationZMatrix = glm::rotate(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 transform = translationMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * scaleMatrix;

        // Transform vertices.
        for (glm::vec3& vertex : vertices) {
            vertex = transform * glm::vec4(vertex, 1.0f);
        }

        // Get the min/max of transformed vertices.
        maximum = glm::vec3(std::numeric_limits<float>::lowest());
        minimum = glm::vec3(std::numeric_limits<float>::max());
        for (const glm::vec3& vertex : vertices) {
            MinMaxVertex(vertex, minimum, maximum);
        }
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

//    AABB GetAABB(const std::vector<Triangle>& triangles) {
//        glm::vec3 minimum(std::numeric_limits<float>::max());
//        glm::vec3 maximum(std::numeric_limits<float>::lowest());
//
//        for (const Triangle& triangle : triangles) {
//            for (const glm::vec3& vertex : triangle.GetVertices()) {
//                MinMaxVertex(vertex, minimum, maximum);
//            }
//        }
//
//        return AABB(minimum, maximum);
//    }

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
