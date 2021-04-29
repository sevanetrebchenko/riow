
#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <pch.h>
#include <raytracer/material.h>

namespace RT {

    enum class NormalPosition {
        VERTEX,
        FACE
    };

    struct Vertex {
        explicit Vertex(const glm::vec3& v);

        glm::vec3 vertex;
        glm::vec3 faceNormal;
        glm::vec3 vertexNormal;
    };

    class Triangle {
        public:
            Triangle(const Vertex& vtx1, const Vertex& vtx2, const Vertex& vtx3);
            ~Triangle();

            // Applies vertexTransform to vertices and inverse(transpose(vertexTransform)) to normals.
            void ApplyTransform(const glm::mat4& vertexTransform);

            void SetNormalPosition(NormalPosition normalPosition);
            void SetMaterial(IMaterial* material);

            [[nodiscard]] glm::vec3 GetNormal(const glm::vec3& intersectionPoint) const;
            [[nodiscard]] IMaterial* GetMaterial() const;
            [[nodiscard]] const std::array<glm::vec3, 3>& GetVertices() const;

        private:
            float Area2D(float x1, float y1, float x2, float y2, float x3, float y3) const;

            IMaterial* _material;
            std::array<glm::vec3, 3> _vertices;

            std::array<glm::vec3, 3> _vertexNormals;
            glm::vec3 _faceNormal;

            NormalPosition _normalPosition;
    };

    class Mesh {
        public:
            Mesh();
            ~Mesh();

            // Applies transform to vertices and inverse(transpose(transform)) to normals.
            void ApplyTransform(const glm::mat4& transform);

            [[nodiscard]] const std::vector<Triangle>& GetTriangles() const;
            void SetTriangles(std::vector<Triangle>& triangles);

            void SetNormalPosition(NormalPosition normalPosition);

        private:
            std::vector<Triangle> _triangles;
    };

}

#endif //RAYTRACER_MESH_H
