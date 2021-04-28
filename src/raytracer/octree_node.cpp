
#include <raytracer/octree_node.h>
#include <raytracer/intersections.h>
#include <raytracer/utility_math.h>
#include <utility>

namespace RT {

    unsigned OctreeNode::maxNumTriangles = 100u;

    OctreeNode::OctreeNode(const AABB& bounds, const Mesh& mesh) : _bounds(bounds),
                                                                   _mesh(mesh)
                                                                   {
        // Children all start as null.
        for (int i = 0; i < 8; ++i) {
            _children[i] = nullptr;
        }

        unsigned numTriangles = _mesh.GetTriangles().size();
        if (numTriangles > maxNumTriangles) {
            Split();
        }
    }

    OctreeNode::~OctreeNode() {
        for (int i = 0; i < 8; ++i) {
            delete _children[i];
        }
    }

    glm::vec4 OctreeNode::CalculatePlane(int axis) const {
        const glm::vec3& nodePosition = _bounds.GetCenter();

        // Construct plane.
        glm::vec3 offset1(0.0f);
        offset1[(axis + 1) % 3] = 1.0f;
        offset1[(axis + 2) % 3] = 1.0f;

        glm::vec3 offset2(0.0f);
        offset2[(axis + 1) % 3] = 1.0f;

        glm::vec3 offset3(0.0f);
        offset3[(axis + 2) % 3] = 1.0f;

        glm::vec3 point1 = nodePosition + offset1;
        glm::vec3 point2 = nodePosition + offset2;
        glm::vec3 point3 = nodePosition + offset3;

        // Plane normal points along the positive axis.
        glm::vec3 planeNormal = -glm::normalize(glm::cross(point2 - point1, point3 - point1));
        float d = glm::dot(planeNormal, point1);

        return glm::vec4(planeNormal, d);
    }

    void OctreeNode::Split() {
        const glm::vec3& position = _bounds.GetCenter();
        unsigned numParentTriangles = _mesh.GetTriangles().size();

        // Split across x axis.
        SplitMesh dataLeftRight = SplitMeshAcrossPlane(_mesh, CalculatePlane(X_AXIS));
        Mesh& left = dataLeftRight.negativeHPMesh;
        Mesh& right = dataLeftRight.positiveHPMesh;

//        if (!SplitReducedTriangles(numParentTriangles, dataLeftRight)) {
//            return;
//        }

        // Split across y axis.
        SplitMesh dataLeftTopBottom = SplitMeshAcrossPlane(left, CalculatePlane(Y_AXIS));
        Mesh& leftBottom = dataLeftTopBottom.negativeHPMesh;
        Mesh& leftTop = dataLeftTopBottom.positiveHPMesh;

//        if (!SplitReducedTriangles(numParentTriangles, dataLeftTopBottom)) {
//            return;
//        }

        SplitMesh dataRightTopBottom = SplitMeshAcrossPlane(right, CalculatePlane(Y_AXIS));
        Mesh& rightBottom = dataRightTopBottom.negativeHPMesh;
        Mesh& rightTop = dataRightTopBottom.positiveHPMesh;

//        if (!SplitReducedTriangles(numParentTriangles, dataRightTopBottom)) {
//            return;
//        }

        // Split across z axis.
        // Left
        SplitMesh dataLeftTopFrontBack = SplitMeshAcrossPlane(leftTop, CalculatePlane(Z_AXIS));
        Mesh& leftTopBack = dataLeftTopFrontBack.negativeHPMesh;
        Mesh& leftTopFront = dataLeftTopFrontBack.positiveHPMesh;

//        if (!SplitReducedTriangles(numParentTriangles, dataLeftTopFrontBack)) {
//            return;
//        }

        SplitMesh dataLeftBottomFrontBack = SplitMeshAcrossPlane(leftBottom, CalculatePlane(Z_AXIS));
        Mesh& leftBottomBack = dataLeftBottomFrontBack.negativeHPMesh;
        Mesh& leftBottomFront = dataLeftBottomFrontBack.positiveHPMesh;

//        if (!SplitReducedTriangles(numParentTriangles, dataLeftBottomFrontBack)) {
//            return;
//        }

        // Right
        SplitMesh dataRightTopFrontBack = SplitMeshAcrossPlane(rightTop, CalculatePlane(Z_AXIS));
        Mesh& rightTopBack = dataRightTopFrontBack.negativeHPMesh;
        Mesh& rightTopFront = dataRightTopFrontBack.positiveHPMesh;

//        if (!SplitReducedTriangles(numParentTriangles, dataRightTopFrontBack)) {
//            return;
//        }

        SplitMesh dataRightBottomFrontBack = SplitMeshAcrossPlane(rightBottom, CalculatePlane(Z_AXIS));
        Mesh& rightBottomBack = dataRightBottomFrontBack.negativeHPMesh;
        Mesh& rightBottomFront = dataRightBottomFrontBack.positiveHPMesh;

//        if (!SplitReducedTriangles(numParentTriangles, dataRightBottomFrontBack)) {
//            return;
//        }

        // Create 8 children nodes.
        const glm::vec3& center = _bounds.GetCenter();
        const glm::vec3& scale = (_bounds.maximum - _bounds.minimum) / 2.0f;

        // Looking along the negative z axis.

        // Bottom left front.
        {
            glm::vec3 min = center + glm::vec3(-scale.x, -scale.y, 0.0f);
            glm::vec3 max = center + glm::vec3(0.0f, 0.0f, scale.z);
            _children[0] = new OctreeNode(AABB(min, max), leftBottomFront);
        }

        // Bottom left back.
        {
            glm::vec3 min = center + glm::vec3(-scale.x, -scale.y, -scale.z);
            glm::vec3 max = center;
            _children[1] = new OctreeNode(AABB(min, max), leftBottomBack);
        }

        // Bottom right front.
        {
            glm::vec3 min = center + glm::vec3(0.0f, -scale.y, 0.0f);
            glm::vec3 max = center + glm::vec3(scale.x, 0.0f, scale.z);
            _children[2] = new OctreeNode(AABB(min, max), rightBottomFront);
        }

        // Bottom right back.
        {
            glm::vec3 min = center + glm::vec3(0.0f, -scale.y, -scale.z);
            glm::vec3 max = center + glm::vec3(scale.x, 0.0f, 0.0f);
            _children[3] = new OctreeNode(AABB(min, max), rightBottomBack);
        }

        // Top left front.
        {
            glm::vec3 min = center + glm::vec3(-scale.x, 0.0f, 0.0f);
            glm::vec3 max = center + glm::vec3(0.0f, scale.y, scale.z);
            _children[4] = new OctreeNode(AABB(min, max), leftTopFront);
        }

        // Top left back.
        {
            glm::vec3 min = center + glm::vec3(-scale.x, 0.0f, -scale.z);
            glm::vec3 max = center + glm::vec3(0.0f, scale.y, 0.0f);
            _children[5] = new OctreeNode(AABB(min, max), leftTopBack);
        }

        // Top right front.
        {
            glm::vec3 min = center;
            glm::vec3 max = center + glm::vec3(scale.x, scale.y, scale.z);
            _children[6] = new OctreeNode(AABB(min, max), rightTopFront);
        }

        // Top right back.
        {
            glm::vec3 min = center + glm::vec3(0.0f, 0.0f, -scale.z);
            glm::vec3 max = center + glm::vec3(scale.x, scale.y, 0.0f);
            _children[7] = new OctreeNode(AABB(min, max), rightTopBack);
        }
    }

    bool OctreeNode::SplitReducedTriangles(unsigned numParentTriangles, const SplitMesh& data) const {
        if (data.positiveHPMesh.GetTriangles().size() >= numParentTriangles || data.negativeHPMesh.GetTriangles().size() >= numParentTriangles) {
            return false;
        }

        return true;
    }

    OctreeNode::SplitMesh OctreeNode::SplitMeshAcrossPlane(const Mesh &mesh, const glm::vec4 &plane) {
        std::vector<Triangle> positiveHPTriangles;
        std::vector<Triangle> negativeHPTriangles;

        // Traverse by triangle.
        for (const Triangle& triangle : mesh.GetTriangles()) {
            if (Intersects(triangle, plane)) {
                // Triangle straddles intersection plane, add triangle to both half-planes.
                positiveHPTriangles.push_back(triangle);
                negativeHPTriangles.push_back(triangle);
            }
            else {
                // Point selected at random since the entire triangle is on one side of the plane.
                if (SignedDistancePointPlane(triangle.GetVertices()[0], plane) < 0.0f) {
                    // Negative half-plane.
                    negativeHPTriangles.push_back(triangle);
                }
                else {
                    // Positive half-plane.
                    positiveHPTriangles.push_back(triangle);
                }
            }
        }

        SplitMesh data;
        data.positiveHPMesh.SetTriangles(positiveHPTriangles);
        data.negativeHPMesh.SetTriangles(negativeHPTriangles);

        return std::move(data);
    }

    bool OctreeNode::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {
        float broadIntersectionTime;

        // Sphere does not intersect this node.
        if (!Intersects(ray, _bounds, broadIntersectionTime)) {
            return false;
        }

        // Intersection time needs to be within range.
        if (broadIntersectionTime < tMin || broadIntersectionTime > tMax) {
            return false;
        }

        if (_mesh.GetTriangles().empty()) {
            return false;
        }

        bool isLeaf = true;
        // If the node has ANY children, it is not a leaf node.
        for (OctreeNode* child : _children) {
            if (child) {
                isLeaf = false;
                break;
            }
        }

        // Narrow phase.
        if (isLeaf) {
            bool hasIntersected = false;

            // Loop through all triangles to determine ray-triangle intersection.
            for (const Triangle& triangle : _mesh.GetTriangles()) {
                float narrowIntersectionTime;

                // Check for intersection against all triangles.
                if (Intersects(ray, triangle, narrowIntersectionTime)) {

                    // Bounds check.
                    if (narrowIntersectionTime < tMin || narrowIntersectionTime > tMax) {
                        continue;
                    }

                    if (narrowIntersectionTime < hitRecord.dt) {
                        // Found closer intersection.
                        hitRecord.dt = narrowIntersectionTime;

                        glm::vec3 intersectionPoint = ray.Step(narrowIntersectionTime);
                        hitRecord.point = intersectionPoint;

                        glm::vec3 intersectionNormal = triangle.GetNormal(intersectionPoint);
                        hitRecord.outwardFacing = glm::dot(ray.GetDirection(), intersectionNormal) < 0.0f;

                        hitRecord.normal = hitRecord.outwardFacing ? intersectionNormal : -intersectionNormal;
                        hitRecord.material = triangle.GetMaterial();
                        hasIntersected = true;
                    }
                }
            }

            return hasIntersected;
        }

        // Recurse through child nodes.
        bool hitChild = false;

        for (OctreeNode* child : _children) {
            if (child->Hit(ray, tMin, tMax, hitRecord)) {
                hitChild = true;
            }
        }

        return hitChild;
    }

}