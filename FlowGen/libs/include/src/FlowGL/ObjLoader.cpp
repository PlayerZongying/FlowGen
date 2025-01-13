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
<<<<<<< Updated upstream
    while (std::getline(file, line)) 
=======
    clock_t start, end;
    start = clock();

    bool has_vt = false;
    bool has_vn = false;

    std::unordered_map<Vertex, unsigned int, VertexHash> uniqueVertices;
    std::vector<glm::vec3> tempPosisitions;
    std::vector<glm::vec2> tempTexCoords;
    std::vector<glm::vec3> tempNormals;
    
    while (std::getline(file, line))
>>>>>>> Stashed changes
    {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") 
        {
            glm::vec3 position;
            ss >> position.x >> position.y >> position.z;
            //outData.positions.push_back(position);
            tempPosisitions.push_back(position);
        }
        else if (prefix == "vn") 
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            //outData.normals.push_back(normal);
            tempNormals.push_back(normal);
        }
        else if (prefix == "vt") 
        {
            glm::vec2 texCoord;
            ss >> texCoord.x >> texCoord.y;
            //outData.texCoords.push_back(texCoord);
            tempTexCoords.push_back(texCoord);
        }
        else if (prefix == "f") 
        {

            unsigned int vIndex[3], tIndex[3], nIndex[3];
<<<<<<< Updated upstream
            char slash; 
            for (int i = 0; i < 3; ++i) 
=======
            Vertex verticesInOneLine[3];
            char slash;

            // f v
            if(!has_vt && !has_vn)
>>>>>>> Stashed changes
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

            
<<<<<<< Updated upstream
=======
            // f v//n
            else if(!has_vt && has_vn)
            {
                for (int i = 0; i < 3; ++i)
                {
                    ss >> vIndex[i] >> slash >> slash >> nIndex[i];
                    outData.indices.push_back(vIndex[i] - 1);
                }

                // in case the face has 4 vertices
                unsigned int v4, n4;
                ss >> v4 >> slash >> slash >> n4;
                if (!ss.fail())
                {
                    // std::cout<<"a quad here"<<std::endl;

                    outData.indices.push_back(vIndex[0] - 1);
                    outData.indices.push_back(vIndex[2] - 1);
                    outData.indices.push_back(v4 - 1);
                }
            }

            //f v/t/n
            else
            {
                for (int i = 0; i < 3; ++i)
                {
                    
                    ss >> vIndex[i] >> slash >> tIndex[i] >> slash >> nIndex[i];
                    Vertex newVert;
                    newVert.position = tempPosisitions[vIndex[i] - 1];
                    newVert.texCoord = tempTexCoords[tIndex[i] - 1];
                    newVert.normal = tempNormals[nIndex[i] - 1];
                    
                    verticesInOneLine[i] = newVert;
            
                    if(uniqueVertices.count(newVert) == 0)
                    {
                        uniqueVertices[newVert] = static_cast<unsigned int>(uniqueVertices.size());
                    }
                    
                     outData.positions.push_back(newVert.position);
                     outData.texCoords.push_back(newVert.texCoord);
                     outData.normals.push_back(newVert.normal);
                     outData.indices.push_back(uniqueVertices[newVert]);
                }
            
                // in case the face has 4 vertices
                
                // unsigned int v4, t4, n4;
                // ss >> v4 >> slash >> t4 >> slash >> n4;
                // if (!ss.fail())
                // {
                //     // std::cout<<"a quad here"<<std::endl;
                //     Vertex newVert;
                //     newVert.position = tempPosisitions[vIndex[v4]];
                //     newVert.texCoord = tempTexCoords[tIndex[t4]];
                //     newVert.normal = tempNormals[nIndex[n4]];
                //
                //     if(uniqueVertices.count(newVert) == 0)
                //     {
                //         uniqueVertices[newVert] = static_cast<unsigned int>(uniqueVertices.size());
                //     }
                //
                //     outData.indices.push_back(vIndex[0] - 1);
                //     outData.indices.push_back(vIndex[2] - 1);
                //     outData.indices.push_back(v4 - 1);
                // }
            }
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
=======
void Flow::SerializeObjData(const std::string& filePath, ObjData& objData)
{
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return;
    }

    size_t vertexCount = objData.positions.size();
    outFile.write(reinterpret_cast<const char*>(&vertexCount), sizeof(vertexCount));
    outFile.write(reinterpret_cast<const char*>(objData.positions.data()), vertexCount * sizeof(float) * 3);

    // Write texture coordinate data
    size_t texcoordCount = objData.texCoords.size();
    outFile.write(reinterpret_cast<const char*>(&texcoordCount), sizeof(texcoordCount));
    outFile.write(reinterpret_cast<const char*>(objData.texCoords.data()), texcoordCount * sizeof(float) * 2);

    // Write normal data
    size_t normalCount = objData.normals.size();
    outFile.write(reinterpret_cast<const char*>(&normalCount), sizeof(normalCount));
    outFile.write(reinterpret_cast<const char*>(objData.normals.data()), normalCount * sizeof(float) * 3);

    // Write index data
    size_t indexCount = objData.indices.size();
    outFile.write(reinterpret_cast<const char*>(&indexCount), sizeof(indexCount));
    outFile.write(reinterpret_cast<const char*>(objData.indices.data()), indexCount * sizeof(unsigned int));

    outFile.close();
}

Flow::ObjData Flow::DeserializeObjData(const std::string& filePath)
{
    ObjData objData;
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile.is_open())
    {
        std::cerr << "Failed to open file for reading: " << filePath << std::endl;
        return objData;
    }

    // Read vertex data
    size_t vertexCount;
    inFile.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount * 3));
    objData.positions.resize(vertexCount);
    inFile.read(reinterpret_cast<char*>(objData.positions.data()), vertexCount * sizeof(float) * 3);

    // Read texture coordinate data
    size_t texcoordCount;
    inFile.read(reinterpret_cast<char*>(&texcoordCount), sizeof(texcoordCount * 2));
    objData.texCoords.resize(texcoordCount);
    inFile.read(reinterpret_cast<char*>(objData.texCoords.data()), texcoordCount * sizeof(float) * 2);

    // Read normal data
    size_t normalCount;
    inFile.read(reinterpret_cast<char*>(&normalCount), sizeof(normalCount * 3));
    objData.normals.resize(normalCount);
    inFile.read(reinterpret_cast<char*>(objData.normals.data()), normalCount * sizeof(float) * 3);

    // Read index data
    size_t indexCount;
    inFile.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));
    objData.indices.resize(indexCount);
    inFile.read(reinterpret_cast<char*>(objData.indices.data()), indexCount * sizeof(unsigned int));

    inFile.close();
    return objData;
}
>>>>>>> Stashed changes
