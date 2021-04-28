
#ifndef RAYTRACING_SOLID_COLOR_TEXTURE_H
#define RAYTRACING_SOLID_COLOR_TEXTURE_H

#include "texture.h"

namespace RT {

    class SolidColorTexture : public ITexture {
        public:
            SolidColorTexture();
            SolidColorTexture(glm::vec3 color);
            SolidColorTexture(float red, float green, float blue);

            ~SolidColorTexture() override;

            glm::vec3 GetColorValue(float u, float v, const glm::vec3& point) const override;
            glm::vec3 GetColorValue(const glm::vec2& uvCoordinates, const glm::vec3& intersectionPoint) const override;

        private:
            glm::vec3 _color;
    };

}

#endif //RAYTRACING_SOLID_COLOR_TEXTURE_H
