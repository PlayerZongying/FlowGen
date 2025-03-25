#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "GLFW/glfw3native.h"
#include "Message/MessageQueue.h"
#include "src/FlowGL/Mesh.h"
#include "src/FlowGL/Texture.h"

class Texture;
class Shader;
class Mesh;


class ResourceHandler : public MessageQueue
{
public:
    
    static ResourceHandler& Instance()
    {
        static ResourceHandler instance;
        return instance;
    }

    ResourceHandler();
    ~ResourceHandler();

    void QueueMessage(Message* msg) override;

    void CreateShader(const char* aVertexPath, const char* aFragmentPath, std::string aName);
    void CreateTexture(const char* aTexturePath, std::string aName);
    void CreateMesh(const char* aModelPath, std::string aName);
    void AddMesh(Mesh* mesh, std::string aName);

    Shader* GetShader(std::string aName);
    Texture* GetTexture(std::string aName);
    Mesh* GetMesh(std::string aName);

    std::vector<std::string> GetAllMeshes();
    std::vector<std::string> GetAllTextures();
    std::vector<std::string> GetAllShaders();

    std::vector<std::string> GetAllResources();

private:
    ResourceHandler(const ResourceHandler&) = delete; // 禁止拷贝
    ResourceHandler& operator=(const ResourceHandler&) = delete; // 禁止赋值

    std::unordered_map<std::string, Texture*> myTextures;
    std::unordered_map<std::string, Shader*> myShaders;
    std::unordered_map<std::string, Mesh*> myMeshes;




    std::mutex queueMutex;
    std::condition_variable queueCV;

    void ProcessMessages();
    void ProcessMessage(Message* msg);

    std::queue<Message*> messages;

    
};
