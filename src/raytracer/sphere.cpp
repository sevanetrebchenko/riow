
#include <raytracer/sphere.h>

namespace RT {

    Sphere::Sphere(const glm::vec3& centerPosition, float radius, IMaterial* material) : _centerPosition(centerPosition),
                                                                                         _radius(radius),
                                                                                         _material(material),
                                                                                         _boundingBox(centerPosition, glm::vec3(0.0f), glm::vec3(radius))
                                                                                         {
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
        hitRecord.SetIntersectionMaterial(_material);

        glm::vec3 intersectionPoint = ray.Step(root);
        hitRecord.SetIntersectionTime(root);
        hitRecord.SetIntersectionPoint(intersectionPoint);

        glm::vec3 normal = (intersectionPoint - _centerPosition) / _radius;
        hitRecord.SetIntersectionNormal(ray, normal);
        hitRecord.SetIntersectionUVs(CalculateUV(normal));

        return true;
    }

    glm::vec2 Sphere::CalculateUV(const glm::vec3 &intersectionPoint) const {
        float theta = glm::atan(intersectionPoint.x, intersectionPoint.z);
        float phi = glm::acos(intersectionPoint.y / _radius);

        float u = theta / ((float)M_PI * 2.0f);
        float v = ((float)M_PI - phi) / (float)M_PI;

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

}
