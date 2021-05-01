
#include <raytracer/hit_record.h>

namespace RT {

    HitRecord::HitRecord() : _dt(std::numeric_limits<float>::max()) {
    }

    HitRecord::~HitRecord() = default;

    void HitRecord::SetIntersectionTime(float dt) {
        _dt = dt;
    }

    float HitRecord::GetIntersectionTime() const {
        return _dt;
    }

    void HitRecord::SetIntersectionPoint(const glm::vec3 &point) {
        _point = point;
    }

    const glm::vec3 &HitRecord::GetIntersectionPoint() const {
        return _point;
    }

    void HitRecord::SetIntersectionNormal(const Ray& ray, const glm::vec3 &normal) {
        // Ensure normal always points against the incident ray.
        _frontFacing = glm::dot(ray.GetDirection(), normal) < 0.0f;
        _normal = _frontFacing ? normal : -normal;
    }

    const glm::vec3 &HitRecord::GetIntersectionNormal() const {
        return _normal;
    }

    bool HitRecord::GetOutwardFacing() const {
        return _frontFacing;
    }

    void HitRecord::SetIntersectionUVs(const glm::vec2 &uv) {
        _uv = uv;
    }

    const glm::vec2 &HitRecord::GetIntersectionUVs() const {
        return _uv;
    }

    void HitRecord::SetIntersectionMaterial(IMaterial *material) {
        _material = material;
    }

    const IMaterial *HitRecord::GetIntersectionMaterial() const {
        return _material;
    }

}
