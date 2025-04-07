#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "ObjLoader.h"
class Shader;

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec3 normal;

    bool operator==(const Vertex& other) const
    {
        return position == other.position && texCoord == other.texCoord && normal == other.normal;
    }
};

struct VertexHash {
    std::size_t operator()(const Vertex& vertex) const {
        return std::hash<float>()(vertex.position.x) ^
               std::hash<float>()(vertex.position.y) ^
               std::hash<float>()(vertex.position.z) ^
               std::hash<float>()(vertex.texCoord.x) ^
               std::hash<float>()(vertex.texCoord.y) ^
               std::hash<float>()(vertex.normal.x) ^
               std::hash<float>()(vertex.normal.y) ^
               std::hash<float>()(vertex.normal.z);
    }
};


class Mesh
{
public:
    Mesh(const float* someVertices, size_t aVertexSize, unsigned int* someIndices, size_t aIndexSize);
    Mesh(Flow::ObjData someData);

    ~Mesh();
    void Draw(Shader* aShader);

private:
    std::vector<Vertex> myVertices;
    std::vector<unsigned int> myIndices;
    int IndicesSize = 0;


    std::string MeshFilePath;

protected:
    unsigned int VBO, VAO, EBO;
};
