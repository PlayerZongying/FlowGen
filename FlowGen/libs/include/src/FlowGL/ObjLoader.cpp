#include "ObjLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>  
#include <algorithm>
#include "Mesh.h"

bool Flow::LoadOBJ(const std::string& filename, ObjData& outData)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") 
        {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            outData.vertices.push_back(vertex);
        }
        else if (prefix == "vn") 
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            outData.normals.push_back(normal);
        }
        else if (prefix == "vt") 
        {
            glm::vec2 texCoord;
            ss >> texCoord.x >> texCoord.y;
            outData.texCoords.push_back(texCoord);
        }
        else if (prefix == "f") 
        {

            unsigned int vIndex[3], tIndex[3], nIndex[3];
            char slash; 
            for (int i = 0; i < 3; ++i) 
            {
                ss >> vIndex[i] >> slash >> tIndex[i] >> slash >> nIndex[i];
                outData.indices.push_back(vIndex[i] - 1);
            }

            unsigned int v4, t4, n4;
            ss >> v4 >> slash >> t4 >> slash >> n4;
            if(!ss.fail())
            {
                // std::cout<<"a quad here"<<std::endl;

                outData.indices.push_back(vIndex[0] - 1);
                outData.indices.push_back(vIndex[2] - 1);
                outData.indices.push_back(v4 - 1);
            }

            
        }
    }

    file.close();
    return true;
}

Mesh* Flow::LoadObjMesh(const std::string& filename)
{
    ObjData someData;
    if (LoadOBJ(filename, someData))
    {
        return new Mesh(someData);
    }
    else
    {
        std::cout << "Could not load mesh " << filename << std::endl;
        return nullptr;
    }
}

