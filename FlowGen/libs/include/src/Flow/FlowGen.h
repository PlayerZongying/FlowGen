#pragma once

struct GLFWwindow;

namespace Flow
{
    class Camera;
}

namespace Engine
{
    class ETime;
    class Input;
    class FlyingCamera;

    
    class FlowGen
    {
    public:

        FlowGen(GLFWwindow* aWindow, Flow::Camera* aCamera);

        void Update(const float& aDeltaTime);

        Flow::Camera* myCamera;
    private:

        Input* myInput;
        ETime* myTime;
        FlyingCamera* myFlyingCamera;

        GLFWwindow* myWindow;
    };
}

