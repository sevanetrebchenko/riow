
#include <raytracer/model.h>
#include <utility>

namespace RT {

    Model::Model(IMaterial* material, const Transform& transform, const Mesh& mesh) : _material(material),
                                                                                      _transform(transform),
                                                                                      _mesh(mesh)
                                                                                      {
        const std::vector<Triangle>& triangles = mesh.GetTriangles();

        std::vector<Triangle> meshTriangles(triangles);
        glm::mat4 matrix = _transform.GetMatrix();

        // Apply model transform to triangle vertices / normals.
        for (int i = 0; i < triangles.size(); ++i) {
            meshTriangles[i].ApplyTransform(matrix);
            meshTriangles[i].SetMaterial(material);
        }

        _mesh.SetTriangles(meshTriangles); // Update vertices.
    }

    Model::~Model() {

    }

    const Mesh &Model::GetMesh() const {
        return _mesh;
    }

}
