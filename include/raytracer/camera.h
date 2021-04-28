
#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <pch.h>
#include <raytracer/ray.h>

namespace RT {

    class Camera {
        public:
            Camera(glm::vec3 eyePosition,
                   glm::vec3 lookAt,
                   glm::vec3 up,
                   float verticalFOV,
                   float aspectRatio);
            ~Camera();

            [[nodiscard]] Ray GetRay(float u, float v) const;
            [[nodiscard]] float GetAspectRatio() const;

        private:
            // Camera lens properties.
            float _verticalFOV;
            float _aspectRatio;

            glm::vec3 _eyePosition;

            // Camera orientation vectors.
            glm::vec3 _upVector;
            glm::vec3 _forwardVector;
            glm::vec3 _rightVector;

            // Viewport orientation vectors.
            glm::vec3 _topLeftCorner;
            glm::vec3 _horizontal;
            glm::vec3 _vertical;
    };
}

#endif //RAYTRACER_CAMERA_H
