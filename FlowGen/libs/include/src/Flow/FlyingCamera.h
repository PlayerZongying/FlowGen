#pragma once

struct GLFWwindow;

namespace Flow
{
    class Camera;
}

namespace Engine
{
    class Input;
    class ETime;

    class FlyingCamera
    {
    public:

        FlyingCamera(Flow::Camera* aCamera, Engine::Input* anInput, Engine::ETime* aTime);

        void Update(GLFWwindow* aWindow);


    private:

        void SetCamState(GLFWwindow* aWindow);
        Engine::Input* myInput;
        Engine::ETime* myTime;
        Flow::Camera* myCamera;

        float yaw, pitch;

        bool Editing = false;

        double lastX, lastY;
    };
}
