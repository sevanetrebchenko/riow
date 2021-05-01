
#include <raytracer/camera.h>
#include <raytracer/utility_math.h>

namespace RT {

    Camera::Camera(glm::vec3 eyePosition,
                   glm::vec3 lookAtPosition,
                   glm::vec3 globalUpVector,
                   float verticalFOV,
                   float aspectRatio,
                   float apertureLength,
                   float focusDistance) : _verticalFOV(verticalFOV),
                                          _globalUpVector(globalUpVector),
                                          _aspectRatio(aspectRatio),
                                          _eyePosition(eyePosition),
                                          _lookAtPosition(lookAtPosition),
                                          _lensRadius(apertureLength / 2.0f),
                                          _focusDistance(focusDistance)
                                          {
        CalculateCameraProperties();
    }

    void Camera::SetEyePosition(const glm::vec3 &eyePosition) {
        _eyePosition = eyePosition;
        CalculateCameraProperties();
    }

    void Camera::SetLookAtPosition(const glm::vec3 &lookAtPosition) {
        _lookAtPosition = lookAtPosition;
        CalculateCameraProperties();
    }

    void Camera::SetVerticalFOV(float fov) {
        _verticalFOV = fov;
        CalculateCameraProperties();
    }

    void Camera::CalculateCameraProperties() {
        // Distance was not set.
        if (_focusDistance == -1.0f) {
            _focusDistance = glm::length(_lookAtPosition - _eyePosition);
        }

        float theta = glm::radians(_verticalFOV);
        float height = std::tan(theta / 2.0f);

        float viewportHeight = 2.0f * height;
        float viewportWidth = viewportHeight * _aspectRatio;

        _forwardVector = glm::normalize(_eyePosition - _lookAtPosition);
        _rightVector = glm::normalize(glm::cross(_globalUpVector, _forwardVector));
        _upVector = glm::normalize(glm::cross(_forwardVector, _rightVector));

        _horizontal = _focusDistance * viewportWidth * _rightVector;
        _vertical = _focusDistance * viewportHeight * _upVector;
        _topLeftCorner = _eyePosition - _horizontal / 2.0f + _vertical / 2.0f - _focusDistance * _forwardVector;
    }

    Camera::~Camera() = default;

    Ray Camera::GetRay(float u, float v) const {
        // Focus blur with depth of field.
        glm::vec3 direction = _lensRadius * RandomDirectionInUnitDisk();

        // Start the ray offset a little around a disk surrounding the camera eye for it to purposefully "miss".
        // Rays that intersect sufficiently close to the focus distance will appear in focus.
        glm::vec3 startingRayPosition = _eyePosition + _horizontal * direction.x + _vertical * direction.y;

        return Ray(startingRayPosition, _topLeftCorner + u * _horizontal - v * _vertical - startingRayPosition);
    }

    float Camera::GetAspectRatio() const {
        return _aspectRatio;
    }

}
