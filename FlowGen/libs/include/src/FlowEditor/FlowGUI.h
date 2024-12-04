#pragma once
#include <vector>

class VirtualObject;
class ResourceHandler;
struct GLFWwindow;

class ResourceEditor;
class ShaderEditor;

namespace Flow
{
    enum class ECurrentEditor
    {
        EObjectHierarchy,
        EShaderEditor,
        EResourceViewer,
        COUNT
    };

    class ObjectEntry;

    class FlowGUI
    {
    public:
        FlowGUI(GLFWwindow* aWindow, ResourceHandler* aResourceHandler);
        ~FlowGUI();
        void Render(std::vector<VirtualObject*> someObjects);

    private:
        void UpdateHierarchy(std::vector<VirtualObject*> someObjects);

        void RepopulateEntries(std::vector<VirtualObject*> someObjects);
        std::vector<ObjectEntry*> myObjectEntries;
        ResourceHandler* myResources;

        ECurrentEditor myCurrentEditor;

        ResourceEditor* myResourceEditor;
        ShaderEditor* myShaderEditor;
    };
};
