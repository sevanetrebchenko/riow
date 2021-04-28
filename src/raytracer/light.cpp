
#include <raytracer/light.h>

namespace RT {

    DiffuseLight::DiffuseLight(const glm::vec3 &color) : _color(color) {
    }

    DiffuseLight::~DiffuseLight() {
    }

    bool DiffuseLight::GetScattered(const Ray &ray, const HitRecord &hitRecord, glm::vec3 &attenuation, Ray &scattered) const {
        return false;
    }

    glm::vec3 DiffuseLight::GetEmitted(float u, float v, const glm::vec3 &point) const {
        return _color;
    }
}
