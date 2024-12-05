#pragma once


struct GLFWwindow;

namespace Engine
{
    class Input
    {
    public:
        Input(GLFWwindow* aWindow);
        bool IsKeyPressed(const int& aKey);
        bool IsKeyDown(const int& aKey);
        float GetCursorX();
        float GetCursorY();
        bool GetIsRightMousePressed();
    private:

        static void KeyCallBack(GLFWwindow* aWindow, int aKey, int aScanCode, int anAction, int aMod);
        static void MouseCallBack(GLFWwindow* aWindow, double xPos, double yPos);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

        GLFWwindow* myWindow;

    };
}