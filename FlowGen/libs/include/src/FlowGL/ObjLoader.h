#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>

class Mesh;

namespace Flow
{
    
    struct ObjData
    {

        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;
    };

    bool LoadOBJ(const std::string& filePath, ObjData& outData);
    Mesh* LoadObjMesh(const std::string& filename);

    void SerializeObjData(const std::string& filePath, ObjData& objData);

    ObjData DeserializeObjData(const std::string& filePath);

    
}
