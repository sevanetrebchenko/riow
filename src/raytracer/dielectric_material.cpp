
#include <cstdio>
#include <cmath>
#include <algorithm>
#include "dielectric_material.h"
#include "common.h"
#include "random.h"

namespace RT {

    DielectricMaterial::DielectricMaterial(float refractionIndex) : _refractionIndex(refractionIndex) {

    }

    DielectricMaterial::~DielectricMaterial() = default;

    bool DielectricMaterial::Scatter(const Ray& ray, const HitRecord& hitRecord, glm::vec3& sourceColor, Ray& scatteredRay) const {
        float refractionRatio = hitRecord.IsFromOutside() ? 1.0f / _refractionIndex : _refractionIndex; // Reverse Snell's law if the ray comes from the inside.
        const glm::vec3& N = hitRecord.GetFaceNormal();
        const glm::vec3& V = glm::normalize(ray.GetDirection());

        float refractionCoefficient = glm::dot(N, -V);
        float cosTheta = std::min(refractionCoefficient, 1.0f);
        float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta); // Trig identity.

        glm::vec3 refractedDirection;

        if ((refractionRatio * sinTheta > 1.0f) || SchlickApproximation(refractionCoefficient) > RandomFloat()) {
            refractedDirection = Reflect(V, N);
        }
        else {
            refractedDirection = Refract(V, N, refractionRatio);
        }

        scatteredRay = Ray(hitRecord.GetIntersectionPoint(), refractedDirection, ray.GetTime());
        sourceColor = glm::vec3(1.0f, 1.0f, 1.0f); // What's the color of a mirror?

        return true;
    }

    float DielectricMaterial::SchlickApproximation(float refractionCoefficient) const {
        float f = ((1.0f - _refractionIndex) / (1.0f + _refractionIndex));
        f *= f;
        return f + (1.0f - f) * IntegerPower(1.0f - refractionCoefficient, 5);
    }

}
