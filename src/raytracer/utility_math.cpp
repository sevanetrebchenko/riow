
#include <raytracer/utility_math.h>

namespace RT {

    void MinMaxVertex(const glm::vec3& vertex, glm::vec3& minimum, glm::vec3& maximum) {
        // Find mesh extrema.
        if (vertex.x < minimum.x) {
            minimum.x = vertex.x;
        }
        else if (vertex.x > maximum.x) {
            maximum.x = vertex.x;
        }

        if (vertex.y < minimum.y) {
            minimum.y = vertex.y;
        }
        else if (vertex.y > maximum.y) {
            maximum.y = vertex.y;
        }

        if (vertex.z < minimum.z) {
            minimum.z = vertex.z;
        }
        else if (vertex.z > maximum.z) {
            maximum.z = vertex.z;
        }
    }

    float SignedDistancePointPlane(const glm::vec3 &point, const glm::vec4 &plane) {
        return glm::dot(glm::vec3(plane), point) - plane.w;
    }

    PointClassification ClassifyPointToPlane(const glm::vec3 &point, const glm::vec4 &plane) {
        float epsilon = std::numeric_limits<float>::epsilon();

        float dist = glm::dot(glm::vec3(plane), point) - plane.w;
        if (dist > epsilon) {
            return PointClassification::POINT_IN_FRONT_OF_PLANE;
        }
        else if (dist < -epsilon) {
            return PointClassification::POINT_BEHIND_PLANE;
        }
        else {
            return PointClassification::POINT_ON_PLANE;
        }
    }
//
//    TriangleClassification ClassifyTriangleToPlane(const Triangle &triangle, const glm::vec4 &plane) {
//        int numFront = 0;
//        int numBehind = 0;
//
//        // Classify
//        for (const glm::vec3& vertex : triangle.GetVertices()) {
//            switch (ClassifyPointToPlane(vertex, plane)) {
//                case PointClassification::POINT_IN_FRONT_OF_PLANE:
//                    ++numFront;
//                    break;
//                case PointClassification::POINT_BEHIND_PLANE:
//                    ++numBehind;
//                    break;
//                default:
//                    break;
//            }
//        }
//
//        // Triangle has vertices on both sides of the plane.
//        if (numBehind != 0 && numFront != 0) {
//            return TriangleClassification::TRIANGLE_STRADDLING_PLANE;
//        }
//
//        // Only front-facing vertices.
//        if (numFront != 0) {
//            return TriangleClassification::TRIANGLE_IN_FRONT_OF_PLANE;
//        }
//
//        // Only back-facing vertices.
//        if (numBehind != 0) {
//            return TriangleClassification::TRIANGLE_BEHIND_PLANE;
//        }
//
//        // ALl vertices lie on the plane.
//        return TriangleClassification::TRIANGLE_COPLANAR_WITH_PLANE;
//    }

    glm::vec3 RandomDirection(float min, float max) {
        return glm::vec3(glm::linearRand(min, max), glm::linearRand(min, max), glm::linearRand(min, max));
    }

    glm::vec3 RandomDirectionInUnitSphere() {
        while (true) {
            glm::vec3 direction = RandomDirection(-1.0f, 1.0f);

            if (glm::dot(direction, direction) >= 1.0f) {
                continue;
            }

            return direction;
        }
    }

    glm::vec3 RandomDirectionInHemisphere(const glm::vec3& rayDirection) {
        glm::vec3 random = RandomDirectionInUnitSphere();
        return glm::dot(random, rayDirection) > 0.0f ? random : -random;
    }

    float IntegerPower(float value, int power) {
        if (power == 0) {
            return 1.0f;
        }

        float result = value;

        while (power-- != 0) {
            result *= value;
        }

        return result;
    }

}