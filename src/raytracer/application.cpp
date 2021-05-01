
#include <raytracer/application.h>
#include <raytracer/hit_record.h>
#include <raytracer/hittable_factory.h>
#include <raytracer/material.h>
#include <raytracer/utility_math.h>
#include <raytracer/sphere.h>
#include <raytracer/cube.h>
#include <raytracer/light.h>

namespace RT {

    Application::Application(const std::string &outputFilename, int width, int height) : _camera(glm::vec3(26.0f, 3.0f, 6.0f),
                                                                                                 glm::vec3(0.0f, 2.0f, 0.0f),
                                                                                                 glm::vec3(0.0f, 1.0f, 0.0f),
                                                                                                 20,
                                                                                                 (float)width / (float)height,
                                                                                                 0.0f),
                                                                                         _width(width),
                                                                                         _height(height),
                                                                                         _writer(new JPGWriter(outputFilename, width, height))
    {
    }

    Application::~Application() {
    }

    void Application::Init() {
//        // Floor.
//        _collection.Add(new Sphere(glm::vec3(0.0f, -1001.0f, 0.0f), 1000.0f, new Lambertian(glm::vec3(0.5f))));
////
////        _collection.Add(new Sphere(glm::vec3(-2.0f, 0.0f, 0.0f), 1.0f, new Metallic(glm::vec3(0.8f), 0.0f)));
////        _collection.Add(new Sphere(glm::vec3(2.0f, 0.0f, 0.0f), 1.0f, new Metallic(glm::vec3(0.8f, 0.6f, 0.2f), 0.0f)));
//
//        IHittable* sphere = CreateSphere(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(45.0f, 45.0f, 0.0f), 2.0f, new Lambertian(new ImageTexture("assets/textures/earthmap.jpg")));
//        _collection.Add(sphere);
//
//        // Light.
//        _collection.Add(new YZRectangle(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), 6.0f, new Light(glm::vec3(10.0f))));

        CornellBox();
        _collection.BuildBVH();
    }

    void Application::Run() {
        float u, v;
        int lineCounter = _height;
        int samplesPerPixel = 100;
        int numRayBounces = 8;

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
        if (!_collection.Hit(ray, 0.001f, std::numeric_limits<float>::infinity(), hitRecord)) {
            return background;
        }

        const IMaterial* material = hitRecord.GetIntersectionMaterial();

        Ray scattered;
        glm::vec3 attenuation;
        glm::vec3 emitted = material->GetEmitted(hitRecord.GetIntersectionUVs(), hitRecord.GetIntersectionPoint());

        // Ray hit light (lights do not scatter, return only emitted light.
        if (!material->GetScattered(ray, hitRecord, attenuation, scattered)) {
            return emitted;
        }

        return emitted + attenuation * RayColor(scattered, numBounces - 1);
    }

    void Application::CornellBox() {
        // Configure camera.
        _camera.SetEyePosition(glm::vec3(278.0f, 278.0f, -750.0f));
        _camera.SetLookAtPosition(glm::vec3(278.0f, 278.0f, 0.0f));
        _camera.SetVerticalFOV(40.0f);

        // Configure scene objects.
        Lambertian* red = new Lambertian(glm::vec3(0.65f, 0.05f, 0.05f));
        Lambertian* white = new Lambertian(glm::vec3(0.73f));
        Lambertian* green = new Lambertian(glm::vec3(0.12f, 0.45f, 0.15f));
        Light* light = new Light(glm::vec3(15.0f));

        // Green wall.
        _collection.Add(new YZRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(555.0f, 555.0f), 555.0f, green));

        // Red wall.
        _collection.Add(new YZRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(555.0f, 555.0f), 0.0f, red));

        // Light.
        _collection.Add(new XZRectangle(glm::vec2(213.0f, 227.0f), glm::vec2(343.0f, 332.0f), 554.0f, light));

        // White walls.
        _collection.Add(new XZRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(555.0f, 555.0f), 0.0f, white));
        _collection.Add(new XZRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(555.0f, 555.0f), 555.0f, white));
        _collection.Add(new XYRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(555.0f, 555.0f), 555.0f, white));

        // Cubes.
        _collection.Add(CreateCube(glm::vec3(265.0f, 0.0f, 295.0f), glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(165.0f, 330.0f, 165.0f), white));
        _collection.Add(CreateCube(glm::vec3(130.0f, 0.0f, 65.0f), glm::vec3(0.0f, -18.0f, 0.0f), glm::vec3(165.0f, 165.0f, 165.0f), white));
    }

}
