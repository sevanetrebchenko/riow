
#include <raytracer/cube.h>
#include <raytracer/common.h>

namespace RT {

    Rectangle::Rectangle(const glm::vec3 &bottom, const glm::vec3 &top, int thinAxis, IMaterial *material) : _material(material),
                                                                                                             _min(bottom),
                                                                                                             _max(top),
                                                                                                             _thinAxis(thinAxis)
                                                                                                             {
        // Determine type of axis-aligned rectangle.
        switch (thinAxis) {
            // YZ rectangle.
            case 0:
                _mainAxis1 = Y_AXIS;
                _mainAxis2 = Z_AXIS;
                _normal = glm::vec3(1.0f, 0.0f, 0.0f);
                break;
            // XZ rectangle.
            case 1:
                _mainAxis1 = X_AXIS;
                _mainAxis2 = Z_AXIS;
                _normal = glm::vec3(0.0f, 1.0f, 0.0f);
                break;
            // XY rectangle.
            case 2:
                _mainAxis1 = X_AXIS;
                _mainAxis2 = Y_AXIS;
                _normal = glm::vec3(0.0f, 0.0f, 1.0f);
                break;
            default:
                throw std::runtime_error("Invalid thin axis provided to Rectangle constructor.");
        }

        ConstructAABB();
    }

    bool Rectangle::GetAABB(AABB &aabb) const {
        aabb = _aabb;
        return true;
    }

    bool Rectangle::ComputeIntersection(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
        const glm::vec3& origin = ray.GetOrigin();
        const glm::vec3& direction = ray.GetDirection();

        float intersectionTime = (_min[_thinAxis] - origin[_thinAxis]) / direction[_thinAxis];

        // Rectangle is behind the start of the ray, or ray is parallel.
        if (intersectionTime < tMin || intersectionTime > tMax) {
            return false;
        }

        float one = origin[_mainAxis1] + intersectionTime * direction[_mainAxis1];
        float two = origin[_mainAxis2] + intersectionTime * direction[_mainAxis2];

        // Make sure intersection coordinates are in the bounds of the rectangle.
        if (one < _min[_mainAxis1] || one > _max[_mainAxis1] || two < _min[_mainAxis2] || two > _max[_mainAxis2]) {
            return false;
        }

        // Construct hit record.
        hitRecord.SetIntersectionTime(intersectionTime);
        hitRecord.SetIntersectionPoint(ray.Step(intersectionTime));
        hitRecord.SetIntersectionNormal(ray, glm::vec3(0.0f, 0.0f, 1.0f)); // Hard-coded for xy rectangle.
        hitRecord.SetIntersectionUVs((one - _min[_mainAxis1]) / (_max[_mainAxis1] - _min[_mainAxis1]), (two - _min[_mainAxis2]) / (_max[_mainAxis2] - _min[_mainAxis2]));
        hitRecord.SetIntersectionMaterial(_material);

        return true;
    }

    void Rectangle::ConstructAABB() {
        static float lightThickness = 0.0001f;

        // Pad AABB in the thin axis for it not to be infinitesimally thin.
        // Negative.
        {
            glm::vec3 offset(0.0f);
            offset[_thinAxis] -= lightThickness;
            _aabb.minimum = _min + offset;
        }

        // Positive.
        {
            glm::vec3 offset(0.0f);
            offset[_thinAxis] += lightThickness;
            _aabb.maximum = _max + offset;
        }
    }



    XYRectangle::XYRectangle(const glm::vec2 &min, const glm::vec2 &max, float height, IMaterial *material) : Rectangle(glm::vec3(min.x, min.y, height), glm::vec3(max.x, max.y, height), Z_AXIS, material) {
    }

    XYRectangle::~XYRectangle() = default;

    bool XYRectangle::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        return ComputeIntersection(ray, tMin, tMax, hitRecord);
    }



    XZRectangle::XZRectangle(const glm::vec2 &min, const glm::vec2 &max, float height, IMaterial *material) : Rectangle(glm::vec3(min.x, height, min.y), glm::vec3(max.x, height, max.y), Y_AXIS, material) {
    }

    XZRectangle::~XZRectangle() = default;

    bool XZRectangle::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        return ComputeIntersection(ray, tMin, tMax, hitRecord);
    }



    YZRectangle::YZRectangle(const glm::vec2 &min, const glm::vec2 &max, float height, IMaterial *material) : Rectangle(glm::vec3(height, min.x, min.y), glm::vec3(height, max.x, max.y), X_AXIS, material) {
    }

    YZRectangle::~YZRectangle() = default;

    bool YZRectangle::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        return ComputeIntersection(ray, tMin, tMax, hitRecord);
    }

}
