
#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <pch.h>
#include <raytracer/ray.h>
#include <raytracer/hit_record.h>
#include <raytracer/texture.h>

namespace RT {

    class IMaterial {
        public:
            virtual ~IMaterial();

            [[nodiscard]] virtual bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered, float &pdf) const;
            [[nodiscard]] virtual float GetScatteringPDF(const Ray& ray, const HitRecord& hitRecord, const Ray& scattered) const;
            [[nodiscard]] virtual glm::vec3 GetEmitted(const glm::vec2& uv, const glm::vec3& point) const;
            [[nodiscard]] virtual glm::vec3 GetEmitted(float u, float v, const glm::vec3& point) const;
    };


    class Lambertian : public IMaterial {
        public:
            explicit Lambertian(const glm::vec3& albedo);
            explicit Lambertian(ITexture* texture);
            ~Lambertian() override;

            bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered, float& pdf) const override;
            float GetScatteringPDF(const Ray& ray, const HitRecord& hitRecord, const Ray& scattered) const override;

        private:
            ITexture* _texture;
    };


    class Metallic : public IMaterial {
        public:
            Metallic(const glm::vec3& albedo, float fuzziness);
            ~Metallic() override;

            bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered, float& pdf) const override;

        private:
            glm::vec3 _albedo;
            float _fuzziness;
    };


    class Dielectric : public IMaterial {
        public:
            explicit Dielectric(float refractionIndex);
            ~Dielectric() override;

            bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered, float& pdf) const override;

        private:
            [[nodiscard]] float SchlickApproximation(float refractionCoefficient, float refractionRatio) const;
            float _refractionIndex;
    };

}

#endif //RAYTRACER_MATERIAL_H
