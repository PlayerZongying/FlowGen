#pragma once

#include <mutex>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Mesh;

namespace Flow
{
    inline std::mutex objLoadingMutex;
    struct ObjData
    {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;
    };


    bool LoadOBJ(const std::string& filePath, ObjData& outData);
    void AddOBJ(const std::string& filePath, const std::string& name, std::unordered_map<std::string, ObjData*>& ObjMap);
    Mesh* LoadObjMesh(const std::string& filename);

    void SerializeObjData(const std::string& filePath, ObjData& objData);

    ObjData DeserializeObjData(const std::string& filePath);

    
}
