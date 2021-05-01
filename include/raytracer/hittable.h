#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <raytracer/ray.h>
#include <raytracer/hit_record.h>

namespace RT {

    class IHittable {
        public:
            virtual ~IHittable();
            virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const = 0;
    };

}

#endif //RAYTRACER_HITTABLE_H
