
#include <raytracer/application.h>
#include <raytracer/hit_record.h>
#include <raytracer/material.h>
#include <raytracer/utility_math.h>
#include <raytracer/sphere.h>

namespace RT {

    Application::Application(const std::string &outputFilename, int width, int height) : _camera({ 0.0f, 0.0f, 8.0f },
                                                                                                 { 0.0f, 0.0f, 0.0f },
                                                                                                 { 0.0f, 1.0f, 0.0f },
                                                                                                 45,
                                                                                                 (float)width / (float)height,
                                                                                                 0.1f,
                                                                                                 glm::length(glm::vec3(0.0f, 0.0f, 8.0f) - glm::vec3(0.0f))),
                                                                                         _width(width),
                                                                                         _height(height),
                                                                                         _writer(new JPGWriter(outputFilename, width, height))
    {
    }

    Application::~Application() {
    }

    void Application::Init() {
        _collection.Add(new Sphere(glm::vec3(0.0f, -1001.0f, 0.0f), 1000.0f, new Lambertian(glm::vec3(0.5f))));
        _collection.Add(new Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, new Dielectric(1.33f)));
        _collection.Add(new Sphere(glm::vec3(-2.0f, 0.0f, 0.0f), 1.0f, new Metallic(glm::vec3(0.8f), 0.0f)));
        _collection.Add(new Sphere(glm::vec3(2.0f, 0.0f, 0.0f), 1.0f, new Metallic(glm::vec3(0.8f, 0.6f, 0.2f), 0.0f)));

        _collection.BuildBVH();
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

                _writer->WriteColor(x, y, pixelColor, samplesPerPixel);
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> millis = endTime - startTime;
        std::cout << "time to render: " << millis.count() << "ms";
    }

    void Application::Shutdown() {
        delete _writer;
    }

    glm::vec3 Application::RayColor(const Ray &ray, int numBounces) const {
        static glm::vec3 background(0.0f);

        HitRecord hitRecord;

        // Reached the limit to how many ray bounces each ray has.
        if (numBounces <= 0) {
            return background; // No color contribution.
        }

        // Ray does not intersect scene, return background color.
        if (_collection.Hit(ray, 0.001f, std::numeric_limits<float>::infinity(), hitRecord)) {
            Ray scattered;
            glm::vec3 attenuation;

            if (hitRecord.GetIntersectionMaterial()->GetScattered(ray, hitRecord, attenuation, scattered)) {
                return attenuation * RayColor(scattered, numBounces - 1);
            }
        }

        float t = 0.5f * (ray.GetDirection().y + 1.0f);
        return lerp(glm::vec3(0.5f, 0.7f, 1.0f), glm::vec3(1.0f), t);
    }

    void Application::CornellCube() {
        glm::vec3 redColor = glm::vec3(178.0f, 34.0f, 34.0f) / glm::vec3(255.0f);
        glm::vec3 greenColor = glm::vec3(0.0f, 128.0f, 0.0f) / glm::vec3(255.0f);

        glm::vec3 blue(0.0f, 0.0f, 1.0f);

//        // Red.
//        _collection.Add(new Model(glm::vec3(-16.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f), OBJLoader::GetInstance().Load("assets/cube.obj"), new Lambertian(redColor)));
//        // Green.
//        _collection.Add(new Model(glm::vec3(16.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f), OBJLoader::GetInstance().Load("assets/cube.obj"), new Lambertian(greenColor)));
//
//        glm::vec3 wallColor = glm::vec3(255.0f, 245.0f, 181.0f) / glm::vec3(255.0f);
//
//        // Floor.
//        _collection.Add(new Model(glm::vec3(0.0f, -16.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f), OBJLoader::GetInstance().Load("assets/cube.obj"), new Lambertian(wallColor)));
//        // Ceiling.
//        _collection.Add(new Model(glm::vec3(0.0f, 16.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f), OBJLoader::GetInstance().Load("assets/cube.obj"), new Lambertian(wallColor)));
//        // Back wall.
//        _collection.Add(new Model(glm::vec3(0.0f, 0.0f, -16.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f), OBJLoader::GetInstance().Load("assets/cube.obj"), new Lambertian(wallColor)));
//
//        // Cube 1.
//        _collection.Add(new Model(glm::vec3(2.0f, -4.0f, -4.0f), glm::vec3(0.0f, -20.0f, 0.0f), glm::vec3(2.0f), OBJLoader::GetInstance().Load("assets/cube.obj"), new Lambertian(blue)));
//        // Cube 2.
//        _collection.Add(new Model(glm::vec3(-7.0f, 0.0f, -7.0f), glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(3.0f, 6.0f, 3.0f), OBJLoader::GetInstance().Load("assets/cube.obj"), new Lambertian(blue)));
    }

}
