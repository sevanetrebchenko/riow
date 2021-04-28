
#ifndef RAYTRACING_HITTABLE_COLLECTION_H
#define RAYTRACING_HITTABLE_COLLECTION_H

#include <vector>
#include "glm/glm.hpp"
#include "hittable.h"
#include "hit_record.h"
#include "ray.h"

namespace RT {

    class HittableCollection : public IHittable {
        public:
            HittableCollection();
            HittableCollection(std::vector<IHittable*>& objects);
            HittableCollection(IHittable* object);
            ~HittableCollection();

            void Add(IHittable* object);
            void Clear();

            const std::vector<IHittable*>& GetObjects() const;

            bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            bool GetBoundingBox(float tMin, float tMax, AABB& boundingBox) const override;

        private:
            std::vector<IHittable*> _objects;
    };

}

#endif //RAYTRACING_HITTABLE_COLLECTION_H
