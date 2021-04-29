
#include <raytracer/model.h>

namespace RT {

    Model::Model(const Transform& transform, const Mesh& mesh, IMaterial* material) : Intersectable(transform, material),
                                                                                      _mesh(mesh)
                                                                                      {
        BuildModel();
    }

    Model::Model(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3 &scale, const Mesh &mesh, IMaterial *material) : Intersectable(position, rotation, scale, material),
                                                                                                                                        _mesh(mesh)
                                                                                                                                        {
        BuildModel();
    }

    Model::~Model() {
    }

    const Mesh &Model::GetMesh() const {
        return _mesh;
    }

    bool Model::Intersect(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        bool hasIntersected = false;

        // Loop through all triangles to determine ray-triangle intersection.
        for (const Triangle& triangle : _mesh.GetTriangles()) {
            float intersectionTime;

            // Check for intersection against all triangles.
            if (Intersects(ray, triangle, intersectionTime)) {

                // Bounds check.
                if (intersectionTime < tMin || intersectionTime > tMax) {
                    continue;
                }

                if (intersectionTime < hitRecord.dt) {
                    // Found closer intersection.
                    hitRecord.dt = intersectionTime;

                    glm::vec3 intersectionPoint = ray.Step(intersectionTime);
                    hitRecord.point = intersectionPoint;

                    glm::vec3 intersectionNormal = triangle.GetNormal(intersectionPoint);
                    hitRecord.SetNormal(ray, intersectionNormal);
                    hitRecord.material = triangle.GetMaterial();
                    hasIntersected = true;
                }
            }
        }

        return hasIntersected;
    }

    void Model::BuildModel() {
        const std::vector<Triangle>& triangles = _mesh.GetTriangles();

        std::vector<Triangle> meshTriangles(triangles);
        const glm::mat4& matrix = _transform.GetMatrix();

        // Apply model transform to triangle vertices / normals.
        for (int i = 0; i < triangles.size(); ++i) {
            meshTriangles[i].ApplyTransform(matrix);
            meshTriangles[i].SetMaterial(_material);
        }

        _mesh.SetTriangles(meshTriangles); // Update vertices.
    }


}
