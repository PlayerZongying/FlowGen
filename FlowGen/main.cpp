#include "src/FlowEditor/FlowGUI.h"
#include "src/Flow/FlowGen.h"
#include "src/FlowGL/FlowGraphics.h"
#include "src/Flow/ResourceHandler.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include "src/FlowGL/VirtualObject.h"
#include <vector>

int main()
{
    ResourceHandler* resources = new ResourceHandler();
    Flow::FlowInitializeData RenderData = Flow::Initialize(1280, 720);
    Engine::FlowGen* engine = new Engine::FlowGen(RenderData.aWindow, RenderData.aCamera);
    Flow::FlowGUI* Gui = new Flow::FlowGUI(RenderData.aWindow, resources);


    glfwSetInputMode(RenderData.aWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    float lastTime = 0;
    float currentTime = 0;
    float delta = 0;

    std::vector<VirtualObject*> objects;

    while (!Flow::ShouldClose())
    {
        objects = Flow::GetObjects();
        currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        Flow::BeginRender(engine->myCamera);
        Gui->Render(objects);
        Flow::End();

        engine->Update(delta);
    }

    return 0;
}






