
#include "glm/gtx/transform.hpp"
#include "rotate.h"
#include "affine_math.h"
#include <algorithm>

namespace RT {

    Rotate::Rotate(IHittable *object, glm::vec3 rotation) : _object(object), _rotation(rotation) {
        // Rotation in 3D is not commutative.
        // The matrix to rotate the ray before checking ray intersection is NOT the same matrix to rotate the ray back.
        _negativeMatrix = RotateAroundX(-_rotation.x) * RotateAroundY(-_rotation.y) * RotateAroundZ(-_rotation.z);
        _positiveMatrix = RotateAroundZ(_rotation.z) * RotateAroundY(_rotation.y) * RotateAroundX(_rotation.x);
        ConstructBoundingBox();
    }

    Rotate::~Rotate() {

    }

    bool Rotate::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        // Perform inverse rotation.
        Ray rotatedRay(_negativeMatrix * glm::vec4(ray.GetOrigin(), 1.0f), _negativeMatrix * glm::vec4(ray.GetDirection(), 0.0f), ray.GetTime());

        if (!_object->Hit(rotatedRay, tMin, tMax, hitRecord)) {
            return false;
        }

        // Undo rotation.
        hitRecord.SetIntersectionPoint(_positiveMatrix * glm::vec4(hitRecord.GetIntersectionPoint(), 1.0f));
        hitRecord.SetFaceNormal(rotatedRay, _positiveMatrix * glm::vec4(hitRecord.GetFaceNormal(), 0.0f));
        return true;
    }

    bool Rotate::GetBoundingBox(float tMin, float tMax, AABB &boundingBox) const {
        boundingBox = _boundingBox;
        return _hasBoundingBox;
    }

    void Rotate::ConstructBoundingBox() {
        _hasBoundingBox = _object->GetBoundingBox(0.0f, 1.0f, _boundingBox);

        if (_hasBoundingBox) {
            const glm::vec3& aabbMinimum = _boundingBox.GetMinimum();
            const glm::vec3& aabbCenter = _boundingBox.GetCenter();

            float halfWidth = std::fabs(aabbCenter.x - aabbMinimum.x);
            glm::vec3 scale(halfWidth);

            // Bottom face corners.
            glm::vec3 bottomLeftNear  = glm::vec3(-scale.x, -scale.y, scale.z);
            glm::vec3 bottomRightNear = glm::vec3(scale.x, -scale.y, scale.z);
            glm::vec3 bottomLeftFar   = glm::vec3(-scale.x, -scale.y, -scale.z);
            glm::vec3 bottomRightFar  = glm::vec3(scale.x, -scale.y, -scale.z);

            // Top face corners.
            glm::vec3 topLeftNear  = glm::vec3(-scale.x, scale.y, scale.z);
            glm::vec3 topRightNear = glm::vec3(scale.x, scale.y, scale.z);
            glm::vec3 topLeftFar   = glm::vec3(-scale.x, scale.y, -scale.z);
            glm::vec3 topRightFar  = glm::vec3(scale.x, scale.y, -scale.z);

            // Get transformed endpoints.
            bottomLeftNear = _positiveMatrix * glm::vec4(bottomLeftNear, 1.0f);
            bottomRightNear = _positiveMatrix * glm::vec4(bottomRightNear, 1.0f);
            bottomLeftFar = _positiveMatrix * glm::vec4(bottomLeftFar, 1.0f);
            bottomRightFar = _positiveMatrix * glm::vec4(bottomRightFar, 1.0f);
            topLeftNear = _positiveMatrix * glm::vec4(topLeftNear, 1.0f);
            topRightNear = _positiveMatrix * glm::vec4(topRightNear, 1.0f);
            topLeftFar = _positiveMatrix * glm::vec4(topLeftFar, 1.0f);
            topRightFar = _positiveMatrix * glm::vec4(topRightFar, 1.0f);

            // Make the axis-aligned box from the minimum points along each axis.
            glm::vec3 minimum;
            glm::vec3 maximum;

            minimum.x = std::min(std::min(std::min(std::min(bottomLeftNear.x, bottomRightNear.x), bottomLeftFar.x), bottomRightFar.x), std::min(std::min(std::min(topLeftNear.x, topRightNear.x), topLeftFar.x), topRightFar.x));
            minimum.y = std::min(std::min(std::min(std::min(bottomLeftNear.y, bottomRightNear.y), bottomLeftFar.y), bottomRightFar.y), std::min(std::min(std::min(topLeftNear.y, topRightNear.y), topLeftFar.y), topRightFar.y));
            minimum.z = std::min(std::min(std::min(std::min(bottomLeftNear.z, bottomRightNear.z), bottomLeftFar.z), bottomRightFar.z), std::min(std::min(std::min(topLeftNear.z, topRightNear.z), topLeftFar.z), topRightFar.z));

            maximum.x = std::max(std::max(std::max(std::max(bottomLeftNear.x, bottomRightNear.x), bottomLeftFar.x), bottomRightFar.x), std::max(std::max(std::max(topLeftNear.x, topRightNear.x), topLeftFar.x), topRightFar.x));
            maximum.y = std::max(std::max(std::max(std::max(bottomLeftNear.y, bottomRightNear.y), bottomLeftFar.y), bottomRightFar.y), std::max(std::max(std::max(topLeftNear.y, topRightNear.y), topLeftFar.y), topRightFar.y));
            maximum.z = std::max(std::max(std::max(std::max(bottomLeftNear.z, bottomRightNear.z), bottomLeftFar.z), bottomRightFar.z), std::max(std::max(std::max(topLeftNear.z, topRightNear.z), topLeftFar.z), topRightFar.z));

            _boundingBox = AABB(minimum, maximum);
        }
    }
}

