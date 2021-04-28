
#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <pch.h>

namespace RT {

    class Ray {
        public:
            explicit Ray(const glm::vec3& origin = glm::vec3(0.0f), const glm::vec3& direction = glm::vec3(0.0f));
            ~Ray();

            [[nodiscard]] const glm::vec3& GetOrigin() const;
            [[nodiscard]] const glm::vec3& GetDirection() const;

            [[nodiscard]] glm::vec3 Step(float t) const;

        private:
            glm::vec3 _direction;
            glm::vec3 _origin;
    };

}

#endif //RAYTRACER_RAY_H
