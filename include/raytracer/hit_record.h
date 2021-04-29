
#ifndef RAYTRACER_HIT_RECORD_H
#define RAYTRACER_HIT_RECORD_H

#include <pch.h>
#include <raytracer/ray.h>

namespace RT {

    // Forward declaration.
    class IMaterial;

    struct HitRecord {
        HitRecord();

        void SetNormal(const Ray& ray, const glm::vec3& normal);

        bool outwardFacing;
        IMaterial* material;
        float dt;
        glm::vec3 point;
        glm::vec3 normal;
        glm::vec2 uv;
    };

}

#endif //RAYTRACER_HIT_RECORD_H
