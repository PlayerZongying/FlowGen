#include "CameraEditor.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "src/Flow/FlyingCamera.h"
#include <iostream>
#include <glm/gtc/constants.hpp>
#include "src/FlowGL/Shader.h"
#include <stdio.h>
#include <string.h>

CameraEditor::CameraEditor(Flow::Camera* _camera)
{
    camera = _camera;
}

CameraEditor::~CameraEditor()
{
}

void CameraEditor::Update()
{
    glm::vec3 cameraPos = camera->GetPosition();
    float* pos[] =
    {
        &cameraPos.x,
        &cameraPos.y,
        &cameraPos.z,
    };

    ImGui::InputFloat3("Position ", *pos);

    camera->SetPosition(cameraPos);

    glm::vec3 cameraDir = camera->GetDirection();
    float yaw = atan2(cameraDir.z, cameraDir.x) * 180 / glm::pi<float>();
    float pitch = atan2(cameraDir.y, sqrt(cameraDir.x * cameraDir.x + cameraDir.z * cameraDir.z)) * 180 / glm::pi<float>();

    float* pitchYaw[] =
    {
        &pitch,
        &yaw,
    };

    ImGui::SliderFloat("Pitch ", &pitch, -90, 90);
    ImGui::SliderFloat("Yaw ", &yaw, -180, 180);

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 newDirection;
    newDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newDirection.y = sin(glm::radians(pitch));
    newDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera->SetDirection(newDirection);

    float FOV = camera->get_field_of_view();
    ImGui::SliderFloat("Field Of View", &FOV, 0, 180);
    camera->set_field_of_view(FOV);
    camera->SetProjection();

    // ImGui::InputFloat3("Scale ", *scale);
    // ImGui::SliderFloat3("Rotation ", *rot, -glm::pi<float>(), glm::pi<float>());
}
