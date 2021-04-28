
#ifndef RAYTRACING_HITTABLE_H
#define RAYTRACING_HITTABLE_H

#include "ray.h"
#include "hit_record.h"
#include "aabb.h"
#include "transform.h"

namespace RT {

    // Interface for all intersectable objects in the scene.
    class IHittable {
        public:
            virtual ~IHittable();
            virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const = 0;
            virtual bool GetBoundingBox(float tMin, float tMax, AABB& boundingBox) const = 0;

        protected:
            void TransformRay(const Transform& transform, Ray& ray) const;
            void UndoTransform(const Transform& transform, const Ray& ray, HitRecord& hitRecord) const;
    };

}

#endif //RAYTRACING_HITTABLE_H
