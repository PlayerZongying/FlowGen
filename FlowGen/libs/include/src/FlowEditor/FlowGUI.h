#pragma once
#include <vector>
#include <src/Flow/FlowGen.h>

class VirtualObject;
class ResourceHandler;
struct GLFWwindow;

class ResourceEditor;
class ShaderEditor;
class CameraEditor;

namespace Flow
{
    enum class ECurrentEditor
    {
        EObjectHierarchy,
        EShaderEditor,
        EResourceViewer,
        ECameraEditor,
        COUNT
    };

    class ObjectEntry;

    class FlowGUI
    {
    public:
        FlowGUI(GLFWwindow* aWindow, ResourceHandler* aResourceHandler);
        FlowGUI(GLFWwindow* aWindow, Engine::FlowGen* flowGen, ResourceHandler* aResourceHandler);
        ~FlowGUI();
        void Render(std::vector<VirtualObject*> someObjects);

    private:
        void UpdateHierarchy(std::vector<VirtualObject*> someObjects);

        void RepopulateEntries(std::vector<VirtualObject*> someObjects);
        std::vector<ObjectEntry*> myObjectEntries;
        ResourceHandler* myResources;
        CameraEditor* myCamera;

        ECurrentEditor myCurrentEditor;

        ResourceEditor* myResourceEditor;
        ShaderEditor* myShaderEditor;
    };
};
