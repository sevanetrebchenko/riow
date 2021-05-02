
#include <raytracer/material.h>
#include <raytracer/utility_math.h>
#include <raytracer/onb.h>

namespace RT {

    glm::vec3 Reflect(const glm::vec3& V, const glm::vec3& N) {
        return V - 2.0f * glm::dot(V, N) * N;
    }

    glm::vec3 Refract(const glm::vec3& V, const glm::vec3& N, float K) {
        // (K * N.V) - sqrt(1 - K^2 * (1 - (N.V)^2)) * N - K * V
        // K is refraction ratio, N is the normal, V is the incoming ray
        float refractionCoefficient = glm::dot(N, -V);
        return ((K * refractionCoefficient) - std::sqrt(1.0f - K * K * (1.0f - refractionCoefficient * refractionCoefficient))) * N - K * -V;
    }



    IMaterial::~IMaterial() = default;

    glm::vec3 IMaterial::GetEmitted(float u, float v, const glm::vec3 &point) const {
        return glm::vec3(0.0f); // Non-emitting materials return black.
    }

    glm::vec3 IMaterial::GetEmitted(const glm::vec2 &uv, const glm::vec3 &point) const {
        return glm::vec3(0.0f);
    }



    Lambertian::Lambertian(const glm::vec3 &albedo) : _texture(new SolidColorTexture(albedo)) {
    }

    Lambertian::Lambertian(ITexture *texture) : _texture(texture) {
    }

    Lambertian::~Lambertian() {
        delete _texture;
    }

    bool Lambertian::GetScattered(const Ray &ray, const HitRecord &hitRecord, glm::vec3 &attenuation, Ray &scattered) const {
//        glm::vec3 scatterDirection = hitRecord.GetIntersectionNormal() + RandomDirectionInHemisphere(hitRecord.GetIntersectionNormal());

        OrthonormalBasis basis(hitRecord.GetIntersectionNormal());
        glm::vec3 scatterDirection = basis.GetLocalVector(RandomCosineDirection());

        // Ensure scatter direction does not cancel out normal.
        if ((std::abs(scatterDirection.x) < std::numeric_limits<float>::epsilon()) && (std::abs(scatterDirection.y) < std::numeric_limits<float>::epsilon()) && (std::abs(scatterDirection.z) < std::numeric_limits<float>::epsilon())) {
            scatterDirection = hitRecord.GetIntersectionNormal();
        }

        attenuation = _texture->GetColorValue(hitRecord.GetIntersectionUVs(), hitRecord.GetIntersectionPoint());
        scattered = Ray(hitRecord.GetIntersectionPoint(), scatterDirection);
        return true;
    }



    Metallic::Metallic(const glm::vec3 &albedo, float fuzziness) : _albedo(albedo),
                                                                   _fuzziness(fuzziness < 1.0f ? fuzziness : 1.0f)
                                                                   {
    }

    Metallic::~Metallic() = default;

    bool Metallic::GetScattered(const Ray &ray, const HitRecord &hitRecord, glm::vec3 &attenuation, Ray &scattered) const {
        const glm::vec3& V = glm::normalize(ray.GetDirection());
        const glm::vec3& N = glm::normalize(hitRecord.GetIntersectionNormal());

        glm::vec3 R = Reflect(V, N);

        scattered = Ray(hitRecord.GetIntersectionPoint(), R + _fuzziness * glm::normalize(RandomDirectionInHemisphere(hitRecord.GetIntersectionNormal())));
        attenuation = _albedo;

        // Returns true if the output ray is scattered (dot product of parallel vectors is 0).
        return glm::dot(scattered.GetDirection(), N) > 0.0f;
    }



    Dielectric::Dielectric(float refractionIndex) : _refractionIndex(refractionIndex) {
    }

    Dielectric::~Dielectric() = default;

    bool Dielectric::GetScattered(const Ray &ray, const HitRecord &hitRecord, glm::vec3 &attenuation, Ray &scattered) const {
        float refractionRatio = hitRecord.GetOutwardFacing() ? 1.0f / _refractionIndex : _refractionIndex; // Reverse Snell's law if the ray comes from the inside.
        const glm::vec3& N = glm::normalize(hitRecord.GetIntersectionNormal());
        const glm::vec3& V = glm::normalize(ray.GetDirection());

        // Deriving Snell's law.
        float refractionCoefficient = glm::dot(N, -V);
        float cosTheta = std::min(refractionCoefficient, 1.0f);
        float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta); // Trig identity.

        glm::vec3 refractedDirection;

        if (refractionRatio * sinTheta > 1.0f || SchlickApproximation(cosTheta, refractionRatio) > glm::linearRand(0.0f, 1.0f)) {
            refractedDirection = Reflect(V, N);
        }
        else {
            refractedDirection = Refract(V, N, refractionRatio);
        }

        scattered = Ray(hitRecord.GetIntersectionPoint(), refractedDirection);
        attenuation = glm::vec3(1.0f, 1.0f, 1.0f);

        return true;
    }

    float Dielectric::SchlickApproximation(float refractionCoefficient, float refractionRatio) const {
        float f = (1.0f - refractionRatio) / (1.0f + refractionRatio);
        f *= f;
        return f + (1.0f - f) * IntegerPower(1.0f - refractionCoefficient, 5);
    }



    Isotropic::Isotropic(const glm::vec3& color) : _texture(new SolidColorTexture(color)) {
    }

    Isotropic::Isotropic(ITexture* texture) : _texture(texture) {
    }

    Isotropic::~Isotropic() {
        delete _texture;
    }

    bool Isotropic::GetScattered(const Ray &ray, const HitRecord &hitRecord, glm::vec3 &attenuation, Ray &scattered) const {
        scattered = Ray(hitRecord.GetIntersectionPoint(), RandomDirectionInUnitSphere()); // Picks random direction in unit sphere.
        attenuation = _texture->GetColorValue(hitRecord.GetIntersectionUVs(), hitRecord.GetIntersectionPoint());

        return true;
    }
}
