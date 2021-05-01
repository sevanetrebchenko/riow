
#ifndef RAYTRACER_BVH_H
#define RAYTRACER_BVH_H

#include <raytracer/hittable.h>

namespace RT {

    class BVHNode : public IHittable {
        public:
            BVHNode(const std::vector<IHittable*>& objects, int start, int end);
            ~BVHNode() override;

            [[nodiscard]] bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            [[nodiscard]] bool GetAABB(AABB& boundingBox) const override;

        private:
            IHittable* _left;
            IHittable* _right;
            AABB _aabb;
    };

}

#endif //RAYTRACER_BVH_H
