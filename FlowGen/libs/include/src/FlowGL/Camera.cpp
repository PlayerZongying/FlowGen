#include "Camera.h"
#include "Camera.h"
#include <src/FlowGL/FlowGraphics.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/glm.hpp>

glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

float Flow::Camera::get_field_of_view() const
{
    return fieldOfView;
}

void Flow::Camera::set_field_of_view(float field_of_view)
{
    fieldOfView = field_of_view;
}

Flow::Camera::Camera(const float& aWidth, const float& aHeight)
{
    cameraSize.x = aWidth;
    cameraSize.y = aHeight;

    myProjection = glm::perspective(glm::radians(fieldOfView), cameraSize.x / cameraSize.y, 0.1f, 100.0f);
    myDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    myPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    myUp = glm::vec3(0.0f, 1.0f, 0.0f);
    myRight = glm::vec3(0, 0, 0);
    myView = glm::mat4(0);
}

void Flow::Camera::CameraUpdate()
{
    myRight = glm::normalize(glm::cross(myDirection, WorldUp));
    myUp = glm::cross(myRight, myDirection);
    myView = glm::lookAt(myPosition, myPosition + myDirection, myUp);
}

void Flow::Camera::CameraUpdate(GLFWwindow* window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    cameraSize.x = width;
    cameraSize.y = height;
    myProjection = glm::perspective(glm::radians(fieldOfView), cameraSize.x / cameraSize.y, 0.1f, 100.0f);
    CameraUpdate();
}

void Flow::Camera::SetPosition(const glm::vec3& aPosition)
{
    myPosition = aPosition;
}


void Flow::Camera::SetRotation(const glm::vec3& aRotation)
{

}

void Flow::Camera::Move(const glm::vec3& aMove)
{
    myPosition += myDirection * aMove.z;
    myPosition += myRight * aMove.x;
    myPosition += WorldUp * aMove.y;
}

glm::vec3 Flow::Camera::GetDirection()
{
    return myDirection;
}
void Flow::Camera::SetDirection(const glm::vec3& aDirection)
{
    myDirection = glm::normalize(aDirection);
}

glm::vec3 Flow::Camera::GetPosition()
{
    return myPosition;
}

void Flow::Camera::SetProjection()
{
    myProjection = glm::perspective(glm::radians(fieldOfView), cameraSize.x / cameraSize.y, 0.1f, 100.0f);
}
