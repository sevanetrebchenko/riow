
#include <raytracer/hittable_collection.h>

namespace RT {

    HittableCollection::HittableCollection() = default;
    HittableCollection::~HittableCollection() {
        Clear();
    }

    void HittableCollection::Add(IHittable *object) {
        _collection.push_back(object);
    }

    void HittableCollection::Clear() {
        for (IHittable* object : _collection) {
            delete object;
        }
    }

    bool HittableCollection::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        HitRecord temp;
        bool intersected = false;
        float nearestIntersectionTime = std::numeric_limits<float>::max();

        for (IHittable* object : _collection) {
            if (object->Hit(ray, tMin, nearestIntersectionTime, temp)) {
                intersected = true;
                nearestIntersectionTime = temp.GetIntersectionTime();
            }
        }

        if (intersected) {
            hitRecord = temp;
        }

        return intersected;
    }
}
