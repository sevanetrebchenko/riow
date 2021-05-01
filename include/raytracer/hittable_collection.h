
#ifndef RAYTRACER_HITTABLE_COLLECTION_H
#define RAYTRACER_HITTABLE_COLLECTION_H

#include <raytracer/hittable.h>

namespace RT {

    class HittableCollection : public IHittable {
        public:
            HittableCollection();
            ~HittableCollection();

            void Add(IHittable* object);
            void Clear();

            [[nodiscard]] bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

        private:
            std::vector<IHittable*> _collection;
    };

}

#endif //RAYTRACER_HITTABLE_COLLECTION_H
