#include "VirtualObject.h"
#include <glad/glad.h>
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <sstream>

VirtualObject::VirtualObject(Mesh* aMesh, Texture* aTexture, Shader* aShader)
{
    myMesh = aMesh;
    myTexture = aTexture;
    myShader = aShader;

    Position =	glm::vec3(0, 0, 0);
    Rotation =	glm::vec3(0, 0, 0);
    Scale =		glm::vec3(1, 1, 1);
}

void VirtualObject::SetMesh(Mesh& aMesh)
{
    myMesh = &aMesh;
}

void VirtualObject::SetTexture(Texture& aTexture)
{
    myTexture = &aTexture;
}

void VirtualObject::SetShader(Shader& aShader)
{
    myShader = &aShader;
}

void VirtualObject::Draw(Flow::Camera* aCamera)
{
    glm::mat4 trans = glm::mat4(1.0f);

    trans = glm::translate(trans, Position);

    trans = glm::rotate(trans, Rotation.x, glm::vec3(1, 0, 0));
    trans = glm::rotate(trans, Rotation.y, glm::vec3(0, 1, 0));
    trans = glm::rotate(trans, Rotation.z, glm::vec3(0, 0, 1));

    trans = glm::scale(trans, Scale);

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);


    myShader->SetMatrix4(trans, "transform");
    myShader->SetMatrix4(aCamera->myView, "view");
    myShader->SetMatrix4(aCamera->myProjection, "projection");
    myMesh->Draw(myShader);

    glBindTexture(GL_TEXTURE_2D, 0);
}

bool VirtualObject::WriteTo(std::ofstream * outFile)
{
    outFile->write(reinterpret_cast<const char*>(&Position), sizeof(float) * 3);
    outFile->write(reinterpret_cast<const char*>(&Scale), sizeof(float) * 3);
    outFile->write(reinterpret_cast<const char*>(&Rotation), sizeof(float) * 3);
    return true;
}

bool VirtualObject::ReadFrom(std::ifstream * inFile)
{
    inFile->read(reinterpret_cast<char*>(&Position), sizeof(float) * 3);
    inFile->read(reinterpret_cast<char*>(&Scale), sizeof(float) * 3);
    inFile->read(reinterpret_cast<char*>(&Rotation), sizeof(float) * 3);
    return false;
}

Shader* VirtualObject::GetShader()
{
    return myShader;
}

