
#include <raytracer/camera.h>

namespace RT {

    Camera::Camera(glm::vec3 eyePosition,
                   glm::vec3 lookAtPosition,
                   glm::vec3 globalUpVector,
                   float verticalFOV,
                   float aspectRatio) : _verticalFOV(verticalFOV),
                                        _aspectRatio(aspectRatio),
                                        _eyePosition(eyePosition)
                                        {
        float theta = glm::radians(verticalFOV);
        float height = std::tan(theta / 2.0f);

        float viewportHeight = 2.0f * height;
        float viewportWidth = viewportHeight * _aspectRatio;

        _forwardVector = glm::normalize(eyePosition - lookAtPosition);
        _rightVector = glm::normalize(glm::cross(globalUpVector, _forwardVector));
        _upVector = glm::normalize(glm::cross(_forwardVector, _rightVector));

        float focalLength = 1.0f;

        _horizontal = viewportWidth * _rightVector;
        _vertical = viewportHeight * _upVector;
        _topLeftCorner = _eyePosition - _horizontal / 2.0f + _vertical / 2.0f - focalLength * _forwardVector;
    }

    Camera::~Camera() = default;

    Ray Camera::GetRay(float u, float v) const {
        return Ray(_eyePosition, _topLeftCorner + u * _horizontal - v * _vertical - _eyePosition);
    }

    float Camera::GetAspectRatio() const {
        return _aspectRatio;
    }

}
