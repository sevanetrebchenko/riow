
#ifndef RAYTRACER_TRANSFORM_H
#define RAYTRACER_TRANSFORM_H

#include <raytracer/ray.h>
#include <raytracer/hit_record.h>
#include <raytracer/hittable.h>
#include <raytracer/aabb.h>

namespace RT {

    class Translate : public IHittable {
        public:
            Translate(IHittable* object, glm::vec3 displacement);
            ~Translate() override;

            bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            bool GetAABB(AABB& aabb) const override;

        private:
            void ConstructBoundingBox();

            glm::vec3 _displacement;

            IHittable* _object;
            AABB _aabb;
            bool _hasBoundingBox;
    };



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
            AABB _aabb;
            bool _hasBoundingBox;
    };



    class Flip : public IHittable {
        public:
            Flip(IHittable* object);
            ~Flip() override;

            bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            bool GetAABB(AABB& aabb) const override;

        private:
            IHittable* _object;
            AABB _aabb;
    };

}

#endif //RAYTRACER_TRANSFORM_H
