
#include <raytracer/sphere.h>

namespace RT {

    Sphere::Sphere(const glm::vec3 &position, const glm::vec3 rotation, float radius, IMaterial *material) : Intersectable(position, rotation, glm::vec3(radius), material) {
    }

    Sphere::~Sphere() = default;

    // If sphere center is at C (cX, cY, cZ), ray R (rX, rY, rZ),
    // equation of the sphere becomes (R - C) * (R - C) = r * r, where r is the sphere radius.
    bool Sphere::Intersect(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        Ray transformed = _transform.TransformRay(ray);
        float radius = _transform.GetScale().x;

        // Compute intersection.
        {
            glm::vec3 originToSphereCenter = transformed.GetOrigin();

            float a = glm::dot(transformed.GetDirection(), transformed.GetDirection());
            float b = 2.0f * glm::dot(originToSphereCenter, transformed.GetDirection());
            float c = glm::dot(originToSphereCenter, originToSphereCenter) - (radius * radius);

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
            hitRecord.material = _material;
            hitRecord.dt = root;
            hitRecord.point = transformed.Step(root);
            hitRecord.normal = (hitRecord.point) / radius;
        }

        _transform.UndoTransform(transformed, hitRecord);
        return true;
    }

//    glm::vec2 Sphere::CalculateUV(const glm::vec3 &intersectionPoint) const {
//        float theta = glm::atan(intersectionPoint.x, intersectionPoint.z);
//        float phi = glm::acos(intersectionPoint.y / _radius);
//
//        float u = theta / (pi * 2.0f);
//        float v = (pi - phi) / pi;
//
//        // Offset texture coordinates correctly to account for negatives.
//        if (u < 0.0f) {
//            u += 1.0f;
//        }
//
//        if (u > 1.0f) {
//            u -= 1.0f;
//        }
//
//        if (v < 0.0f) {
//            v += 1.0f;
//        }
//
//        if (v > 1.0f) {
//            v -= 1.0f;
//        }
//
//        return glm::vec2(u, v);
//    }


}
