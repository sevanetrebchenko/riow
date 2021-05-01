//
//#ifndef RAYTRACING_INTERSECTABLE_COLLECTION_H
//#define RAYTRACING_INTERSECTABLE_COLLECTION_H
//
//#include <pch.h>
//#include <raytracer/intersectable.h>
//
//namespace RT {
//
//    class IntersectableCollection {
//        public:
//            IntersectableCollection();
//            ~IntersectableCollection();
//
//            void Add(Intersectable* object);
//            void Clear();
//
//            bool Intersect(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const;
//
//        private:
//            std::vector<Intersectable*> _objects;
//    };
//
//}
//
//#endif //RAYTRACING_INTERSECTABLE_COLLECTION_H
