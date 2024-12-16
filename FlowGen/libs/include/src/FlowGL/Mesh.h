#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "ObjLoader.h"
class Shader;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
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
