
#include <raytracer/hittable_factory.h>

// Objects.
#include <raytracer/sphere.h>

// Transforms.
#include <raytracer/rotate.h>
#include <raytracer/translate.h>

namespace RT {

    IHittable *CreateSphere(const glm::vec3 &position, const glm::vec3 &rotation, float radius, IMaterial *material) {
        // Create initial sphere.
        Sphere* sphere = new Sphere(glm::vec3(0.0f), radius, material);
        IHittable* rotated = new Rotate(sphere, rotation);
        IHittable* translated = new Translate(rotated, position);

        return translated;
    }
}
