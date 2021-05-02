
#include <raytracer/light.h>

namespace RT {

    Light::Light(const glm::vec3 &color) : _texture(new SolidColorTexture(color)) {
    }

    Light::Light(ITexture *texture) : _texture(texture) {
    }

    Light::~Light() {
        delete _texture;
    }

    bool Light::GetScattered(const Ray &ray, const HitRecord &hitRecord, glm::vec3 &attenuation, Ray &scattered, float& pdf) const {
        return false; // Light does not scatter.
    }

    glm::vec3 Light::GetEmitted(float u, float v, const glm::vec3 &point) const {
        return _texture->GetColorValue(u, v, point);
    }

    glm::vec3 Light::GetEmitted(const glm::vec2 &uv, const glm::vec3 &point) const {
        return _texture->GetColorValue(uv.x, uv.y, point);
    }
}
