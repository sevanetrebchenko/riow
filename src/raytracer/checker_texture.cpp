
#include "checker_texture.h"
#include "solid_color_texture.h"

namespace RT {


    CheckerTexture::CheckerTexture(const glm::vec3 &evenTileColor, const glm::vec3 &oddTileColor) : _evenTileTexture(new SolidColorTexture(evenTileColor)),
                                                                                                    _oddTileTexture(new SolidColorTexture(oddTileColor)),
                                                                                                    _clean(true),
                                                                                                    _checkerScale(1.0f) {
    }

    CheckerTexture::CheckerTexture(ITexture *evenTileTexture, ITexture *oddTileTexture) : _evenTileTexture(evenTileTexture),
                                                                                          _oddTileTexture(oddTileTexture),
                                                                                          _clean(false),
                                                                                          _checkerScale(1.0f) {
    }

    CheckerTexture::~CheckerTexture() {
        if (_clean) {
            delete _evenTileTexture;
            delete _oddTileTexture;
        }
    }

    glm::vec3 CheckerTexture::GetColorValue(float u, float v, const glm::vec3 &intersectionPoint) const {
        float value = std::sin(_checkerScale * intersectionPoint.x) * std::sin(_checkerScale * intersectionPoint.y) * std::sin(_checkerScale * intersectionPoint.z);
        return value < 0.0f ? _oddTileTexture->GetColorValue(u, v, intersectionPoint) : _evenTileTexture->GetColorValue(u, v, intersectionPoint);
    }

    glm::vec3 CheckerTexture::GetColorValue(const glm::vec2 &uvCoordinates, const glm::vec3 &intersectionPoint) const {
        float value = std::sin(_checkerScale * intersectionPoint.x) * std::sin(_checkerScale * intersectionPoint.y) * std::sin(_checkerScale * intersectionPoint.z);
        return value < 0.0f ? _oddTileTexture->GetColorValue(uvCoordinates, intersectionPoint) : _evenTileTexture->GetColorValue(uvCoordinates, intersectionPoint);
    }

    void CheckerTexture::SetCheckerScale(float scale) {
        _checkerScale = 1.0f / scale; // The larger the number, the smaller the checkers (make this value make sense logically).
    }

    float CheckerTexture::GetCheckerScale() const {
        return 1.0f / _checkerScale;
    }
}

