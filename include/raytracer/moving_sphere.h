
#ifndef RAYTRACING_MOVING_SPHERE_H
#define RAYTRACING_MOVING_SPHERE_H

#include "glm/glm.hpp"
#include "hittable.h"
#include "material.h"

namespace RT {

    class MovingSphere : public IHittable {
        public:
            MovingSphere(glm::vec3 centerPosition1, float timePosition1, glm::vec3 centerPosition2, float timePosition2, float radius, IMaterial* material);
            ~MovingSphere();

            bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            bool GetBoundingBox(float tMin, float tMax, AABB& boundingBox) const override;

        private:
            glm::vec3 CenterAtTime(float time) const;
            glm::vec2 CalculateUV(const glm::vec3& intersectionPoint) const;

            glm::vec3 _centerPosition1;
            float _timePosition1;
            glm::vec3 _centerPosition2;
            float _timePosition2;
            float _radius;
            IMaterial* _material;
    };

}

#endif //RAYTRACING_MOVING_SPHERE_H
