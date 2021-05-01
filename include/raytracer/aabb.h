
#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#include <raytracer/mesh.h>
#include <raytracer/transform.h>
#include <raytracer/ray.h>

namespace RT {

    struct AABB {
        AABB(const glm::vec3 &minimum = glm::vec3(std::numeric_limits<float>::max()), const glm::vec3 &maximum = glm::vec3(std::numeric_limits<float>::lowest()));
        AABB(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
        ~AABB();

        [[nodiscard]] glm::vec3 GetCenter() const;
        [[nodiscard]] bool Hit(const Ray& ray, float tMin, float tMax) const;

        glm::vec3 minimum;
        glm::vec3 maximum;
    };

    // Combine two AABBs.
    AABB Combine(const AABB& first, const AABB& second);

    // Get AABB from a set of vertices.
    AABB GetAABB(const std::vector<glm::vec3>& vertices);
//    AABB GetAABB(const std::vector<Triangle>& triangles);

}

#endif //RAYTRACER_AABB_H
