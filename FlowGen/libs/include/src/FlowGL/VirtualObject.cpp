#include "VirtualObject.h"
#include <glad/glad.h>
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <sstream>

#include "LightManager.h"

VirtualObject::VirtualObject(Mesh* aMesh, Texture* aTexture, Shader* aShader)
{
    myMesh = aMesh;
    myTexture = aTexture;
    myShader = aShader;

    Position = glm::vec3(0, 0, 0);
    Rotation = glm::vec3(0, 0, 0);
    Scale = glm::vec3(1, 1, 1);
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

    myShader->SetVector3(aCamera->GetPosition(), "viewPos");

    // glm::vec3 lightPos(0.0f, 15.0f, 5.0f);
    // glm::vec3 lightAmbient(0.2f);
    // glm::vec3 lightDiffuse(1.0f, 1.0f, 1.0f);
    // glm::vec3 lightSpecular(1.0f, 1.0f, 1.0f);
    //
    // myShader->SetVector3(lightPos, "light.position");
    // myShader->SetVector3(lightAmbient, "light.ambient");
    // myShader->SetVector3(lightDiffuse, "light.diffuse");
    // myShader->SetVector3(lightSpecular, "light.specular");
    for (int i = 0; i < LightManager::lightsAmount; i++)
    {
        std::string lightType = "lights[" + std::to_string(i) + "].lightType";
        std::string position = "lights[" + std::to_string(i) + "].position";
        std::string direction = "lights[" + std::to_string(i) + "].direction";
        std::string intensity = "lights[" + std::to_string(i) + "].intensity";
        std::string length = "lights[" + std::to_string(i) + "].length";
        std::string angle = "lights[" + std::to_string(i) + "].angle";
        std::string ambient = "lights[" + std::to_string(i) + "].ambient";
        std::string diffuse = "lights[" + std::to_string(i) + "].diffuse";
        std::string specular = "lights[" + std::to_string(i) + "].specular";

        myShader->SetInt(LightManager::instance->lights[i]->lightType, lightType);
        myShader->SetVector3(LightManager::instance->lights[i]->position, position);
        myShader->SetVector3(LightManager::instance->lights[i]->direction, direction);
        myShader->SetFloat(LightManager::instance->lights[i]->intensity, intensity);
        myShader->SetFloat(LightManager::instance->lights[i]->length, length);
        myShader->SetFloat(LightManager::instance->lights[i]->angle, angle);
        myShader->SetVector3(LightManager::instance->lights[i]->ambient, ambient);
        myShader->SetVector3(LightManager::instance->lights[i]->diffuse, diffuse);
        myShader->SetVector3(LightManager::instance->lights[i]->specular, specular);
    }

    glm::vec3 materialAmbient(1.f);
    glm::vec3 materialDiffuse(1.f);
    glm::vec3 materialSpecular(1.f);
    float shininess = 8.0f;

    myShader->SetVector3(materialAmbient, "material.ambient");
    myShader->SetVector3(materialDiffuse, "material.diffuse");
    myShader->SetVector3(materialSpecular, "material.specular");
    myShader->SetFloat(shininess, "material.shininess");

    glm::vec4 testColor(0.5f, 0.5f, 0.5f, 1.f);
    myShader->SetVector4(testColor, "testColor");


    myMesh->Draw(myShader);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void VirtualObject::DrawShadow(Shader* simpleDepthShader)
{
    glm::mat4 trans = glm::mat4(1.0f);

    trans = glm::translate(trans, Position);

    trans = glm::rotate(trans, Rotation.x, glm::vec3(1, 0, 0));
    trans = glm::rotate(trans, Rotation.y, glm::vec3(0, 1, 0));
    trans = glm::rotate(trans, Rotation.z, glm::vec3(0, 0, 1));

    trans = glm::scale(trans, Scale);

    simpleDepthShader->SetMatrix4(trans, "transform");

    myMesh->Draw(simpleDepthShader);
    
}

bool VirtualObject::WriteTo(std::ofstream* outFile)
{
    outFile->write(reinterpret_cast<const char*>(&Position), sizeof(float) * 3);
    outFile->write(reinterpret_cast<const char*>(&Scale), sizeof(float) * 3);
    outFile->write(reinterpret_cast<const char*>(&Rotation), sizeof(float) * 3);
    return true;
}

bool VirtualObject::ReadFrom(std::ifstream* inFile)
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

Mesh* VirtualObject::GetMesh()
{
    return myMesh;
}

Texture* VirtualObject::GetTexture()
{
    return myTexture;
}
