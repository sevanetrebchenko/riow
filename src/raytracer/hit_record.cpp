
#include <raytracer/hit_record.h>

namespace RT {

    HitRecord::HitRecord() : dt(std::numeric_limits<float>::max()) {
    }

    void HitRecord::SetNormal(const Ray& ray, const glm::vec3& n) {
        outwardFacing = glm::dot(ray.GetDirection(), n) < 0.0f;
        normal = outwardFacing ? n : -n;
    }

}
