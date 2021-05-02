
#include <raytracer/onb.h>

namespace RT {

    OrthonormalBasis::OrthonormalBasis(const glm::vec3 &normal) {
        _axes[2] = glm::normalize(normal);
        glm::vec3 a = (std::fabs(_axes[2].x) > 0.9f) ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
        _axes[1] = glm::normalize(glm::cross(_axes[2], a));
        _axes[0] = glm::cross(_axes[2], _axes[1]);
    }

    OrthonormalBasis::~OrthonormalBasis() = default;

    glm::vec3 OrthonormalBasis::GetLocalVector(const glm::vec3 &input) const {
        return input.x * _axes[0] + input.y * _axes[1] + input.z * _axes[2];
    }

}