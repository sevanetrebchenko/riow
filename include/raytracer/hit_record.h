
#ifndef RAYTRACER_HIT_RECORD_H
#define RAYTRACER_HIT_RECORD_H

#include <pch.h>
#include <raytracer/ray.h>

namespace RT {

    // Forward declaration.
    class IMaterial;

    class HitRecord {
        public:
            HitRecord();
            ~HitRecord();

            void SetIntersectionTime(float dt);
            [[nodiscard]] float GetIntersectionTime() const;

            void SetIntersectionPoint(const glm::vec3& point);
            [[nodiscard]] const glm::vec3& GetIntersectionPoint() const;

            void SetIntersectionNormal(const Ray& ray, const glm::vec3& normal);
            [[nodiscard]] const glm::vec3& GetIntersectionNormal() const;
            [[nodiscard]] bool GetOutwardFacing() const;

            void SetIntersectionUVs(const glm::vec2& uv);
            void SetIntersectionUVs(float u, float v);
            [[nodiscard]] const glm::vec2& GetIntersectionUVs() const;

            void SetIntersectionMaterial(IMaterial* material);
            [[nodiscard]] const IMaterial* GetIntersectionMaterial() const;

        private:
            float _dt;
            glm::vec3 _point;
            glm::vec3 _normal;
            glm::vec2 _uv;
            IMaterial* _material;
            bool _frontFacing;
    };

}

#endif //RAYTRACER_HIT_RECORD_H
