
#include "translate.h"

namespace RT {

    Translate::Translate(IHittable *object, glm::vec3 displacement) : _object(object), _displacement(displacement) {
        ConstructBoundingBox();
    }

    Translate::~Translate() {
    }

    bool Translate::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        Ray translatedRay(ray.GetOrigin() - _displacement, ray.GetDirection(), ray.GetTime());

        if (!_object->Hit(translatedRay, tMin, tMax, hitRecord)) {
            return false;
        }

        hitRecord.SetIntersectionPoint(hitRecord.GetIntersectionPoint() + _displacement);
        hitRecord.SetFaceNormal(translatedRay, hitRecord.GetFaceNormal());
        return true;
    }

    bool Translate::GetBoundingBox(float tMin, float tMax, AABB &boundingBox) const {
        boundingBox = _boundingBox;
        return _hasBoundingBox;
    }

    void Translate::ConstructBoundingBox() {
        _hasBoundingBox = _object->GetBoundingBox(0.0f, 1.0f, _boundingBox);
        if (_hasBoundingBox) {
            _boundingBox = AABB(_boundingBox.GetMinimum() + _displacement, _boundingBox.GetMaximum() + _displacement);
        }
    }
}

