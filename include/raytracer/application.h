
#ifndef RAYTRACER_APPLICATION_H
#define RAYTRACER_APPLICATION_H

#include <pch.h>
#include <raytracer/writer.h>
#include <raytracer/camera.h>
#include <raytracer/ray.h>
#include <raytracer/intersectable_collection.h>

namespace RT {

    class Application {
        public:
            Application(const std::string& outputFilename, int width, int height);
            ~Application();

            void Init();
            void Run();
            void Shutdown();

        private:
            [[nodiscard]] glm::vec3 RayColor(const Ray& ray, int numBounces) const;

            Camera _camera;
            IntersectableCollection _collection;

            int _width;
            int _height;
            IWriter* _writer;
    };

}

#endif //RAYTRACER_APPLICATION_H
