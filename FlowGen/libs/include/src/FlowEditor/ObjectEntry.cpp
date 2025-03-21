#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "ObjectEntry.h"
#include "src/FlowGL/VirtualObject.h"
#include <iostream>
#include <glm/gtc/constants.hpp>
#include "src/FlowGL/Shader.h"
#include "src/FlowGL/Mesh.h"
#include "src/Flow/ResourceHandler.h"
#include <stdio.h>
#include <string.h>

Flow::ObjectEntry::ObjectEntry()
{
    myObject = nullptr;
    Opened = false;
}

Flow::ObjectEntry::ObjectEntry(VirtualObject* anObject)
{
    myObject = anObject;
    Opened = false;
}

Flow::ObjectEntry::~ObjectEntry()
{

}


void Flow::ObjectEntry::Update()
{
    if (myObject == nullptr)
    {
        std::cout << "[Flow] Object entry has null object" << std::endl;
        return;
    }

    float* pos[] =
    {
        &myObject->Position.x,
        &myObject->Position.y,
        &myObject->Position.z,
    };

    float* rot[] =
    {
        &myObject->Rotation.x,
        &myObject->Rotation.y,
        &myObject->Rotation.z,
    };


    float* scale[] =
    {
        &myObject->Scale.x,
        &myObject->Scale.y,
        &myObject->Scale.z,
    };

    std::string* name = &myObject->ObjectName;

    char nameBuffer[256]; 
    strncpy_s(nameBuffer, name->c_str(), sizeof(nameBuffer));

    // 使用 ImGui::InputText 创建输入框
    if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
        // 如果用户修改了输入框的内容，更新成员变量 name
        *(name) = std::string(nameBuffer);
    }

    ImGui::InputFloat3("Position ", *pos);
    ImGui::InputFloat3("Scale ", *scale);
    ImGui::SliderFloat3("Rotation ", *rot, -glm::pi<float>(), glm::pi<float>());


    UpdateMesh();
    UpdateShader();
    UpdateTexture();
    UpdateSpecularMap();
    

    // -- Move to dedicated shader tool

    // -- Move to dedicated shader tool

}

void Flow::ObjectEntry::UpdateMesh()
{
    const std::vector<std::string> meshes = ResourceHandler::Instance().GetAllMeshes();
    int meshesCount = meshes.size();
    std::vector<const char*> meshNames;
    const char* selectedMesh;
    for(int i = 0; i < meshesCount; i++)
    {
        meshNames.push_back(meshes[i].c_str());
        // if(ResourceHandler::Instance().GetMesh(meshes[selectedMeshIndex]) == myObject->GetMesh()){
        //     selectedMeshIndex = i;
        // }

    }

    if (ImGui::Combo("Mesh", &selectedMeshIndex, meshNames.data(), meshesCount)) {
        //const char* selectedMesh = meshNames[selectedMeshIndex];
        selectedMesh = meshNames[selectedMeshIndex];
        ImGui::Text("Selected Mesh: %s", selectedMesh);
        myObject->SetMesh(*ResourceHandler::Instance().GetMesh(meshes[selectedMeshIndex]));
    }
}

void Flow::ObjectEntry::UpdateShader()
{
    const std::vector<std::string> shaders = ResourceHandler::Instance().GetAllShaders();
    int shadersCount = shaders.size();
    std::vector<const char*> shaderNames;
    for(int i = 0; i < shadersCount; i++)
    {
        shaderNames.push_back(shaders[i].c_str());
        // if(ResourceHandler::Instance().GetShader(shaders[selectedshaderIndex]) == myObject->GetShader()){
        //     selectedshaderIndex = i;
        // }
    }
    
    if (ImGui::Combo("Shader", &selectedShaderIndex, shaderNames.data(), shadersCount)) {
        const char* selectedShader = shaderNames[selectedShaderIndex];
        ImGui::Text("Selected Shader: %s", selectedShader);
        myObject->SetShader(*ResourceHandler::Instance().GetShader(shaders[selectedShaderIndex]));
    }
}

void Flow::ObjectEntry::UpdateTexture()
{
    const std::vector<std::string> textures = ResourceHandler::Instance().GetAllTextures();
    int texturesCount = textures.size();
    std::vector<const char*> textureNames;
    for(int i = 0; i < texturesCount; i++)
    {
        textureNames.push_back(textures[i].c_str());
        // if(ResourceHandler::Instance().GetShader(shaders[selectedshaderIndex]) == myObject->GetShader()){
        //     selectedshaderIndex = i;
        // }
    }
    
    if (ImGui::Combo("Texture", &selectedTextureIndex, textureNames.data(), texturesCount)) {
        const char* selectedTexture = textureNames[selectedTextureIndex];
        ImGui::Text("Selected Texure: %s", selectedTexture);
        myObject->SetTexture(*ResourceHandler::Instance().GetTexture(textures[selectedTextureIndex]));
        std::cout<<textures[selectedTextureIndex]<<std::endl;
    }
}

void Flow::ObjectEntry::UpdateSpecularMap()
{
    const std::vector<std::string> textures = ResourceHandler::Instance().GetAllTextures();
    int texturesCount = textures.size();
    std::vector<const char*> textureNames;
    for(int i = 0; i < texturesCount; i++)
    {
        textureNames.push_back(textures[i].c_str());
        // if(ResourceHandler::Instance().GetShader(shaders[selectedshaderIndex]) == myObject->GetShader()){
        //     selectedshaderIndex = i;
        // }
    }
    
    if (ImGui::Combo("Specular Map", &selectedSpecularMapIndex, textureNames.data(), texturesCount)) {
        const char* selectedTexture = textureNames[selectedSpecularMapIndex];
        ImGui::Text("Selected Specular Map: %s", selectedTexture);
        myObject->SetSpecularMap(*ResourceHandler::Instance().GetTexture(textures[selectedSpecularMapIndex]));
        std::cout<<textures[selectedSpecularMapIndex]<<std::endl;
    }
}

VirtualObject* Flow::ObjectEntry::GetVirtualObject()
{
    return myObject;
}



