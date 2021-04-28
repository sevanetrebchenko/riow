
#ifndef RAYTRACING_IMAGE_TEXTURE_H
#define RAYTRACING_IMAGE_TEXTURE_H

#include "texture.h"

namespace RT {

    class ImageTexture : public ITexture {
        public:
            const static int BYTES_PER_PIXEL = 3; // RGB

            ImageTexture();
            ImageTexture(const char* filename);
            ~ImageTexture();

            glm::vec3 GetColorValue(float u, float v, const glm::vec3& point) const override;
            glm::vec3 GetColorValue(const glm::vec2& uvCoordinates, const glm::vec3& intersectionPoint) const override;

        private:
            unsigned char* _imageData;
            int _width;
            int _height;
            int _bytesPerLine;
    };

}

#endif //RAYTRACING_IMAGE_TEXTURE_H
