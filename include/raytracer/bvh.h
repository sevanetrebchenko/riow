
#ifndef RAYTRACING_BVH_H
#define RAYTRACING_BVH_H

#include <list>
#include "hittable.h"
#include "hittable_collection.h"

namespace RT {

    class BVHNode : public IHittable {
        public:
            BVHNode();
            BVHNode(const std::vector<IHittable*>& objects, float tMin, float tMax);
            ~BVHNode();

            bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            bool GetBoundingBox(float tMin, float tMax, AABB& boundingBox) const override;

        private:
            BVHNode(IHittable* left, IHittable* right, const AABB& boundingBox);
            void CondenseBVHTree(std::list<IHittable*>& objects, float tMin, float tMax);

            IHittable* _left;
            IHittable* _right;
            AABB _boundingBox;
    };

}

#endif //RAYTRACING_BVH_H
