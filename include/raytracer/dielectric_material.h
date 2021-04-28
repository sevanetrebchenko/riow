
#ifndef RAYTRACING_DIELECTRIC_MATERIAL_H
#define RAYTRACING_DIELECTRIC_MATERIAL_H

#include "glm/glm.hpp"
#include "material.h"
#include "ray.h"
#include "hit_record.h"

namespace RT {

    class DielectricMaterial : public IMaterial {
        public:
            DielectricMaterial(float refractionIndex);
            ~DielectricMaterial() override;

            bool Scatter(const Ray& ray, const HitRecord& hitRecord, glm::vec3& colorAttenuation, Ray& scatteredRay) const override;

        private:
            float SchlickApproximation(float refractionCoefficient) const;

            float _refractionIndex;
    };

}

#endif //RAYTRACING_DIELECTRIC_MATERIAL_H
