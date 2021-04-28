
#include <stdexcept>
#include "image_texture.h"
#include "rt_stb_image.h"
#include "common.h"

namespace RT {

    ImageTexture::ImageTexture() : _imageData(nullptr), _width(0u), _height(0u), _bytesPerLine(0u) {
    }

    ImageTexture::ImageTexture(const char *filename) {
        int channelsPerPixel = BYTES_PER_PIXEL;

        stbi_set_flip_vertically_on_load(true);
        _imageData = stbi_load(filename, &_width, &_height, &channelsPerPixel, channelsPerPixel);

        if (!_imageData) {
            throw std::runtime_error("Failed to open image texture file: " + std::string(filename));
        }

        _bytesPerLine = _width * BYTES_PER_PIXEL;
    }

    ImageTexture::~ImageTexture() {
        delete _imageData;
    }

    glm::vec3 ImageTexture::GetColorValue(float u, float v, const glm::vec3 &point) const {
        // Clamp input UV coordinates to not go outside the range of the image [0, 1].
        u = Clamp01(u);
        v = Clamp01(v);

        int x = static_cast<int>(u * _width);
        int y = static_cast<int>(v * _height);

        // Actual texture coordinate needs to be less than 1.0.
        if (x >= _width) {
            x = _width - 1;
        }
        if (y >= _height) {
            y = _height - 1;
        }

        float scalingFactor = 1.0f / 255.0f;
        unsigned char* pixel = _imageData + y * _bytesPerLine + x * BYTES_PER_PIXEL;

        return glm::vec3(scalingFactor * pixel[0], scalingFactor * pixel[1], scalingFactor * pixel[2]);
    }

    glm::vec3 ImageTexture::GetColorValue(const glm::vec2 &uvCoordinates, const glm::vec3 &intersectionPoint) const {
        float u = uvCoordinates.x;
        float v = uvCoordinates.y;

        // Clamp input UV coordinates to not go outside the range of the image [0, 1].
        Clamp01(u);
        Clamp01(v);

        int x = static_cast<int>(u * _width);
        int y = static_cast<int>(v * _height);

        // Actual texture coordinate needs to be less than 1.0.
        if (x >= _width) {
            x = _width - 1;
        }
        if (y >= _height) {
            y = _height - 1;
        }

        float scalingFactor = 1.0 / 255.0;
        unsigned char* pixel = _imageData + y * _bytesPerLine + x * BYTES_PER_PIXEL;

        return glm::vec3(scalingFactor * pixel[0], scalingFactor * pixel[1], scalingFactor * pixel[2]);
    }
}

