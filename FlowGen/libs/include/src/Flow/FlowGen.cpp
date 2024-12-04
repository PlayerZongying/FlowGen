#include "FlowGen.h"
#include <src/FlowGL/Camera.h>
#include <GLFW/glfw3.h>
#include "Input.h"
#include "ETime.h"
#include <glm/glm.hpp>
#include "FlyingCamera.h"

Engine::FlowGen::FlowGen(GLFWwindow* aWindow, Flow::Camera* aCamera)
{
    myInput = new Input(aWindow);
    myTime = new ETime();
    myWindow = aWindow;

    myFlyingCamera = new FlyingCamera(aCamera, myInput, myTime);
    myCamera = aCamera;
}

void Engine::FlowGen::Update(const float& aDeltaTime)
{
    myFlyingCamera->Update(myWindow);
    myTime->UpdateDeltaTime(aDeltaTime);
}
