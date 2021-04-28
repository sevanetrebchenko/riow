
#ifndef RAYTRACER_MODEL_MANAGER_H
#define RAYTRACER_MODEL_MANAGER_H

#include <raytracer/transform.h>
#include <raytracer/mesh.h>
#include <raytracer/model.h>
#include <raytracer/octree_node.h>

namespace RT {

    class ModelManager {
        public:
            ModelManager();
            ~ModelManager();

            void AddModel(IMaterial* material, const Transform& transform, const Mesh& mesh);
            void AddModel(Model* model);

            OctreeNode* BuildBVH();

        private:
            std::vector<Model*> _modelList;
    };

}

#endif //RAYTRACER_MODEL_MANAGER_H
