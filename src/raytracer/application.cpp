
#include <raytracer/application.h>
#include <raytracer/hit_record.h>
#include <raytracer/material.h>
#include <raytracer/utility_math.h>
#include <raytracer/model.h>
#include <raytracer/object_loader.h>

namespace RT {

    Application::Application(const std::string &outputFilename, int width, int height) : _camera({ 0.0f, 2.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 90, (float)width / (float)height),
                                                                                         _width(width),
                                                                                         _height(height),
                                                                                         _writer(new JPGWriter(outputFilename, width, height))
    {
    }

    Application::~Application() {
    }

    void Application::Init() {
        _collection.Add(new Model(glm::vec3(0.0f, -1001.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1000.0f), OBJLoader::GetInstance().Load("assets/cube.obj"), new Metallic(glm::vec3(0.5f), 0.0f)));
        _collection.Add(new Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -35.0f, 0.0f), glm::vec3(1.0f), OBJLoader::GetInstance().Load("assets/cube.obj"), new Dielectric(1.55f)));
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
        HitRecord hitRecord;

        // Reached the limit to how many ray bounces each ray has.
        if (numBounces <= 0) {
            return glm::vec3(0.0f); // No color contribution.
        }

        if (_collection.Intersect(ray, 0.001f, std::numeric_limits<float>::infinity(), hitRecord)) {
            Ray scattered;
            glm::vec3 attenuation;

            if (hitRecord.material->GetScattered(ray, hitRecord, attenuation, scattered)) {
                return attenuation * RayColor(scattered, numBounces - 1);
            }
        }

        float t = 0.5f * (ray.GetDirection().y + 1.0f);
        return lerp(glm::vec3(0.5f, 0.7f, 1.0f), glm::vec3(1.0f), t);
    }

}
