
#include <raytracer/material.h>
#include <raytracer/utility_math.h>

namespace RT {

    Lambertian::Lambertian(const glm::vec3 &albedo) : _albedo(albedo) {
    }

    Lambertian::~Lambertian() {
    }

    bool Lambertian::GetScattered(const Ray &ray, const HitRecord &hitRecord, glm::vec3 &attenuation, Ray &scattered) const {
        glm::vec3 scatterDirection = hitRecord.normal + RandomDirectionInHemisphere(hitRecord.normal);

        // Ensure scatter direction does not cancel out normal.
        if ((std::abs(scatterDirection.x) < std::numeric_limits<float>::epsilon()) && (std::abs(scatterDirection.y) < std::numeric_limits<float>::epsilon()) && (std::abs(scatterDirection.z) < std::numeric_limits<float>::epsilon())) {
            scatterDirection = hitRecord.normal;
        }

        attenuation = _albedo;
        scattered = Ray(hitRecord.point, scatterDirection);
        return true;
    }



    Metallic::Metallic(const glm::vec3 &albedo, float fuzziness) : _albedo(albedo),
                                                                   _fuzziness(fuzziness < 1.0f ? fuzziness : 1.0f) {
    }

    Metallic::~Metallic() {
    }

    bool Metallic::GetScattered(const Ray &ray, const HitRecord &hitRecord, glm::vec3 &attenuation, Ray &scattered) const {
        const glm::vec3& V = glm::normalize(ray.GetDirection());
        const glm::vec3& N = glm::normalize(hitRecord.normal);

        glm::vec3 R = Reflect(V, N);

        scattered = Ray(hitRecord.point, R + _fuzziness * glm::normalize(RandomDirectionInHemisphere(hitRecord.normal)));
        attenuation = _albedo;

        // Returns true if the output ray is scattered (dot product of parallel vectors is 0).
        return glm::dot(scattered.GetDirection(), N) > 0.0f;
    }

    glm::vec3 Metallic::Reflect(const glm::vec3 &v, const glm::vec3 &n) const {
        return v - 2.0f * glm::dot(v, n) * n;
    }


    Dielectric::Dielectric(float refractionIndex) : _refractionIndex(refractionIndex) {
    }

    Dielectric::~Dielectric() {
    }

    bool Dielectric::GetScattered(const Ray &ray, const HitRecord &hitRecord, glm::vec3 &attenuation, Ray &scattered) const {
        float refractionRatio = hitRecord.outwardFacing ? 1.0f / _refractionIndex : _refractionIndex; // Reverse Snell's law if the ray comes from the inside.
        const glm::vec3& N = hitRecord.normal;
        const glm::vec3& V = ray.GetDirection();

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

        scattered = Ray(hitRecord.point, refractedDirection);
        attenuation = glm::vec3(1.0f, 1.0f, 1.0f);

        return true;
    }

    glm::vec3 Dielectric::Reflect(const glm::vec3 &v, const glm::vec3 &n) const {
        return v - 2.0f * glm::dot(v, n) * n;
    }

    glm::vec3 Dielectric::Refract(const glm::vec3& v, const glm::vec3& n, float refractionRatio) const {
        // (K * N.V) - sqrt(1 - K^2 * (1 - (N.V)^2)) * N - K * V
        // K is refraction ratio, N is the normal, V is the incoming ray
        float refractionCoefficient = glm::dot(n, -v);
        return ((refractionRatio * refractionCoefficient) - std::sqrt(1.0f - refractionRatio * refractionRatio * (1.0f - refractionCoefficient * refractionCoefficient))) * n - refractionRatio * -v;
    }

    float Dielectric::SchlickApproximation(float refractionCoefficient, float refractionRatio) const {
        float f = ((1.0f - refractionRatio) / (1.0f + refractionRatio));
        f *= f;
        return f + (1.0f - f) * IntegerPower(1.0f - refractionCoefficient, 5);
    }

    glm::vec3 IMaterial::GetEmitted(float u, float v, const glm::vec3 &point) const {
        return glm::vec3(0.0f); // Non-emitting materials return black.
    }


    //     glm::vec3 IMaterial::Reflect(const glm::vec3& V, const glm::vec3& N) const {
    //        return V - 2.0f * glm::dot(V, N) * N;
    //    }
    //
    //    glm::vec3 IMaterial::Refract(const glm::vec3& V, const glm::vec3& N, float refractionRatio) const {
    //        // (K * N.V) - sqrt(1 - K^2 * (1 - (N.V)^2)) * N - K * V
    //        // K is refraction ratio, N is the normal, V is the incoming ray
    //        float refractionCoefficient = glm::dot(N, -V);
    //        return ((refractionRatio * refractionCoefficient) - std::sqrt(1.0f - refractionRatio * refractionRatio * (1.0f - refractionCoefficient * refractionCoefficient))) * N - refractionRatio * -V;
    //    }



}
