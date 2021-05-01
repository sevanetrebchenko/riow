
#include <raytracer/hittable_collection.h>
#include <raytracer/bvh.h>

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
        float nearestIntersectionTime = tMax;

        // Intersect with all objects to get the nearest intersection.
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

    bool HittableCollection::GetAABB(AABB &aabb) const {
        if (_collection.empty()) {
            return false;
        }

        AABB temp;
        bool first = true;

        // Combine the bounding boxes for all objects.
        for (IHittable* object : _collection) {
            if (!object->GetAABB(temp)) {
                return false;
            }
            aabb = first ? temp : Combine(aabb, temp);
            first = false;
        }

        return true;
    }

    void HittableCollection::BuildBVH() {
        BVHNode* node = new BVHNode(_collection, 0, _collection.size());
        _collection.clear();
        _collection.push_back(node);
    }
}
