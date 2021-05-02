
#include <raytracer/medium.h>
#include <raytracer/material.h>

namespace RT {

    Medium::Medium(IHittable *object, float density, const glm::vec3 &color) : _object(object),
                                                                               _density(-1.0f / density),
                                                                               _material(new Isotropic(color))
                                                                               {
    }

    Medium::Medium(IHittable *object, float density, ITexture *texture) : _object(object),
                                                                          _density(-1.0f / density),
                                                                          _material(new Isotropic(texture))
                                                                          {
    }

    Medium::~Medium() {
        delete _material;
    }

    bool Medium::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        HitRecord hitRecord1;
        HitRecord hitRecord2;

        float infinity = std::numeric_limits<float>::infinity();

        if (!_object->Hit(ray, -infinity, infinity, hitRecord1)) {
            return false;
        }

        if (!_object->Hit(ray, hitRecord1.GetIntersectionTime() + 0.0001f, infinity, hitRecord2)) {
            return false;
        }

        // Bound intersection times with object.
        if (hitRecord1.GetIntersectionTime() < tMin) {
            hitRecord1.SetIntersectionTime(tMin);
        }

        if (hitRecord2.GetIntersectionTime() > tMax) {
            hitRecord2.SetIntersectionTime(tMax);
        }

        if (hitRecord1.GetIntersectionTime() >= hitRecord2.GetIntersectionTime()) {
            return false;
        }

        if (hitRecord1.GetIntersectionTime() < 0.0f) {
            hitRecord1.SetIntersectionTime(0.0f);
        }

        float rayLength = glm::length(ray.GetDirection());
        float distanceInBoundary = (hitRecord2.GetIntersectionTime() - hitRecord1.GetIntersectionTime()) * rayLength;
        float intersectionDistance = _density * std::log(glm::linearRand(0.0f, 1.0f));

        if (intersectionDistance > distanceInBoundary) {
            return false;
        }

        hitRecord.SetIntersectionTime(hitRecord1.GetIntersectionTime() + intersectionDistance / rayLength);
        hitRecord.SetIntersectionPoint(ray.Step(hitRecord.GetIntersectionTime()));
        hitRecord.SetIntersectionMaterial(_material);

        // Arbitrary for a medium.
        hitRecord.SetIntersectionNormal(ray, glm::vec3(1.0f, 0.0f, 0.0f));
        hitRecord.SetOutwardFacing(true);
        return true;
    }

    bool Medium::GetAABB(AABB &aabb) const {
        return _object->GetAABB(aabb);
    }

}