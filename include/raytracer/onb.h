
#ifndef RAYTRACER_ONB_H
#define RAYTRACER_ONB_H

#include <pch.h>

namespace RT {

    class OrthonormalBasis {
        public:
            OrthonormalBasis(const glm::vec3& normal);
            ~OrthonormalBasis();

            glm::vec3 GetLocalVector(const glm::vec3& input) const;

        private:
            glm::vec3 _axes[3];
    };

}

#endif //RAYTRACER_ONB_H