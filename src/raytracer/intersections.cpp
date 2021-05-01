//
//#include <raytracer/intersections.h>
//#include <raytracer/utility_math.h>
//
//namespace RT {
//
////    bool Intersects(const Triangle& triangle, const glm::vec3& point) {
////        glm::vec3 vtx1 = triangle.GetVertices()[0];
////        glm::vec3 vtx2 = triangle.GetVertices()[1];
////        glm::vec3 vtx3 = triangle.GetVertices()[2];
////
////        // Translate point and triangle so that point lies at origin.
////        vtx1 -= point;
////        vtx2 -= point;
////        vtx3 -= point;
////
////        // Compute triangle normals
////        glm::vec3 u = glm::cross(vtx2, vtx3);
////        glm::vec3 v = glm::cross(vtx3, vtx1);
////        glm::vec3 w = glm::cross(vtx1, vtx2);
////
////        // Ensure both normals are pointing in the same direction.
////        if (glm::dot(u, v) < 0.0f) {
////            return false;
////        }
////
////        // Ensure both normals are pointing in the same direction.
////        if (glm::dot(u, w) < 0.0f) {
////            return false;
////        }
////
////        return true;
////    }
////
////    bool Intersects(const Triangle& triangle, const glm::vec4& plane) {
////        auto da = glm::sign(SignedDistancePointPlane(triangle.GetVertices()[0], plane));
////        auto db = glm::sign(SignedDistancePointPlane(triangle.GetVertices()[1], plane));
////
////        // Triangle is straddling the plane.
////        if (glm::epsilonNotEqual(da, db, std::numeric_limits<float>::epsilon())) {
////            return true;
////        }
////
////        auto dc = glm::sign(SignedDistancePointPlane(triangle.GetVertices()[2], plane));
////
////        // Triangle is straddling the plane.
////        if (glm::epsilonNotEqual(dc, db, std::numeric_limits<float>::epsilon())) {
////            return true;
////        }
////
////        // Triangle is coplanar with plane.
////        if (glm::abs(da) < std::numeric_limits<float>::epsilon() && glm::abs(db) < std::numeric_limits<float>::epsilon() && glm::abs(dc) < std::numeric_limits<float>::epsilon()) {
////            return true;
////        }
////
////        // No intersection occurred.
////        return false;
////    }
//
//    bool Intersects(const Ray& ray, const AABB& aabb, float& intersectionTime) {
//        const glm::vec3& rayOrigin = ray.GetOrigin();
//        const glm::vec3& rayDirection = ray.GetDirection();
//
//        // Rays that start inside the AABB are automatically intersecting.
//        bool inside = true;
//        for (int i = 0; i < 3; ++i) {
//            if (rayOrigin[i] < aabb.minimum[i] || rayOrigin[i] > aabb.maximum[i]) {
//                inside = false;
//                break;
//            }
//        }
//        if (inside) {
//            intersectionTime = 0.001f;
//            return true;
//        }
//
//        float tMin = std::numeric_limits<float>::min();
//        float tMax = std::numeric_limits<float>::max();
//
//        for (int i = 0; i < 3; ++i) {
//            // Ray direction is parallel.
//            if (std::abs(rayDirection[i]) < std::numeric_limits<float>::epsilon()) {
//                if (rayOrigin[i] < aabb.minimum[i] || rayOrigin[i] > aabb.maximum[i]) {
//                    return false;
//                }
//            }
//            else {
//                // Break up intersection along each plane.
//                float div = 1.0f / rayDirection[i];
//
//                float tMinCurrent = (aabb.minimum[i] - rayOrigin[i]) * div;
//                float tMaxCurrent = (aabb.maximum[i] - rayOrigin[i]) * div;
//
//                // Flip intersection times if the ray is facing the opposite way.
//                if (tMinCurrent > tMaxCurrent) {
//                    std::swap(tMaxCurrent, tMinCurrent);
//                }
//
//                tMin = std::max(tMin, tMinCurrent);
//                tMax = std::min(tMax, tMaxCurrent);
//
//                if (tMin > tMax) {
//                    return false;
//                }
//            }
//        }
//
//        // AABB is behind the origin of the ray.
//        if (tMax < 0) {
//            return false;
//        }
//
//        // Compute intersection point.
//        intersectionTime = tMin;
//        return true;
//    }
//
//    bool Intersects(const Ray& ray, const glm::vec4& plane, float& intersectionTime) {
//        float no = glm::dot(glm::vec3(plane), ray.GetOrigin());
//        float nd = glm::dot(glm::vec3(plane), ray.GetDirection());
//
//        if (glm::epsilonNotEqual(glm::abs(nd), 0.0f, std::numeric_limits<float>::epsilon()))
//        {
//            intersectionTime = (plane.w - no) / nd;
//            return true;
//        }
//
//        return false;
//    }
//
////    bool Intersects(const Ray& ray, const Triangle& triangle, float& intersectionTime) {
////        const std::array<glm::vec3, 3>& vertices = triangle.GetVertices();
////
////        // Test if intersection point lies inside triangle.
////        glm::vec3 normal = glm::cross(vertices[1] - vertices[0], vertices[2] - vertices[0]);
////        float d = glm::dot(normal, triangle.GetVertices()[0]);
////
////        glm::vec4 plane = glm::vec4(normal, d);
////
////        if (Intersects(ray, plane, intersectionTime)) {
////            return Intersects(triangle, ray.Step(intersectionTime));
////        }
////
////        // Ray does not intersect plane, hence ray will not intersect triangle.
////        return false;
////    }
//
//    bool Intersects(const glm::vec3& begin, const glm::vec3& end, const glm::vec4& plane, float& intersectionTime) {
//        glm::vec3 vector = end - begin;
//        glm::vec3 normal(plane);
//
//        intersectionTime = (plane.w - glm::dot(normal, begin)) / glm::dot(normal, vector);
//
//        if (intersectionTime >= 0.0f && intersectionTime <= 1.0f) {
//            return true;
//        }
//
//        return false;
//    }
//
//}
