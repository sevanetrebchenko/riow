
#include <raytracer/ray.h>

namespace RT {

    Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction) : _origin(origin),
                                                                    _direction(glm::normalize(direction))
                                                                    {
    }

    Ray::~Ray() {
    }

    const glm::vec3 &Ray::GetOrigin() const {
        return _origin;
    }

    const glm::vec3 &Ray::GetDirection() const {
        return _direction;
    }

    glm::vec3 Ray::Step(float t) const {
        return _origin + t * _direction;
    }

}
