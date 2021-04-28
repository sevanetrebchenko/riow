
#include "game_object.h"

// Transformations.
#include "translate.h"
#include "rotate.h"

namespace RT {

    IHittable* MakeSphere(const glm::vec3& translation, float scale, const glm::vec3& rotation, IMaterial* material) {
        // Construct base sphere.
        RT::IHittable* base = new RT::Sphere(translation, scale, material);

        // Apply transformations.
        RT::IHittable* rotated = new RT::Rotate(base, rotation);

        return rotated;
    }

    IHittable* MakeSphere(const glm::vec3& translation, const glm::vec3& scale, const glm::vec3& rotation, IMaterial* material) {
        return nullptr; // TODO: Ellipsoid
    }

}

