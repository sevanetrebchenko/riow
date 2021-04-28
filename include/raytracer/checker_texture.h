
#ifndef RAYTRACING_CHECKER_TEXTURE_H
#define RAYTRACING_CHECKER_TEXTURE_H

#include "glm/glm.hpp"
#include "texture.h"

namespace RT {

    class CheckerTexture : public ITexture {
        public:
            CheckerTexture(const glm::vec3& evenTileColor, const glm::vec3& oddTileColor);
            CheckerTexture(ITexture* evenTileTexture, ITexture* oddTileTexture);
            ~CheckerTexture() override;

            void SetCheckerScale(float scale);
            float GetCheckerScale() const;

            glm::vec3 GetColorValue(float u, float v, const glm::vec3& intersectionPoint) const override;
            glm::vec3 GetColorValue(const glm::vec2& uvCoordinates, const glm::vec3& intersectionPoint) const override;

        private:
            ITexture* _evenTileTexture;
            ITexture* _oddTileTexture;
            float _checkerScale;
            bool _clean;
    };

}

#endif //RAYTRACING_CHECKER_TEXTURE_H
