#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "ObjectEntry.h"
#include "src/FlowGL/VirtualObject.h"
#include <iostream>
#include <glm/gtc/constants.hpp>
#include "src/FlowGL/Shader.h"
#include <stdio.h>
#include <string.h>

Flow::ObjectEntry::ObjectEntry()
{
    myObject = nullptr;
    Opened = false;
}

Flow::ObjectEntry::ObjectEntry(VirtualObject* anObject)
{
    myObject = anObject;
    Opened = false;
}

Flow::ObjectEntry::~ObjectEntry()
{

}


void Flow::ObjectEntry::Update()
{
    if (myObject == nullptr)
    {
        std::cout << "[Flow] Object entry has null object" << std::endl;
        return;
    }

    float* pos[] =
    {
        &myObject->Position.x,
        &myObject->Position.y,
        &myObject->Position.z,
    };

    float* rot[] =
    {
        &myObject->Rotation.x,
        &myObject->Rotation.y,
        &myObject->Rotation.z,
    };


    float* scale[] =
    {
        &myObject->Scale.x,
        &myObject->Scale.y,
        &myObject->Scale.z,
    };

    ImGui::InputFloat3("Position ", *pos);
    ImGui::InputFloat3("Scale ", *scale);
    ImGui::SliderFloat3("Rotation ", *rot, -glm::pi<float>(), glm::pi<float>());

    // -- Move to dedicated shader tool

    // -- Move to dedicated shader tool

}
