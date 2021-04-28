
#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include <raytracer/material.h>

namespace RT {

    class DiffuseLight : public IMaterial {
        public:
            explicit DiffuseLight(const glm::vec3& color);
            ~DiffuseLight();

            [[nodiscard]] bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;
            [[nodiscard]] glm::vec3 GetEmitted(float u, float v, const glm::vec3& point) const override;

        private:
            glm::vec3 _color;
    };

}

#endif //RAYTRACER_LIGHT_H
