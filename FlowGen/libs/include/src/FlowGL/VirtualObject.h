#pragma once
#include <glm/glm.hpp>
#include "IWritable.h"

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

    void SetMesh(Mesh& aMesh);
    void SetTexture(Texture& aTexture);
    void SetShader(Shader& aShader);

    void Draw(Flow::Camera* aCamera);

    // bool WriteTo(const std::ofstream& outFile) override;
    // bool ReadFrom(const std::ifstream& inFile) override;
    bool WriteTo(std::ofstream* outFile) override;
    bool ReadFrom(std::ifstream* inFile) override;

    glm::vec3 Position;
    glm::vec3 Scale;
    glm::vec3 Rotation;

    std::string ObjectName;

    Shader* GetShader();

private:

    Mesh* myMesh;
    Texture* myTexture;
    Shader* myShader;
};

