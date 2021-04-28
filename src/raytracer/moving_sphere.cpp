
#include "moving_sphere.h"
#include "common.h"

namespace RT {

    MovingSphere::MovingSphere(glm::vec3 centerPosition1, float timePosition1, glm::vec3 centerPosition2, float timePosition2, float radius, IMaterial* material) : _centerPosition1(centerPosition1),
                                                                                                                                                                    _timePosition1(timePosition1),
                                                                                                                                                                    _centerPosition2(centerPosition2),
                                                                                                                                                                    _timePosition2(timePosition2),
                                                                                                                                                                    _radius(radius),
                                                                                                                                                                    _material(material) {

    }

    MovingSphere::~MovingSphere() = default;

    bool MovingSphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
        glm::vec3 centerPosition = CenterAtTime(ray.GetTime());

        glm::vec3 originToSphereCenter = ray.GetOrigin() - centerPosition;

        // Calculate discriminant to get if the ray intersects the sphere.
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
        hitRecord.SetIntersectionTime(root);
        hitRecord.SetIntersectionPoint(ray.StepTo(root));

        glm::vec3 outwardFacingNormal = (hitRecord.GetIntersectionPoint() - centerPosition) / _radius;

        hitRecord.SetFaceNormal(ray, outwardFacingNormal);
        hitRecord.SetMaterial(_material);
        hitRecord.SetIntersectionUVCoordinate(CalculateUV(outwardFacingNormal));

        return true;
    }

    bool MovingSphere::GetBoundingBox(float tMin, float tMax, AABB& boundingBox) const {
        AABB startingPositionAABB(CenterAtTime(tMin) - glm::vec3(_radius, _radius, _radius), CenterAtTime(tMin) + glm::vec3(_radius, _radius, _radius));
        AABB endingPositionAABB(CenterAtTime(tMax) - glm::vec3(_radius, _radius, _radius), CenterAtTime(tMax) + glm::vec3(_radius, _radius, _radius));

        boundingBox = AABB::Combine(startingPositionAABB, endingPositionAABB);
        return true;
    }

    glm::vec3 MovingSphere::CenterAtTime(float time) const {
        return _centerPosition1 + ((time - _timePosition1) / (_timePosition2 - _timePosition1)) * (_centerPosition2 - _centerPosition1);
    }

    glm::vec2 MovingSphere::CalculateUV(const glm::vec3 &intersectionPoint) const {
        float theta = glm::atan((intersectionPoint.x), (intersectionPoint.z));
        float phi = glm::acos(intersectionPoint.y / _radius);

        float u = theta / (pi * 2.0f);
        float v = (pi - phi) / pi;

        // Offset texture coordinates correctly to account for negatives.
        if (u < 0.0f) {
            u += 1.0f;
        }

        if (v < 0.0f) {
            v += 1.0f;
        }

        return glm::vec2(u, v);
    }

}
