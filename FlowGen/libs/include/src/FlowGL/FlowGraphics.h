#pragma once
#include <vector>
#include <string>

struct GLFWwindow;
class VirtualObject;

class Mesh;
class Texture;
class Shader;

namespace Flow
{
    class Camera;

    struct FlowInitializeData
    {
        Camera* aCamera;
        GLFWwindow* aWindow;
    };

    FlowInitializeData Initialize(int aWidth, int aHeight);
    void BeginRender(Camera* aCamera);
    void End();
    bool ShouldClose();
    void Input(GLFWwindow* aWindow);

    void CreateVirtualObject(Mesh* aMesh, Texture* aTexture, Shader* aShader);

    void CreateVirtualObject();
    void DeleteVirtualObject(VirtualObject* objectToDelete);
    std::vector<VirtualObject*> GetObjects();

    void ClearObjects();


}
