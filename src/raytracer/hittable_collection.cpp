
#include "hittable_collection.h"

namespace RT {

    HittableCollection::HittableCollection() = default;

    HittableCollection::HittableCollection(std::vector<IHittable*>& objects) : _objects(std::move(objects)) {

    }

    HittableCollection::HittableCollection(IHittable *object) {
        Add(object);
    }

  HittableCollection::~HittableCollection() {
      Clear();
  }

  void HittableCollection::Add(IHittable* object) {
      _objects.push_back(object);
  }

  void HittableCollection::Clear() {
      for (IHittable* object : _objects) {
          delete object;
      }
  }

  const std::vector<IHittable*>& HittableCollection::GetObjects() const {
      return _objects;
  }

  bool HittableCollection::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
      HitRecord tempHitRecord;
      bool hitAnything = false;
      float closestObjectIntersectionTime = tMax;

      // Get the closest object to the origin of the ray that the ray intersects.
      for (const IHittable* object : _objects) {

          // Update hit record data if the ray intersects any object in the scene.
          if (object->Hit(ray, tMin, closestObjectIntersectionTime, tempHitRecord)) {
              hitAnything = true;
              closestObjectIntersectionTime = tempHitRecord.GetIntersectionTime();
              hitRecord = tempHitRecord;
          }
      }

      return hitAnything;
  }

  bool HittableCollection::GetBoundingBox(float tMin, float tMax, AABB& boundingBox) const {
      if (_objects.empty()) {
          return false;
      }

      AABB tempAABB;
      bool firstObject = true;

      // Generate AABB for all the objects in the scene.
      for (const IHittable* object : _objects) {

          if (!object->GetBoundingBox(tMin, tMax, tempAABB)) {
              continue;
          }

          if (firstObject) {
              boundingBox = tempAABB;
              firstObject = false;
          }
          else {
              boundingBox = AABB::Combine(tempAABB, boundingBox);
          }
      }

      return true;
  }

}
