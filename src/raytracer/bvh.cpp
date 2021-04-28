
#include "bvh.h"
#include "common.h"
#include "affine_math.h"

namespace RT {

    BVHNode::BVHNode() : _left(nullptr), _right(nullptr) {
    }

    BVHNode::BVHNode(IHittable* left, IHittable* right, const AABB& boundingBox) : _left(left), _right(right), _boundingBox(boundingBox) {
    }

    BVHNode::BVHNode(const std::vector<IHittable*>& objects, float tMin, float tMax) : _left(nullptr), _right(nullptr) {
        if (objects.empty()) {
            return;
        }

        if (objects.size() == 1) {
            IHittable* object = objects[0];

            _left = object;
            _right = nullptr;
            object->GetBoundingBox(tMin, tMax, _boundingBox);
        }
        else {
            // Construct list from objects.
            std::list<IHittable*> nodesList(objects.begin(), objects.end());

            while (nodesList.size() != 1) {
                CondenseBVHTree(nodesList, tMin, tMax);
            }

            *this = *dynamic_cast<BVHNode*>(*nodesList.begin());
        }
    }

    BVHNode::~BVHNode() {
    }

    bool BVHNode::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
        // Bounding box was not hit.
        if (!_boundingBox.Hit(ray, tMin, tMax)) {
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

    bool BVHNode::GetBoundingBox(float tMin, float tMax, AABB& boundingBox) const {
        boundingBox = _boundingBox;
        return true;
    }

    void BVHNode::CondenseBVHTree(std::list<IHittable*> &objects, float tMin, float tMax) {
        unsigned numObjects = objects.size();
        unsigned currentNumPairs = 0;
        bool unevenNumObjects = numObjects % 2 == 1;
        unsigned totalNumPairs = unevenNumObjects ? numObjects / 2 + 1 : numObjects / 2; // Uneven number of objects will have the last pairing be only one object.

        std::vector<bool> pairings;

        pairings.resize(numObjects);

        // Initially objects have no pairing.
        for (int i = 0; i < numObjects; ++i) {
            pairings[i] = false;
        }

        float minDistance = infinity;
        unsigned fistObjectID, secondObjectID;
        AABB firstObjectBoundingBox, secondObjectBoundingBox;

        for (int i = 0; i < numObjects; ++i) {
            bool foundPair = false;

            // Don't pair objects that have already been paired.
            if (pairings[i]) {
                continue;
            }

            fistObjectID = i;
            std::list<IHittable*>::iterator firstObjectIter = objects.begin();
            std::advance(firstObjectIter, fistObjectID);

            // Get first object data.
            (*firstObjectIter)->GetBoundingBox(tMin, tMax, firstObjectBoundingBox);
            const glm::vec3& firstObjectCenter = firstObjectBoundingBox.GetCenter();

            // Get the closest object to the current selected one.
            for (int j = 0; j < numObjects; ++j) {

                // Don't pair an object with itself.
                if (i == j) {
                    continue;
                }

                // Don't pair objects that have already been paired.
                if (pairings[j]) {
                    continue;
                }

                std::list<IHittable*>::iterator secondObjectIter = objects.begin();
                std::advance(secondObjectIter, j);

                // Get second object data.
                (*secondObjectIter)->GetBoundingBox(tMin, tMax, secondObjectBoundingBox);
                const glm::vec3& secondObjectCenter = secondObjectBoundingBox.GetCenter();

                float distance = DistanceSquared(firstObjectCenter, secondObjectCenter);

                // Found one closer.
                if (distance < minDistance) {
                    minDistance = distance;
                    secondObjectID = j;
                    foundPair = true;
                }
            }

            if (foundPair) {
                // Register pairing.
                pairings[fistObjectID] = true;
                pairings[secondObjectID] = true;

                // Recompute data for pairing (might have been invalidated during search).
                firstObjectIter = objects.begin();
                std::advance(firstObjectIter, fistObjectID);
                (*firstObjectIter)->GetBoundingBox(tMin, tMax, firstObjectBoundingBox);

                std::list<IHittable*>::iterator secondObjectIter = objects.begin();
                std::advance(secondObjectIter, secondObjectID);
                (*secondObjectIter)->GetBoundingBox(tMin, tMax, secondObjectBoundingBox);

                // Append to the end (this is safe because looping only happens for all the objects present in the list at
                // the time the function is called).
                objects.push_back(new BVHNode(*firstObjectIter, *secondObjectIter, AABB::Combine(firstObjectBoundingBox, secondObjectBoundingBox)));
                ++currentNumPairs;
            }

        }

        // Final pairing
        if (currentNumPairs != totalNumPairs) {
            // Find the ID of the object that has not been paired yet.
            for (int i = 0; i < numObjects; ++i) {
                if (!pairings[i]) {
                    // ID found, construct node with one end being a nullptr.
                    std::list<IHittable*>::iterator object = objects.begin();
                    std::advance(object, i);

                    // Get the node's bounding box.
                    AABB boundingBox;
                    (*object)->GetBoundingBox(tMin, tMax, boundingBox);

                    objects.push_back(new BVHNode(*object, nullptr, boundingBox));
                }
            }
        }

        // Clear out objects from previous iteration.
        for (int i = 0; i < numObjects; ++i) {
            objects.pop_front();
        }
    }

}
