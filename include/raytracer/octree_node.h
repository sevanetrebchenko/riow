
#ifndef RAYTRACER_OCTREE_NODE_H
#define RAYTRACER_OCTREE_NODE_H

#include <raytracer/aabb.h>
#include <raytracer/mesh.h>
#include <raytracer/ray.h>
#include <raytracer/hit_record.h>

namespace RT {

    class OctreeNode {
        public:
            static unsigned maxNumTriangles;

            OctreeNode(const AABB& bounds, const Mesh& mesh);
            ~OctreeNode();

            bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const;

        private:
            struct SplitMesh {
                Mesh positiveHPMesh;
                Mesh negativeHPMesh;
            };

            constexpr static int X_AXIS = 0;
            constexpr static int Y_AXIS = 1;
            constexpr static int Z_AXIS = 2;
            [[nodiscard]] glm::vec4 CalculatePlane(int axis) const;

            void Split();
            [[nodiscard]] bool SplitReducedTriangles(unsigned parentNumTriangles, const SplitMesh& data) const;

            // Returns two submeshes, each belonging and fully contained by the half-plane of the input plane.
            // (negative half-plane, positive half-plane).
            SplitMesh SplitMeshAcrossPlane(const Mesh& meshData, const glm::vec4& plane);

            AABB _bounds;
            Mesh _mesh;
            std::array<OctreeNode*, 8> _children;
    };

}

#endif //RAYTRACER_OCTREE_NODE_H
