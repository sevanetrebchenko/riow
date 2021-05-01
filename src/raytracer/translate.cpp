
#include <raytracer/translate.h>

namespace RT {

    Translate::Translate(IHittable *object, glm::vec3 displacement) : _object(object), _displacement(displacement) {
        ConstructBoundingBox();
    }

    Translate::~Translate() {
    }

    bool Translate::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        Ray translatedRay(ray.GetOrigin() - _displacement, ray.GetDirection());

        if (!_object->Hit(translatedRay, tMin, tMax, hitRecord)) {
            return false;
        }

        hitRecord.SetIntersectionPoint(hitRecord.GetIntersectionPoint() + _displacement);
        hitRecord.SetIntersectionNormal(translatedRay, hitRecord.GetIntersectionNormal());
        return true;
    }

    bool Translate::GetAABB(AABB& aabb) const {
        aabb = _aabb;
        return _hasBoundingBox;
    }

    void Translate::ConstructBoundingBox() {
        _hasBoundingBox = _object->GetAABB(_aabb);
        if (_hasBoundingBox) {
            _aabb = AABB(_aabb.minimum + _displacement, _aabb.maximum + _displacement);
        }
    }
}

