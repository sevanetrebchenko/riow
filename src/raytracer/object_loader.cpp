//
//#include <raytracer/object_loader.h>
//#include <raytracer/utility_math.h>
//
//namespace RT {
//
//    OBJLoader &OBJLoader::GetInstance() {
//        static OBJLoader instance;
//        return instance;
//    }
//
//    OBJLoader::OBJLoader() = default;
//    OBJLoader::~OBJLoader() = default;
//
//    Mesh OBJLoader::Load(const std::string &filepath) {
//        if (_meshes.find(filepath) != _meshes.end()) {
//            return _meshes[filepath]; // Copy.
//        }
//
//        // Loading new mesh.
//        std::vector<Vertex> vertices;
//
//        glm::vec3 minimum(std::numeric_limits<float>::max());
//        glm::vec3 maximum(std::numeric_limits<float>::lowest());
//
//        // Prepare tinyobj loading parameters.
//        tinyobj::attrib_t attributes; // Holds all positions, normals, and texture coordinates.
//        std::vector<tinyobj::shape_t> shapeData; // Holds all separate objects and their faces.
//        std::vector<tinyobj::material_t> materialData;
//        std::string warning;
//        std::string error;
//
//        // Triangulation enabled by default.
//        if (!tinyobj::LoadObj(&attributes, &shapeData, &materialData, &warning, &error, filepath.c_str())) {
//            throw std::runtime_error("Failed to load OBJ file: " + filepath + ". Provided information: " + warning + " (WARNING) " + error + "(ERROR)");
//        }
//
//        bool hasVertexNormals = !attributes.normals.empty();
//        bool hasTextureCoordinates = !attributes.texcoords.empty();
//        bool hasVertexColors = !attributes.colors.empty();
//
//        // Push shape data.
//        for (const tinyobj::shape_t& shape : shapeData) {
//            for (const tinyobj::index_t& index : shape.mesh.indices) {
//                int vertexBase = 3 * index.vertex_index;
//                glm::vec3 vertex (attributes.vertices[vertexBase + 0], attributes.vertices[vertexBase + 1], attributes.vertices[vertexBase + 2]);
//
//                int vertexNormalBase = 3 * index.normal_index;
//                glm::vec3 vertexNormal;
//                if (hasVertexNormals) {
//                    vertexNormal = glm::vec3(attributes.normals[vertexNormalBase + 0], attributes.normals[vertexNormalBase + 1], attributes.normals[vertexNormalBase + 2]);
//                }
//
//                int textureCoordinateBase = 2 * index.texcoord_index;
//                glm::vec2 textureCoordinate;
//                if (hasTextureCoordinates) {
//                    textureCoordinate = glm::vec2(attributes.texcoords[textureCoordinateBase + 0], attributes.texcoords[textureCoordinateBase + 1]);
//                }
//
//                int vertexColorBase = vertexBase;
//                glm::vec3 vertexColor;
//                if (hasVertexColors) {
//                    vertexColor = glm::vec3(attributes.colors[vertexColorBase + 0], attributes.colors[vertexColorBase + 1], attributes.colors[vertexColorBase + 2]);
//                }
//
//                vertices.emplace_back(vertex);
//                MinMaxVertex(vertex, minimum, maximum);
//            }
//        }
//
//        // Compute normal data.
//        std::unordered_map<glm::vec3, std::vector<glm::vec3>> globalVertexNormalData;
//
//        for (int index = 0; index < vertices.size(); index += 3) {
//            Vertex& v1 = vertices[index + 0];
//            Vertex& v2 = vertices[index + 1];
//            Vertex& v3 = vertices[index + 2];
//
//            // Calculate face normal.
//            glm::vec3 faceNormal = glm::normalize(glm::cross(v2.vertex - v1.vertex, v3.vertex - v1.vertex));
//            v1.faceNormal = faceNormal;
//            v2.faceNormal = faceNormal;
//            v3.faceNormal = faceNormal;
//
//            // Contribute face normal to vertex normal calculation.
//            for (int i = 0; i < 3; ++i) {
//                const glm::vec3& vertex = vertices[index + i].vertex;
//
//                // Determine if normal was already encountered.
//                // Don't add duplicate normals.
//                bool add = true;
//                std::vector<glm::vec3>& vector = globalVertexNormalData[vertex];
//
//                for (const glm::vec3& temp : vector) {
//                    if (temp == faceNormal) {
//                        add = false;
//                        break;
//                    }
//                }
//
//                if (add) {
//                    vector.push_back(faceNormal);
//                }
//            }
//        }
//
//        // Compute vertex normals.
//        std::unordered_map<glm::vec3, glm::vec3> globalVertexNormals;
//        for (const auto& vertexNormalData : globalVertexNormalData) {
//            const glm::vec3& key = vertexNormalData.first;
//            const std::vector<glm::vec3>& uniqueNormals = vertexNormalData.second;
//
//            // Compute vertex normal.
//            glm::vec3 vertexNormal(0.0f);
//
//            for (const glm::vec3& normal : uniqueNormals) {
//                vertexNormal += normal;
//            }
//
//            globalVertexNormals[key] = glm::normalize(vertexNormal);
//        }
//
//        // Construct triangles.
//        std::vector<Triangle> triangles;
//
//        for (int index = 0; index < vertices.size(); index += 3) {
//            Vertex& v1 = vertices[index + 0];
//            Vertex& v2 = vertices[index + 1];
//            Vertex& v3 = vertices[index + 2];
//
//            // Set vertex normals.
//            v1.vertexNormal = globalVertexNormals[v1.vertex];
//            v2.vertexNormal = globalVertexNormals[v2.vertex];
//            v3.vertexNormal = globalVertexNormals[v3.vertex];
//
//            // Construct triangle.
//            triangles.emplace_back(v1, v2, v3);
//        }
//
//        // Create mesh.
//        Mesh mesh;
//        mesh.SetTriangles(triangles);
//
//        // Normalize mesh.
//        {
//            // Center model at (0, 0, 0)
//            glm::vec3 centerPosition = glm::vec3((minimum + maximum) / 2.0f);
//            glm::mat4 transform = glm::translate(glm::mat4(1.0f), -centerPosition);
//
//            mesh.ApplyTransform(transform);
//        }
//
//        // Scale the mesh to range [-1 1] on all axes.
//        {
//            glm::vec3 boundingBoxDimensions = maximum - minimum;
//            float maxDimension = std::max(boundingBoxDimensions.x, std::max(boundingBoxDimensions.y, boundingBoxDimensions.z));
//            glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f / maxDimension));
//
//            mesh.ApplyTransform(transform);
//        }
//
//        _meshes[filepath] = mesh;
//        return mesh;
//    }
//
//
//}
//
