
#ifndef RAYTRACER_TRANSFORM_H
#define RAYTRACER_TRANSFORM_H

#include <raytracer/ray.h>
#include <raytracer/hit_record.h>

namespace RT {

    class Transform {
        public:
            Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
            ~Transform();

            [[nodiscard]] const glm::vec3& GetPosition() const;
            [[nodiscard]] const glm::vec3& GetRotation() const;
            [[nodiscard]] const glm::vec3& GetScale() const;
            [[nodiscard]] const glm::mat4& GetMatrix() const;

        private:
            void CalculateMatrix();
            glm::vec3 _position;
            glm::vec3 _rotation;
            glm::vec3 _scale;
            glm::mat4 _matrix;
    };

}

#endif //RAYTRACER_TRANSFORM_H
