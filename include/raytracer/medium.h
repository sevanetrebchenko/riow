
#ifndef RAYTRACER_MEDIUM_H
#define RAYTRACER_MEDIUM_H

#include <raytracer/hittable.h>
#include <raytracer/texture.h>

namespace RT {

    class Medium : public IHittable {
        public:
            Medium(IHittable* object, float density, const glm::vec3& color);
            Medium(IHittable* object, float density, ITexture* texture);
            ~Medium() override;

            [[nodiscard]] bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
            [[nodiscard]] bool GetAABB(AABB& aabb) const override;

        private:
            IHittable* _object;
            IMaterial* _material;
            float _density;
    };

}

#endif //RAYTRACER_MEDIUM_H
