
#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include <pch.h>
#include <raytracer/hittable.h>
#include <raytracer/aabb.h>
#include <raytracer/material.h>

namespace RT {

    class Sphere : public IHittable {
        public:
            Sphere(const glm::vec3& centerPosition, float radius, IMaterial* material);
            ~Sphere() override;

            [[nodiscard]] bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            [[nodiscard]] bool GetAABB(AABB& aabb) const override;

        private:
            [[nodiscard]] glm::vec2 CalculateUV(const glm::vec3& intersectionPoint) const;

            glm::vec3 _centerPosition;
            float _radius;

            IMaterial* _material;
            AABB _boundingBox;
    };

}

#endif //RAYTRACING_SPHERE_H
