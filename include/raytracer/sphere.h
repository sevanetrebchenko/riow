
#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include <pch.h>
#include <raytracer/intersectable.h>

namespace RT {

    class Sphere : public Intersectable {
        public:
            Sphere(const glm::vec3& position, const glm::vec3 rotation, float radius, IMaterial* material);
            ~Sphere() override;

            bool Intersect(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

        private:
            void ConstructBoundingBox();
            glm::vec2 CalculateUV(const glm::vec3& intersectionPoint) const;
    };

}

#endif //RAYTRACING_SPHERE_H
