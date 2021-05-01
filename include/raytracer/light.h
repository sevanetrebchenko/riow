
#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include <pch.h>
#include <raytracer/material.h>

namespace RT {

    class Light : public IMaterial {
        public:
            explicit Light(const glm::vec3& color);
            explicit Light(ITexture* texture);
            ~Light();

            [[nodiscard]] bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;
            [[nodiscard]] glm::vec3 GetEmitted(const glm::vec2& uv, const glm::vec3& point) const override;
            [[nodiscard]] glm::vec3 GetEmitted(float u, float v, const glm::vec3& point) const override;

        private:
            ITexture* _texture;
    };

}

#endif //RAYTRACER_LIGHT_H
