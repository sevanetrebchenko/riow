
#include "metallic_material.h"
#include "random.h"

namespace RT {

    MetallicMaterial::MetallicMaterial(const glm::vec3& color, float fuzziness) : _albedo(color), _fuzziness(fuzziness < 1.0f ? fuzziness : 1.0f) {
    }

    MetallicMaterial::~MetallicMaterial() = default;

    bool MetallicMaterial::Scatter(const Ray& ray, const HitRecord& hitRecord, glm::vec3& sourceColor, Ray& scatteredRay) const {
        const glm::vec3& V = glm::normalize(ray.GetDirection());
        const glm::vec3& N = glm::normalize(hitRecord.GetFaceNormal());

        glm::vec3 R = Reflect(V, N);

        scatteredRay = Ray(hitRecord.GetIntersectionPoint(), R + _fuzziness * glm::normalize(RandomVec3InUnitSphere()), ray.GetTime());
        sourceColor = _albedo;

        // Returns true if the output ray is scattered (dot product of parallel vectors is 0).
        return glm::dot(scatteredRay.GetDirection(), N) > 0.0f;
    }

}
