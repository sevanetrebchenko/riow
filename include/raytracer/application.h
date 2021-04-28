
#ifndef RAYTRACER_APPLICATION_H
#define RAYTRACER_APPLICATION_H

#include <raytracer/writers/image_writer.h>
#include <raytracer/camera.h>
#include <raytracer/model_manager.h>
#include <raytracer/object_loader.h>
#include <raytracer/ray.h>

namespace RT {

    class Application {
        public:
            Application(const std::string& outputFilename, int width, int height);
            ~Application();

            void Init();
            void Run();
            void Shutdown();

        private:
            void BunnyScene();
            void CornellBox();

            [[nodiscard]] glm::vec3 RayColor(const Ray& ray, int numBounces) const;

            ModelManager _modelManager;
            Camera _camera;

            int _width;
            int _height;
            IWriter* _writer;
    };

}

#endif //RAYTRACER_APPLICATION_H
