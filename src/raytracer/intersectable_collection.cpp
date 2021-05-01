//
//#include <raytracer/intersectable_collection.h>
//
//namespace RT {
//
//    IntersectableCollection::IntersectableCollection() {
//    }
//
//    IntersectableCollection::~IntersectableCollection() {
//        Clear();
//    }
//
//    void IntersectableCollection::Add(Intersectable *object) {
//        _objects.push_back(object);
//    }
//
//    void IntersectableCollection::Clear() {
//        for (Intersectable* object : _objects) {
//            delete object;
//        }
//    }
//
//    bool IntersectableCollection::Intersect(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
//        HitRecord tempHitRecord;
//        bool hitAnything = false;
//        float closestObjectIntersectionTime = tMax;
//
//        // Get the closest object to the origin of the ray that the ray intersects.
//        for (const Intersectable* object : _objects) {
//
//            // Update hit record data if the ray intersects any object in the scene.
//            if (object->Intersect(ray, tMin, closestObjectIntersectionTime, tempHitRecord)) {
//                hitAnything = true;
//                closestObjectIntersectionTime = tempHitRecord.dt;
//            }
//        }
//
//        hitRecord = tempHitRecord;
//        return hitAnything;
//    }
//}
