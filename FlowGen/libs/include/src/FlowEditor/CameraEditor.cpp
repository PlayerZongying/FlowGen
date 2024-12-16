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
    
    
    // ImGui::InputFloat3("Scale ", *scale);
    // ImGui::SliderFloat3("Rotation ", *rot, -glm::pi<float>(), glm::pi<float>());
}
