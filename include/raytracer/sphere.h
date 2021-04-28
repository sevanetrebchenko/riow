
#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "glm/glm.hpp"
#include "hittable.h"
#include "hit_record.h"
#include "ray.h"
#include "material.h"
#include "transform.h"

namespace RT {

    // Record of an intersection of a ray and a Hittable object.
    class Sphere : public IHittable {
        public:
            Sphere(const glm::vec3& centerPosition, float radius, IMaterial* material);
            ~Sphere() override;

            bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            bool GetBoundingBox(float tMin, float tMax, AABB& boundingBox) const override;

        private:
            void ConstructBoundingBox();
            glm::vec2 CalculateUV(const glm::vec3& intersectionPoint) const;

            glm::vec3 _centerPosition;
            float _radius;

            IMaterial* _material;
            AABB _boundingBox;
    };

}

#endif //RAYTRACING_SPHERE_H
