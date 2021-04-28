
#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <pch.h>
#include <raytracer/ray.h>
#include <raytracer/hit_record.h>

namespace RT {

    class IMaterial {
        public:
            [[nodiscard]] virtual bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const = 0;
            [[nodiscard]] virtual glm::vec3 GetEmitted(float u, float v, const glm::vec3& point) const;
    };

    class Lambertian : public IMaterial {
        public:
            explicit Lambertian(const glm::vec3& albedo);
            ~Lambertian();

            bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;

        private:
            glm::vec3 _albedo;
    };

    class Metallic : public IMaterial {
        public:
            Metallic(const glm::vec3& albedo, float fuzziness);
            ~Metallic();

            bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;

        private:
            [[nodiscard]] glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n) const;

            glm::vec3 _albedo;
            float _fuzziness;
    };

    class Dielectric : public IMaterial {
        public:
            explicit Dielectric(float refractionIndex);
            ~Dielectric();

            bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;

        private:
            [[nodiscard]] glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n) const;
            [[nodiscard]] glm::vec3 Refract(const glm::vec3& v, const glm::vec3& n, float refractionRatio) const;
            [[nodiscard]] float SchlickApproximation(float refractionCoefficient, float refractionRatio) const;

            float _refractionIndex;
    };

}

#endif //RAYTRACER_MATERIAL_H
