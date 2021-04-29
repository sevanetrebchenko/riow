
#ifndef RAYTRACER_OBJECT_LOADER_H
#define RAYTRACER_OBJECT_LOADER_H

#include <pch.h>
#include <raytracer/mesh.h>

namespace RT {

    class OBJLoader {
        public:
            static OBJLoader& GetInstance();
            Mesh Load(const std::string& filepath);

        private:
            OBJLoader();
            ~OBJLoader();

            std::unordered_map<std::string, Mesh> _meshes;
    };

}

#endif //RAYTRACER_OBJECT_LOADER_H
