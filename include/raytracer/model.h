
#ifndef RAYTRACER_MODEL_H
#define RAYTRACER_MODEL_H

#include <pch.h>
#include <raytracer/transform.h>
#include <raytracer/mesh.h>

namespace RT {

    class Model {
        public:
            Model(IMaterial* material, const Transform& transform, const Mesh& mesh);
            ~Model();

            [[nodiscard]] const Mesh& GetMesh() const;

        private:
            Mesh _mesh;
            Transform _transform;
            IMaterial* _material;
    };

}

#endif //RAYTRACER_MODEL_H
