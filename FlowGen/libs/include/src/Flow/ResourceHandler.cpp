﻿#include "ResourceHandler.h"
#include "ResourceHandler.h"
#include "src/FlowGL/Shader.h"
#include "src/FlowGL/Texture.h"
#include "src/FlowGL/Mesh.h"
#include "src/FlowGL/ObjLoader.h"
#include "ResourceHandler.h"

#include <iostream>

ResourceHandler::ResourceHandler()
{
    
}

ResourceHandler::~ResourceHandler()
{

}

void ResourceHandler::CreateShader(const char* aVertexPath, const char* aFragmentPath, std::string aName)
{
    Shader* newShader = new Shader(aVertexPath, aFragmentPath);

    if (newShader->myShaderProgram != 0)
    {
        myShaders.emplace(aName, newShader);
    }
}

void ResourceHandler::CreateTexture(const char* aTexturePath, std::string aName)
{
    Texture* newTexture = new Texture(aTexturePath);

    myTextures.emplace(aName, newTexture);
}

void ResourceHandler::CreateMesh(const char* aModelPath, std::string aName)
{
    // std::lock_guard<std::mutex> lock(meshMutex);
    Mesh* newMesh = Flow::LoadObjMesh(aModelPath);
    myMeshes.emplace(aName, newMesh);
    std::cout << aName<< " is added into mesh list"<< std::endl;
}

void ResourceHandler::CreateMesh(const Flow::ObjData& objData, std::string aName)
{
    Mesh* newMesh = new Mesh(objData);
    myMeshes.emplace(aName, newMesh);
    std::cout << aName<< " is added into mesh list"<< std::endl;
}

void ResourceHandler::CreateMeshesfromObjMap()
{
    for (const auto& pair : myObjsData) {
        Flow::ObjData objData = *pair.second;
        std::string name = pair.first;
        CreateMesh(objData, name);
    }
}

void ResourceHandler::AddMesh(Mesh* mesh, std::string aName)
{
    // std::lock_guard<std::mutex> lock(meshMutex);
    myMeshes.emplace(aName, mesh);
}

void ResourceHandler::AddObj(const char* aObjFilePath, std::string aName)
{
    Flow::ObjData* someData = new Flow::ObjData;
    if (LoadOBJ(aObjFilePath, *someData))
    {
        std::lock_guard<std::mutex> lock(objMutex);
        myObjsData[aName] = someData;
    }
}

Shader* ResourceHandler::GetShader(std::string aName)
{
    return myShaders[aName];
}

Texture* ResourceHandler::GetTexture(std::string aName)
{
    return myTextures[aName];
}

Mesh* ResourceHandler::GetMesh(std::string aName)
{
    return myMeshes[aName];
}

std::vector<std::string> ResourceHandler::GetAllMeshes()
{
    std::vector<std::string> ReturnVector;
    for (auto& m : myMeshes)
    {
        ReturnVector.push_back(m.first);
    }
    return ReturnVector;
}

std::vector<std::string> ResourceHandler::GetAllTextures()
{
    std::vector<std::string> ReturnVector;
    for (auto& t : myTextures)
    {
        ReturnVector.push_back(t.first);
    }
    return ReturnVector;
}

std::vector<std::string> ResourceHandler::GetAllShaders()
{
    std::vector<std::string> ReturnVector;
    for (auto& s : myShaders)
    {
        ReturnVector.push_back(s.first);
    }
    return ReturnVector;
}

std::vector<std::string> ResourceHandler::GetAllResources()
{
    std::vector<std::string> ReturnVector;

    for (auto& m : myMeshes)
    {
        ReturnVector.push_back(m.first);
    }

    for (auto& s : myShaders)
    {
        ReturnVector.push_back(s.first);
    }

    for (auto& t : myTextures)
    {
        ReturnVector.push_back(t.first);
    }

    return ReturnVector;
}



// msg queue
void ResourceHandler::QueueMessage(Message* msg)
{
    std::lock_guard<std::mutex> lock(queueMutex);
    messages.push(msg);
    queueCV.notify_one();
}

void ResourceHandler::ProcessMessages()
{
    while (!messages.empty())
    {
        std::unique_lock<std::mutex> lock(queueMutex);

        queueCV.wait(lock, [this] { return !messages.empty(); });

        Message* msg = messages.front();
        messages.pop();

        ProcessMessage(msg);

    }
}

void ResourceHandler::ProcessMessage(Message* msg)
{
    switch (msg->type)
    {
    case MessageType::OBJMeshLoading:
        // Flow::ObjData outData;
        // Flow::LoadOBJ(msg->msg, outData);

        // more message reply
        // Mesh* newMesh = Flow::LoadObjMesh(msg->msg);
        // std::string meshPath = msg->msg;
        // myMeshes[meshPath] = newMesh;

        std::cout<<"Resource Handler: "<< msg->msg<<std::endl;
        
        break;

    }

}