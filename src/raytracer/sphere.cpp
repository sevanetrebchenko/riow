
#include <algorithm>
#include "sphere.h"
#include "common.h"
#include "affine_math.h"

namespace RT {

    Sphere::Sphere(const glm::vec3& centerPosition, float radius, IMaterial* material) : _centerPosition(centerPosition), _radius(radius), _material(material) {
        ConstructBoundingBox();
    }

    Sphere::~Sphere() = default;

    // If sphere center is at C (cX, cY, cZ), ray R (rX, rY, rZ),
    // equation of the sphere becomes (R - C) * (R - C) = r * r, where r is the sphere radius.
    bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
        // Compute intersection.
        glm::vec3 originToSphereCenter = ray.GetOrigin() - _centerPosition;

        float a = glm::dot(ray.GetDirection(), ray.GetDirection());
        float b = 2.0f * glm::dot(originToSphereCenter, ray.GetDirection());
        float c = glm::dot(originToSphereCenter, originToSphereCenter) - (_radius * _radius);

        float discriminant = (b * b - 4.0f * a * c);
        if (discriminant < 0.0f) {
            // No real roots, no intersection.
            return false;
        }

        float sqrtDiscriminant = std::sqrt(discriminant);
        float root = (-b - sqrtDiscriminant) / (2.0f * a);

        // Find the nearest root that lies in the acceptable range.
        if (root < tMin || root > tMax) {
            root = (-b + sqrtDiscriminant) / (2.0f * a);

            if (root < tMin || root > tMax) {
              return false;
            }
        }

        // Construct hit record.
        hitRecord.SetMaterial(_material);

        glm::vec3 intersectionPoint = ray.StepTo(root);
        hitRecord.SetIntersectionTime(root);
        hitRecord.SetIntersectionPoint(intersectionPoint);

        glm::vec3 normal = (intersectionPoint - _centerPosition) / _radius;
        hitRecord.SetFaceNormal(ray, normal);
        hitRecord.SetIntersectionUVCoordinate(CalculateUV(normal));

        return true;
    }

    bool Sphere::GetBoundingBox(float tMin, float tMax, AABB& boundingBox) const {
        boundingBox = _boundingBox;
        return true;
    }

    glm::vec2 Sphere::CalculateUV(const glm::vec3 &intersectionPoint) const {
        float theta = glm::atan(intersectionPoint.x, intersectionPoint.z);
        float phi = glm::acos(intersectionPoint.y / _radius);

        float u = theta / (pi * 2.0f);
        float v = (pi - phi) / pi;

        // Offset texture coordinates correctly to account for negatives.
        if (u < 0.0f) {
            u += 1.0f;
        }

        if (u > 1.0f) {
            u -= 1.0f;
        }

        if (v < 0.0f) {
            v += 1.0f;
        }

        if (v > 1.0f) {
            v -= 1.0f;
        }

        return glm::vec2(u, v);
    }

    void Sphere::ConstructBoundingBox() {
        // Bottom face corners.
        glm::vec3 bottomLeftNear  = _centerPosition + glm::vec3(-_radius, -_radius, _radius);
        glm::vec3 bottomRightNear = _centerPosition + glm::vec3(_radius, -_radius, _radius);
        glm::vec3 bottomLeftFar   = _centerPosition + glm::vec3(-_radius, -_radius, -_radius);
        glm::vec3 bottomRightFar  = _centerPosition + glm::vec3(_radius, -_radius, -_radius);

        // Top face corners.
        glm::vec3 topLeftNear  = _centerPosition + glm::vec3(-_radius, _radius, _radius);
        glm::vec3 topRightNear = _centerPosition + glm::vec3(_radius, _radius, _radius);
        glm::vec3 topLeftFar   = _centerPosition + glm::vec3(-_radius, _radius, -_radius);
        glm::vec3 topRightFar  = _centerPosition + glm::vec3(_radius, _radius, -_radius);

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
