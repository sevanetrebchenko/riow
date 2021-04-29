
#ifndef RAYTRACER_INTERSECTABLE_H
#define RAYTRACER_INTERSECTABLE_H

#include <raytracer/ray.h>
#include <raytracer/hit_record.h>
#include <raytracer/aabb.h>
#include <raytracer/transform.h>

namespace RT {

    class Intersectable {
        public:
            Intersectable(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, IMaterial* material);
            Intersectable(const Transform& transform, IMaterial* material);
            virtual ~Intersectable();

            [[nodiscard]] virtual bool Intersect(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const = 0;
            [[nodiscard]] const AABB& GetBoundingBox() const;

        protected:
            AABB _aabb;
            Transform _transform;
            IMaterial* _material;
    };

}

#endif //RAYTRACER_INTERSECTABLE_H
