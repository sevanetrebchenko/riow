
#include <raytracer/texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace RT {

    ITexture::~ITexture() = default;



    SolidColorTexture::SolidColorTexture(glm::vec3 color) : _color(color) {
    }

    SolidColorTexture::~SolidColorTexture() = default;

    glm::vec3 SolidColorTexture::GetColorValue(float u, float v, const glm::vec3 &point) const {
        return _color;
    }

    glm::vec3 SolidColorTexture::GetColorValue(const glm::vec2 &uvCoordinates, const glm::vec3 &intersectionPoint) const {
        return _color;
    }



    ImageTexture::ImageTexture(const char *filename) {
        stbi_set_flip_vertically_on_load(true);
        _data = stbi_load(filename, &_width, &_height, &_channels, 3);

        if (!_data) {
            throw std::runtime_error("Failed to open image texture file: " + std::string(filename));
        }
    }

    ImageTexture::~ImageTexture() {
        delete _data;
    }

    glm::vec3 ImageTexture::GetColorValue(float u, float v, const glm::vec3 &point) const {
        return GetColor(u, v, point);
    }

    glm::vec3 ImageTexture::GetColorValue(const glm::vec2 &uv, const glm::vec3 &point) const {
        return GetColor(uv.x, uv.y, point);
    }

    glm::vec3 ImageTexture::GetColor(float u, float v, const glm::vec3 &point) const {
        // Clamp input UV coordinates to not go outside the range of the image [0, 1].
        u = glm::clamp(u, 0.0f, 1.0f);
        u = glm::clamp(v, 0.0f, 1.0f);

        int x = static_cast<int>(u * (float)_width);
        int y = static_cast<int>(v * (float)_height);

        // Actual texture coordinate needs to be less than 1.0.
        if (x >= _width) {
            x = _width - 1;
        }
        if (y >= _height) {
            y = _height - 1;
        }

        float scalingFactor = 1.0f / 255.0f;
        unsigned char* offset = _data + (x + _width * y) * _channels;

        return glm::vec3(scalingFactor * offset[0], scalingFactor * offset[1], scalingFactor * offset[2]);
    }
}
