
#include <raytracer/application.h>
#include <raytracer/utility_math.h>
#include <raytracer/hit_record.h>
#include <raytracer/material.h>

namespace RT {

    Application::Application(const std::string &outputFilename, int width, int height) : _camera({ 0.0f, 0.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 90, (float)width / (float)height),
                                                                                         _width(width),
                                                                                         _height(height),
                                                                                         _writer(outputFilename, width, height)
                                                                                         {
    }

    Application::~Application() {
    }

    void Application::Init() {
        BunnyScene();
        _root = _modelManager.BuildBVH();
    }

    void Application::Run() {
        float u, v;
        int lineCounter = _height;
        int samplesPerPixel = 8;
        int numRayBounces = 10;

        auto startTime = std::chrono::high_resolution_clock::now();

        for (int y = 0; y < _height; ++y) {
            std::cout << "rows remaining: " << lineCounter-- << " " << std::endl;

            for (int x = 0; x < _width; ++x) {
                glm::vec3 pixelColor(0.0f, 0.0f, 0.0f);

                // Antialiasing.
                for (int sample = 0; sample < samplesPerPixel; ++sample) {
                    u = ((float)x + glm::linearRand(0.0f, 1.0f)) / (float)(_width - 1);
                    v = ((float)y + glm::linearRand(0.0f, 1.0f)) / (float)(_height - 1);

                    pixelColor += RayColor(_camera.GetRay(u, v), numRayBounces);
                }

                _writer.WriteColor(x, y, pixelColor, samplesPerPixel);
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> millis = endTime - startTime;
        std::cout << "time to render: " << millis.count() << "ms";
    }

    void Application::Shutdown() {
    }

    void Application::BunnyScene() {
        // Bunny.
        Transform bunnyTransform;
        Mesh bunnyMesh = OBJLoader::GetInstance().Load("assets/models/bunny.obj");
        bunnyMesh.SetNormalPosition(NormalPosition::VERTEX);
        _modelManager.AddModel(new Dielectric(1.55f), bunnyTransform, bunnyMesh);

//        // Cup.
//        Transform cup;
//        cup.SetScale(glm::vec3(3.0f));
//        cup.SetPosition(glm::vec3(-1.0f, 0.0f, -3.0f));
//        cup.SetRotation(glm::vec3(0.0f, -15.0f, 0.0f));
//        _modelManager.AddModel(new Metallic(glm::vec3(0.0f, 0.4f, 0.1f), 1.0f), cup, OBJLoader::GetInstance().Load("assets/models/cup.obj"));
//
        // Sphere.
        Transform sphere;
        sphere.SetScale(glm::vec3(1.5f));
        sphere.SetPosition(glm::vec3(1.5f, sphere.GetScale().y / 2.0f, -2.0f));
        Mesh sphereMesh = OBJLoader::GetInstance().Load("assets/models/sphere.obj");
        sphereMesh.SetNormalPosition(NormalPosition::VERTEX);
        _modelManager.AddModel(new Metallic(glm::vec3(0.4f, 0.1f, 0.1f), 0.05f), sphere, sphereMesh);

        // Floor.
        Transform floor;
        floor.SetScale(glm::vec3(30.0f, 1.0f, 30.0f));
        floor.SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
        _modelManager.AddModel(new Lambertian(glm::vec3(0.5f)), floor, OBJLoader::GetInstance().Load("assets/models/cube.obj"));
    }

    void Application::CornellBox() {
//        OBJLoader& objectLoader = RT::OBJLoader::GetInstance();
//
//        // Walls.
//        float wallWidth = 5.5f;
//        float wallThickness = 0.5f;
//
//        // Ceiling
//        Transform ceiling;
//        ceiling.SetPosition(glm::vec3(0.0f, 5.0f, 2.0f));
//        ceiling.SetScale(glm::vec3(wallWidth, wallThickness, wallWidth));
//        _modelManager.AddModel(ceiling, objectLoader.Load("assets/models/cube.obj"));
//
//        // Floor.
//        Transform floor;
//        floor.SetPosition(glm::vec3(0.0f, -5.0f, 2.0f));
//        floor.SetScale(glm::vec3(wallWidth, wallThickness, wallWidth));
//        _modelManager.AddModel(floor, objectLoader.Load("assets/models/cube.obj"));
//
//        // Left wall.
//        Transform left;
//        left.SetPosition(glm::vec3(-5.0f, 0.0f, 2.0f));
//        left.SetScale(glm::vec3(wallThickness, wallWidth, wallWidth));
//        _modelManager.AddModel(left, objectLoader.Load("assets/models/cube.obj"));
//
//        // Right wall.
//        Transform right;
//        right.SetPosition(glm::vec3(5.0f, 0.0f, 2.0f));
//        right.SetScale(glm::vec3(wallThickness, wallWidth, wallWidth));
//        _modelManager.AddModel(right, objectLoader.Load("assets/models/cube.obj"));
//
//        // Back wall.
//        Transform back;
//        back.SetPosition(glm::vec3(0.0f, 0.0f, 2.5f));
//        back.SetScale(glm::vec3(wallWidth, wallWidth, wallThickness));
//        _modelManager.AddModel(back, objectLoader.Load("assets/models/cube.obj"));

        // Cube 1.
//        Transform cube1;
//        cube1.SetPosition(glm::vec3(-2.0f, 1.0f, 3.0f));
//        cube1.SetRotation(glm::vec3(0.0f, 15.0f, 0.0f));
//        cube1.SetScale(glm::vec3(3.0f, 6.0f, 3.0f));
//        _modelManager.AddModel(cube1, objectLoader.Load("assets/models/cube.obj"));

        // Cube 2.
    }

    glm::vec3 Application::RayColor(const Ray &ray, int numBounces) const {
        static glm::vec3 backgroundColor(0.0f, 0.0f, 0.0f);
        HitRecord hitRecord;

        // Reached the limit to how many ray bounces each ray has.
        if (numBounces <= 0) {
            return glm::vec3(0.0f); // No color contribution.
        }

        // Intersect ray with all objects in the scene.

        // If the ray hits nothing, return the background color.
        if (!_root->Hit(ray, 0.001f, std::numeric_limits<float>::infinity(), hitRecord)) {
            // return (hitRecord.normal + glm::vec3(1.0f)) / 2.0f;
            return backgroundColor;
        }

        Ray scattered;
        glm::vec3 attenuation;
        glm::vec3 emitted = hitRecord.material->GetEmitted(0.0f, 0.0f, hitRecord.point); // Temporary, no uvs.

        // Ray hit light, no scatter.
        if (!hitRecord.material->GetScattered(ray, hitRecord, attenuation, scattered)) {
            return emitted;
        }

        return emitted + attenuation * RayColor(scattered, numBounces - 1);
    }

}
