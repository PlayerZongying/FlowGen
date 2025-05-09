﻿#pragma once
#include <glm/glm.hpp>
#include "IWritable.h"
#include "Texture.h"
#include "src/FlowPhysics/Collider.h"

class Mesh;
class Texture;
class Shader;

namespace Flow 
{
    class Camera;
}

class VirtualObject : public IWritable
{
public:

    VirtualObject(Mesh* aMesh, Texture* aTexture, Shader* aShader);
    VirtualObject(Mesh* aMesh, Texture* aTexture, Texture* aSpecularMap, Shader* aShader);

    void SetMesh(Mesh& aMesh);
    void SetTexture(Texture& aTexture);
    void SetSpecularMap(Texture& aSpecularMap);
    void SetShader(Shader& aShader);
    void SetCollider();

    void Draw(Flow::Camera* aCamera);
    void DrawShadow(Shader* simpleDepthShader);

    // bool WriteTo(const std::ofstream& outFile) override;
    // bool ReadFrom(const std::ifstream& inFile) override;
    bool WriteTo(std::ofstream* outFile) override;
    bool ReadFrom(std::ifstream* inFile) override;

    glm::vec3 Position;
    glm::vec3 Scale;
    glm::vec3 Rotation;

    std::string ObjectName;

    Shader* GetShader();
    Mesh* GetMesh();
    Texture* GetTexture();

    Collider* collider;

private:

    Mesh* myMesh;
    Texture* myTexture;
    Texture* mySpecularMap;
    Shader* myShader;
};

