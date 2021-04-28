
#include "solid_color_texture.h"

namespace RT {

    SolidColorTexture::SolidColorTexture() : _color(glm::vec3(0.0f, 0.0f, 0.0f)) {
    }

    SolidColorTexture::SolidColorTexture(glm::vec3 color) : _color(color) {
    }

    SolidColorTexture::SolidColorTexture(float red, float green, float blue) : _color(glm::vec3(red, green, blue)) {
    }

    SolidColorTexture::~SolidColorTexture() = default;

    glm::vec3 SolidColorTexture::GetColorValue(float u, float v, const glm::vec3 &intersectionPoint) const {
        return _color;
    }

    glm::vec3 SolidColorTexture::GetColorValue(const glm::vec2 &uvCoordinates, const glm::vec3 &intersectionPoint) const {
        return _color;
    }
}

