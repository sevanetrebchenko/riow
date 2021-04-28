
#include "lambertian_material.h"
#include "random.h"
#include "common.h"
#include "solid_color_texture.h"

namespace RT {

    LambertianMaterial::LambertianMaterial(const glm::vec3& color) : _albedo(new SolidColorTexture(color)) {
    }

    LambertianMaterial::LambertianMaterial(ITexture *texture) : _albedo(texture) {
    }

    LambertianMaterial::~LambertianMaterial() = default;

    bool LambertianMaterial::Scatter(const Ray& ray, const HitRecord& hitRecord, glm::vec3& sourceColor, Ray& scatteredRay) const {
        glm::vec3 scatterDirection = hitRecord.GetFaceNormal() + glm::normalize(RandomVec3InUnitSphere());

        // Catch vectors that are near zero.
        if (NearZero(scatterDirection)) {
            scatterDirection = hitRecord.GetFaceNormal();
        }

        scatteredRay = Ray(hitRecord.GetIntersectionPoint(), scatterDirection, ray.GetTime());
        sourceColor = _albedo->GetColorValue(hitRecord.GetIntersectionUVCoordinate(), hitRecord.GetIntersectionPoint());

        return true;
    }

}
