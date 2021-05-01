
#ifndef RAYTRACING_TRANSLATE_H
#define RAYTRACING_TRANSLATE_H

#include <pch.h>
#include <raytracer/hittable.h>

namespace RT {

    class Translate : public IHittable {
        public:
            Translate(IHittable* object, glm::vec3 displacement);
            ~Translate() override;

            bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            bool GetBoundingBox(AABB& boundingBox) const;

        private:
            void ConstructBoundingBox();

            glm::vec3 _displacement;

            IHittable* _object;
            AABB _boundingBox;
            bool _hasBoundingBox;
    };

}

#endif //RAYTRACING_TRANSLATE_H
