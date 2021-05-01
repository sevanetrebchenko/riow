//
//#include <raytracer/transform.h>
//
//namespace RT {
//
//    Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : _position(position),
//                                                                                                         _rotation(rotation),
//                                                                                                         _scale(scale)
//                                                                                                         {
//        CalculateMatrix();
//    }
//
//    Transform::~Transform() = default;
//
//    const glm::vec3 &Transform::GetPosition() const {
//        return _position;
//    }
//
//    const glm::vec3 &Transform::GetRotation() const {
//        return _rotation;
//    }
//
//    const glm::vec3 &Transform::GetScale() const {
//        return _scale;
//    }
//
//    const glm::mat4& Transform::GetMatrix() const {
//        return _matrix;
//    }
//
//    void Transform::CalculateMatrix() {
//        glm::mat4 translation = glm::translate(glm::mat4(1.0f), _position);
//        glm::mat4 scale = glm::scale(_scale);
//        glm::mat4 rotationX = glm::rotate(glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
//        glm::mat4 rotationY = glm::rotate(glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
//        glm::mat4 rotationZ = glm::rotate(glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
//
//        _matrix = translation * rotationX * rotationY * rotationZ * scale;
//    }
//
//}
