
#include <raytracer/hittable_factory.h>

// Objects.
#include <raytracer/sphere.h>
#include <raytracer/cube.h>

// Transforms.
#include <raytracer/rotate.h>
#include <raytracer/translate.h>

namespace RT {

    IHittable *CreateSphere(const glm::vec3 &position, const glm::vec3 &rotation, float radius, IMaterial *material) {
        // Create initial sphere.
        IHittable* sphere = new Sphere(glm::vec3(0.0f), radius, material);
        sphere = new Rotate(sphere, rotation);
        sphere = new Translate(sphere, position);

        return sphere;
    }

    IHittable *CreateCube(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3& scale, IMaterial *material) {
        // Create initial cube.
        IHittable* cube = new Cube(glm::vec3(0.0f), scale, material);
        cube = new Rotate(cube, rotation);
        cube = new Translate(cube, position);

        return cube;
    }
}
