
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
                   float aspectRatio,
                   float apertureLength,
                   float focusDistance);
            ~Camera();

            [[nodiscard]] Ray GetRay(float u, float v) const;
            [[nodiscard]] float GetAspectRatio() const;

        private:
            // Camera lens properties.
            float _verticalFOV;
            float _aspectRatio;
            float _lensRadius;
            float _focusDistance;

            glm::vec3 _eyePosition;

            // Camera orientation vectors.
            glm::vec3 _globalUpVector;
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
