
#include <raytracer/intersectable.h>

namespace RT {

    Intersectable::Intersectable(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, IMaterial* material) : _transform(position, rotation, scale),
                                                                                                                                      _aabb(_transform),
                                                                                                                                      _material(material)
                                                                                                                                      {
    }

    Intersectable::Intersectable(const Transform &transform, IMaterial* material) : _transform(transform),
                                                                                    _aabb(transform),
                                                                                    _material(material)
                                                                                    {
    }

    Intersectable::~Intersectable() = default;

    const AABB &Intersectable::GetBoundingBox() const {
        return _aabb;
    }

}
