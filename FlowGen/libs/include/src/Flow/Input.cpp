#include "Input.h"
#include <GLFW/glfw3.h>
#include <unordered_map>

std::unordered_map<int, bool> myKeyStates;
float lastX, lastY;
bool isRightMousePressed = false;

void Engine::Input::KeyCallBack(GLFWwindow* aWindow, int aKey, int aScanCode, int anAction, int aMod)
{
    if (anAction == GLFW_PRESS)
    {
        myKeyStates[aKey] = true;
    }
    else if (anAction == GLFW_RELEASE)
    {
        myKeyStates[aKey] = false;
    }
}

void Engine::Input::MouseCallBack(GLFWwindow* aWindow, double xPos, double yPos)
{
    lastX = xPos;
    lastY = yPos;
}

void Engine::Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            isRightMousePressed = true;
            // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏鼠标光标
        } else if (action == GLFW_RELEASE) {
            isRightMousePressed = false;
            // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // 恢复鼠标光标
        }
    }
}

float Engine::Input::GetCursorX()
{
    return lastX;
}

float Engine::Input::GetCursorY()
{
    return lastY;
}

bool Engine::Input::GetIsRightMousePressed()
{
    return isRightMousePressed;
}

bool Engine::Input::IsKeyPressed(const int& aKey)
{
    if (myKeyStates[aKey])
    {
        myKeyStates[aKey] = false;
        return true;
    }
    return false;
}

bool Engine::Input::IsKeyDown(const int& aKey)
{
    return glfwGetKey(myWindow, aKey) == GLFW_PRESS;
}

Engine::Input::Input(GLFWwindow* aWindow)
{
    myWindow = aWindow;

    GLFWvidmode return_struct;

    int width, height = 0;

    glfwGetWindowSize(aWindow, &width, &height);

    lastX = width / 2;
    lastY = height / 2;

    glfwSetKeyCallback(aWindow, KeyCallBack);
    glfwSetCursorPosCallback(aWindow, MouseCallBack);
    glfwSetMouseButtonCallback(aWindow, MouseButtonCallback);


}
