
#include <raytracer/bvh.h>
#include <raytracer/common.h>

namespace RT {

    bool Compare(IHittable *left, IHittable *right, int axis) {
        AABB a;
        AABB b;

        if (!left->GetAABB(a) || !right->GetAABB(b)) {
            throw std::runtime_error("No bounding box in BVH node constructor.");
        }

        return a.minimum[axis] < b.minimum[axis];
    }

    bool CompareX(IHittable *left, IHittable *right) {
        return Compare(left, right, X_AXIS);
    }

    bool CompareY(IHittable *left, IHittable *right) {
        return Compare(left, right, Y_AXIS);
    }

    bool CompareZ(IHittable *left, IHittable *right) {
        return Compare(left, right, Z_AXIS);
    }


    BVHNode::BVHNode(const std::vector<IHittable*> &sceneObjects, int start, int end) {
        // Create a modifiable array of the source scene objects.
        std::vector<IHittable*> objects = sceneObjects;

        int axis = glm::linearRand(0, 2);
        auto comparator = (axis == X_AXIS) ? CompareX : (axis == Y_AXIS) ? CompareY : CompareZ;

        int numObjects = end - start;

        if (numObjects == 1) {
            // Only one object, duplicate into both child nodes.
            _left = objects[start];
            _right = objects[start];
        }
        else if (numObjects == 2) {
            if (Compare(objects[start], objects[start + 1], axis)) {
                _left = objects[start];
                _right = objects[start + 1];
            }
            else {
                _right = objects[start];
                _left = objects[start + 1];
            }
        }
        else {
            // Sort on a random axis.
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            int mid = start + numObjects / 2;
            _left = new BVHNode(objects, start, mid);
            _right = new BVHNode(objects, mid, end);
        }

        AABB left;
        AABB right;

        if (!_left->GetAABB(left) || !_right->GetAABB(right)) {
            throw std::runtime_error("No bounding box in BVH node constructor.");
        }

        _aabb = Combine(left, right);
    }

    BVHNode::~BVHNode() {

    }

    bool BVHNode::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        // Bounding box was not hit.
        if (!_aabb.Hit(ray, tMin, tMax)) {
            return false;
        }

        // Get the shortest intersection time.
        bool hitLeftSubtree = false;
        if (_left) {
            hitLeftSubtree = _left->Hit(ray, tMin, tMax, hitRecord);
        }

        bool hitRightSubtree = false;
        if (_right) {
            hitRightSubtree = _right->Hit(ray, tMin, hitLeftSubtree ? hitRecord.GetIntersectionTime() : tMax, hitRecord);
        }

        return hitLeftSubtree || hitRightSubtree;
    }

    bool BVHNode::GetAABB(AABB &boundingBox) const {
        boundingBox = _aabb;
        return true;
    }

}
