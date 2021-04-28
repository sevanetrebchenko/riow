
#ifndef RAYTRACING_TEXTURE_H
#define RAYTRACING_TEXTURE_H

#include "glm/glm.hpp"

namespace RT {

    class ITexture {
        public:
            virtual ~ITexture();

            [[nodiscard]] virtual glm::vec3 GetColorValue(float u, float v, const glm::vec3& intersectionPoint) const = 0;
            [[nodiscard]] virtual glm::vec3 GetColorValue(const glm::vec2& uvCoordinates, const glm::vec3& intersectionPoint) const = 0;
    };

}

#endif //RAYTRACING_TEXTURE_H
