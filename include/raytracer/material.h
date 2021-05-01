
#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <pch.h>
#include <raytracer/ray.h>
#include <raytracer/hit_record.h>
#include <raytracer/texture.h>

namespace RT {

    class IMaterial {
        public:
            [[nodiscard]] virtual bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const = 0;
            [[nodiscard]] virtual glm::vec3 GetEmitted(float u, float v, const glm::vec3& point) const;
    };


    class Lambertian : public IMaterial {
        public:
            explicit Lambertian(const glm::vec3& albedo);
            explicit Lambertian(ITexture* texture);
            ~Lambertian();

            bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;

        private:
            ITexture* _texture;
    };


    class Metallic : public IMaterial {
        public:
            Metallic(const glm::vec3& albedo, float fuzziness);
            Metallic(ITexture* texture, float fuzziness);
            ~Metallic();

            bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;

        private:
            ITexture* _texture;
            float _fuzziness;
    };


    class Dielectric : public IMaterial {
        public:
            Dielectric(float refractionIndex);
            ~Dielectric();

            bool GetScattered(const Ray& ray, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;

        private:
            [[nodiscard]] float SchlickApproximation(float refractionCoefficient, float refractionRatio) const;
            float _refractionIndex;
    };

}

#endif //RAYTRACER_MATERIAL_H
