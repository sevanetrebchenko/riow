
#include <raytracer/mesh.h>
#include <raytracer/intersections.h>

namespace RT {

    Vertex::Vertex(const glm::vec3 &v) : vertex(v) {
    }



    Triangle::Triangle(const Vertex &vtx1, const Vertex &vtx2, const Vertex &vtx3) : _material(nullptr),
                                                                                     _normalPosition(NormalPosition::FACE)
                                                                                     {
        // Initialize vertices.
        _vertices[0] = vtx1.vertex;
        _vertices[1] = vtx2.vertex;
        _vertices[2] = vtx3.vertex;

        // Initialize face normal.
        assert(vtx1.faceNormal == vtx2.faceNormal && vtx2.faceNormal == vtx3.faceNormal);
        _faceNormal = vtx1.faceNormal;

        // Initialize vertex normals.
        _vertexNormals[0] = vtx1.vertexNormal;
        _vertexNormals[1] = vtx2.vertexNormal;
        _vertexNormals[2] = vtx3.vertexNormal;
    }

    Triangle::~Triangle() {
    }

    void Triangle::ApplyTransform(const glm::mat4 &vertexTransform) {
        // Transform vertices to world-space.
        for (glm::vec3& vertex : _vertices) {
            vertex = vertexTransform * glm::vec4(vertex, 1.0f);
        }

        // Transform normals to world space.
        glm::mat4 normalTransform = glm::inverse(glm::transpose(vertexTransform));

        // Face normal.
        _faceNormal = glm::normalize(normalTransform * glm::vec4(_faceNormal, 0.0f));

        // Vertex normals.
        for (glm::vec3& vertexNormal : _vertexNormals) {
            vertexNormal = glm::normalize(normalTransform * glm::vec4(vertexNormal, 0.0f));
        }
    }

    void Triangle::SetNormalPosition(NormalPosition normalPosition) {
        switch (normalPosition) {
            case NormalPosition::VERTEX:
            case NormalPosition::FACE:
                _normalPosition = normalPosition;
                break;
            default:
                throw std::runtime_error("Invalid normal position passed to Triangle::SetNormalPosition.");
        }
    }

    void Triangle::SetMaterial(IMaterial *material) {
        _material = material;
    }

    glm::vec3 Triangle::GetNormal(const glm::vec3 &intersectionPoint) const {
        if (_normalPosition == NormalPosition::FACE) {
            return _faceNormal;
        }
        else {
//            // Find the distance between each point and the intersection point I
//            float d0 = glm::distance(_vertices[0], intersectionPoint);
//            float d1 = distance(_vertices[1], intersectionPoint);
//            float d2 = distance(_vertices[2], intersectionPoint);
//
//            // Our three points.. re-oriented so that 'a' is the farthest
//            int a, b, c;
//
//            if (d0 > d1 && d0 > d2) {
//                a = 0;
//                b = 1;
//                c = 2;
//            }
//            else if (d1 > d0 && d1 > d2) {
//                a = 1;
//                b = 0;
//                c = 2;
//            }
//            else { // if (d2 > d0 && d2 > d1) {
//                a = 2;
//                b = 0;
//                c = 1;
//            }
//
//            // For convenience
//            const glm::vec3& pointA = _vertices[a];
//            const glm::vec3& pointB = _vertices[b];
//            const glm::vec3& pointC = _vertices[c];
//
//            const glm::vec3& normalA = _vertexNormals[a];
//            const glm::vec3& normalB = _vertexNormals[b];
//            const glm::vec3& normalC = _vertexNormals[c];
//
//            // Generate an edge plane from pointB -> pointC
//            // Note that a Plane is instantiated with (origin, vector)
//
//            glm::vec3 normal = glm::vec3(glm::cross(pointC - pointB, _faceNormal));
//            glm::vec4 edgePlane (normal, glm::dot(normal, pointC));
//
//            // Generate a ray that originates at pointA and points toward I
//            //
//            // A Ray is also instantiated like a plane (origin, direction)
//
//            Ray ray(pointA, intersectionPoint - pointA);
//
//            // Find the intersection of the ray and the edge plane
//
//            glm::vec3 pointQ;
//            float t;
//            if (!Intersects(ray, edgePlane, t)) {
//                std::cerr << "No intersection between ray and edge plane." << std::endl;
//                return glm::vec3(0.0f);
//            }
//            pointQ = ray.Step(t);
//
//            // Get the interpolated vector for pointQ
//
//            float distanceBQ = glm::distance(pointB, pointQ);
//            float distanceBC = glm::distance(pointB, pointC);
//            glm::vec3 normalQ = normalB + (normalC - normalB) * (distanceBQ / distanceBC);
//
//            // Finally, interpolate from q to pointA to find the normal for I
//
//            float distanceQI = glm::distance(pointQ, intersectionPoint);
//            float distanceQA = glm::distance(pointQ, pointA);
//            glm::vec3 normalI = normalQ + (normalA - normalQ) * (distanceQI / distanceQA);
//
//            return normalI;

            const glm::vec3& a = _vertices[0];
            const glm::vec3& b = _vertices[1];
            const glm::vec3& c = _vertices[2];
            const glm::vec3& p = intersectionPoint;

// Unnormalized triangle normal
            glm::vec3 m = glm::cross(b - a, c - a);
// Nominators and one-over-denominator for u and v ratios
            float nu, nv, ood;
// Absolute components for determining projection plane
            float x = glm::abs(m.x), y = glm::abs(m.y), z = glm::abs(m.z);
// Compute areas in plane of largest projection
            if (x >= y && x >= z) {
// x is largest, project to the yz plane
                nu = Area2D(p.y, p.z, b.y, b.z, c.y, c.z); // Area of PBC in yz plane
                nv = Area2D(p.y, p.z, c.y, c.z, a.y, a.z); // Area of PCA in yz plane
                ood = 1.0f / m.x; // 1/(2*area of ABC in yz plane)
            } else if (y >= x && y >= z) {
// y is largest, project to the xz plane
                nu = Area2D(p.x, p.z, b.x, b.z, c.x, c.z);
                nv = Area2D(p.x, p.z, c.x, c.z, a.x, a.z);
                ood = 1.0f / -m.y;
            } else {
// z is largest, project to the xy plane
                nu = Area2D(p.x, p.y, b.x, b.y, c.x, c.y);
                nv = Area2D(p.x, p.y, c.x, c.y, a.x, a.y);
                ood = 1.0f / m.z;
            }
            float u = nu * ood;
            float v = nv * ood;
            float w = 1.0f - u - v;

            return glm::normalize(u * _vertexNormals[0] + v * _vertexNormals[1] + w * _vertexNormals[2]);


//            // Barycentric coordinate interpolation.
//            const glm::vec3& vtx1 = _vertices[0];
//            const glm::vec3& vtx2 = _vertices[1];
//            const glm::vec3& vtx3 = _vertices[2];
//
//            glm::vec3 v0 = vtx2 - vtx1;
//            glm::vec3 v1 = vtx3 - vtx1;
//            glm::vec3 v2 = intersectionPoint - vtx1;
//
//            float d00 = glm::dot(v0, v0);
//            float d01 = glm::dot(v0, v1);
//            float d11 = glm::dot(v1, v1);
//            float d20 = glm::dot(v2, v0);
//            float d21 = glm::dot(v2, v1);
//
//            float div = 1.0f / (d00 * d11 - d01 * d01);
//            float v = (d11 * d20 - d01 * d21) * div;
//            float w = (d00 * d21 - d01 * d20) * div;
//            float u = 1.0f - v - w;
//
//            return glm::normalize(u * _vertexNormals[0] + v * _vertexNormals[1] + w * _vertexNormals[2]);
        }
    }

    IMaterial *Triangle::GetMaterial() const {
        return _material;
    }

    const std::array<glm::vec3, 3> &Triangle::GetVertices() const {
        return _vertices;
    }

    float Triangle::Area2D(float x1, float y1, float x2, float y2, float x3, float y3) const {
        return (x1-x2)*(y2-y3) - (x2-x3)*(y1-y2);
    }


    Mesh::Mesh() = default;
    Mesh::~Mesh() = default;

    void Mesh::SetNormalPosition(NormalPosition normalPosition) {
        // Update triangles with new normal position.
        for (Triangle& triangle : _triangles) {
            triangle.SetNormalPosition(normalPosition);
        }
    }

    const std::vector<Triangle> &Mesh::GetTriangles() const {
        return _triangles;
    }

    void Mesh::SetTriangles(std::vector<Triangle> &triangles) {
        _triangles = std::move(triangles);
    }

    void Mesh::ApplyTransform(const glm::mat4 &transform) {
        for (Triangle& triangle : _triangles) {
            triangle.ApplyTransform(transform);
        }
    }


}
