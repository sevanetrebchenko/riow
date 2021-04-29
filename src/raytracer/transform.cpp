
#include <raytracer/transform.h>

namespace RT {

    Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : _position(position),
                                                                                                         _rotation(rotation),
                                                                                                         _scale(scale)
                                                                                                         {
        CalculateMatrix();
    }

    Transform::~Transform() = default;

    const glm::vec3 &Transform::GetPosition() const {
        return _position;
    }

    const glm::vec3 &Transform::GetRotation() const {
        return _rotation;
    }

    const glm::vec3 &Transform::GetScale() const {
        return _scale;
    }

    Ray Transform::TransformRay(const Ray &input) const {
        glm::vec3 origin = input.GetOrigin();
        glm::vec3 direction = input.GetDirection();

        // Translation affects only origin.
        origin -= _position;

        // Rotation affects both origin and direction.
        glm::mat4 rotationX = glm::rotate(glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotationY = glm::rotate(glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotationZ = glm::rotate(glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 matrix = rotationX * rotationY * rotationZ;

        origin = matrix * glm::vec4(origin, 1.0f);
        direction = matrix * glm::vec4(direction, 0.0f);

        return Ray(origin, direction);
    }

    void Transform::UndoTransform(const Ray &transformed, HitRecord &hitRecord) const {
        Ray undo = transformed;

        // Undo rotation.
        {
            glm::mat4 rotationX = glm::rotate(glm::radians(-_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 rotationY = glm::rotate(glm::radians(-_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 rotationZ = glm::rotate(glm::radians(-_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

            glm::mat4 matrix = rotationZ * rotationY * rotationX;

            // Reverse order for hit record.
            hitRecord.point = matrix * glm::vec4(hitRecord.point, 1.0f);
            hitRecord.normal = matrix * glm::vec4(hitRecord.normal, 0.0f);

            // Recompute ray without rotation.
            glm::vec3 origin = matrix * glm::vec4(undo.GetOrigin(), 1.0f);
            glm::vec3 direction = matrix * glm::vec4(undo.GetDirection(), 0.0f);
            undo = Ray(origin, direction);

            // Update normal.
            bool outwardFacing = glm::dot(transformed.GetDirection(), hitRecord.normal) < 0.0f;
            hitRecord.outwardFacing = outwardFacing;
            hitRecord.normal = outwardFacing ? hitRecord.normal : -hitRecord.normal;
        }

        // Undo translation.
        {
            hitRecord.point += _position;

            // Update normal.
            bool outwardFacing = glm::dot(undo.GetDirection(), hitRecord.normal) < 0.0f;
            hitRecord.outwardFacing = outwardFacing;
            hitRecord.normal = outwardFacing ? hitRecord.normal : -hitRecord.normal;
        }
    }

    void Transform::CalculateMatrix() {
        // to transforms initial ray to dimensions specified by this transform.


        // for transforms transformed ray back to initial conditions.
    }

}
