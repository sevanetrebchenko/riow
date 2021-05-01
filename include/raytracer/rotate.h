
#ifndef RAYTRACING_ROTATE_H
#define RAYTRACING_ROTATE_H

#include <pch.h>
#include <raytracer/hittable.h>

namespace RT {

    class Rotate : public IHittable {
        public:
            Rotate(IHittable* object, glm::vec3 rotation);
            ~Rotate() override;

            bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            bool GetAABB(AABB& aabb) const override;

        private:
            void ConstructBoundingBox();

            glm::vec3 _rotation;
            glm::mat4 _positiveMatrix;
            glm::mat4 _negativeMatrix;

            IHittable* _object;
            AABB _boundingBox;
            bool _hasBoundingBox;
    };

}

#endif //RAYTRACING_ROTATE_H
