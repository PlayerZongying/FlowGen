﻿#include "FlyingCamera.h"
#include "FlyingCamera.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <src/FlowGl/Camera.h>
#include "ETime.h"
#include <iostream>

const float Sensitivity = 0.5f;
const float MoveSpeed = 10.0f;

Engine::FlyingCamera::FlyingCamera(Flow::Camera* aCamera, Engine::Input* anInput, Engine::ETime* aTime)
{
    myCamera = aCamera;
    myInput = anInput;
    myTime = aTime;

    lastX = 0;
    lastY = 0;

    pitch = 0;
    yaw = 0;
}

void Engine::FlyingCamera::Update(GLFWwindow* aWindow)
{
    glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

    // if (myInput->IsKeyPressed(GLFW_KEY_TAB))
    // {
    //     SetCamState(aWindow);
    // }
    //
    // if (Editing) return;

    if(!myInput->GetIsRightMousePressed())
    {
        DoOnce = false;
        return;
    }

    
    // move with WASD
    if (myInput->IsKeyDown(GLFW_KEY_W)) velocity.z = 1;
    if (myInput->IsKeyDown(GLFW_KEY_A)) velocity.x = -1;
    if (myInput->IsKeyDown(GLFW_KEY_S)) velocity.z = -1;
    if (myInput->IsKeyDown(GLFW_KEY_D)) velocity.x = 1;

    if (myInput->IsKeyDown(GLFW_KEY_SPACE)) velocity.y = 1;
    if (myInput->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) velocity.y = -1;


    // rotate with cursor
    float xpos, ypos;
    xpos = myInput->GetCursorX();
    ypos = myInput->GetCursorY();

    if(DoOnce == false)
    {
        lastX = xpos;
        lastY = ypos;
        DoOnce = true;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    // *myTime->DeltaTime()
    // 	* myTime->DeltaTime()

    xoffset *= Sensitivity;
    yoffset *= Sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    myCamera->Move(velocity * MoveSpeed * myTime->DeltaTime());
    myCamera->SetDirection(direction);
}

void Engine::FlyingCamera::SetCamState(GLFWwindow* aWindow)
{
    Editing = !Editing;

    if (Editing)
    {
        glfwSetInputMode(aWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(aWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}