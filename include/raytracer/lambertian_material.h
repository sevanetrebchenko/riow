
#ifndef RAYTRACING_LAMBERTIAN_MATERIAL_H
#define RAYTRACING_LAMBERTIAN_MATERIAL_H

#include "glm/glm.hpp"
#include "material.h"
#include "hit_record.h"
#include "ray.h"
#include "texture.h"

namespace RT {

    class LambertianMaterial : public IMaterial {
        public:
            LambertianMaterial(const glm::vec3& color);
            LambertianMaterial(ITexture* texture);

            ~LambertianMaterial() override;

            bool Scatter(const Ray& ray, const HitRecord& hitRecord, glm::vec3& sourceColor, Ray& scatteredRay) const override;

        private:
            ITexture* _albedo;
    };

}

#endif //RAYTRACING_LAMBERTIAN_MATERIAL_H
