
#ifndef RAYTRACER_MODEL_H
#define RAYTRACER_MODEL_H

#include <pch.h>
#include <raytracer/transform.h>
#include <raytracer/mesh.h>
#include <raytracer/intersectable.h>
#include <raytracer/intersections.h>

namespace RT {

    class Model : public Intersectable {
        public:
            Model(const Transform& transform, const Mesh& mesh, IMaterial* material);
            Model(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const Mesh& mesh, IMaterial* material);
            ~Model() override;

            [[nodiscard]] const Mesh& GetMesh() const;

            [[nodiscard]] bool Intersect(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

        private:
            void BuildModel();
            Mesh _mesh;
    };

}

#endif //RAYTRACER_MODEL_H
