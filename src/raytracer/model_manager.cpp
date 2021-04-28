
#include <raytracer/model_manager.h>

namespace RT {

    ModelManager::ModelManager() {
    }

    ModelManager::~ModelManager() {
        for (Model* model : _modelList) {
            delete model;
        }
    }

    void ModelManager::AddModel(IMaterial* material, const Transform &transform, const Mesh &mesh) {
        _modelList.push_back(new Model(material, transform, mesh));
    }

    void ModelManager::AddModel(Model* model) {
        _modelList.push_back(model);
    }

    OctreeNode* ModelManager::BuildBVH() {
        // Combine all mesh data into one mesh.
        std::vector<Triangle> combinedTriangles;

        for (const Model* model : _modelList) {
            for (const Triangle& triangle : model->GetMesh().GetTriangles()) {
                combinedTriangles.push_back(triangle);
            }
        }

        AABB combinedAABB = GetAABB(combinedTriangles);

        Mesh combinedMesh;
        combinedMesh.SetTriangles(combinedTriangles);

        return new OctreeNode(combinedAABB, combinedMesh); // Constructs top-down scene octree.
    }

}
