
#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include <pch.h>
#include <raytracer/hittable.h>
#include <raytracer/material.h>
#include <raytracer/hittable_collection.h>

namespace RT {

    class Rectangle : public IHittable {
        public:
            Rectangle(const glm::vec3& bottom, const glm::vec3& top, int thinAxis, IMaterial* material);
            [[nodiscard]] bool GetAABB(AABB& aabb) const override;

        protected:
            void ConstructAABB();
            bool ComputeIntersection(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const;

            int _thinAxis;
            int _mainAxis1;
            int _mainAxis2;

            AABB _aabb;
            IMaterial* _material;

            glm::vec3 _min;
            glm::vec3 _max;
            glm::vec3 _normal;
    };

    class XYRectangle : public Rectangle {
        public:
            XYRectangle(const glm::vec2& min, const glm::vec2& max, float height, IMaterial* material);
            ~XYRectangle() override;

            [[nodiscard]] bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
    };

    class XZRectangle : public Rectangle {
        public:
            XZRectangle(const glm::vec2& bottom, const glm::vec2& top, float height, IMaterial* material);
            ~XZRectangle() override;

            [[nodiscard]] bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
    };

    class YZRectangle : public Rectangle {
        public:
            YZRectangle(const glm::vec2& bottom, const glm::vec2& top, float height, IMaterial* material);
            ~YZRectangle() override;

            [[nodiscard]] bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
    };



    class Cube : public IHittable {
        public:
            Cube(const glm::vec3& min, const glm::vec3& max, IMaterial* material);
            ~Cube();

            [[nodiscard]] bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            [[nodiscard]] bool GetAABB(AABB& aabb) const override;

        private:
            glm::vec3 _min;
            glm::vec3 _max;
            IMaterial* _material;
            AABB _aabb;

            HittableCollection _sides;
    };
}

#endif //RAYTRACER_CUBE_H
