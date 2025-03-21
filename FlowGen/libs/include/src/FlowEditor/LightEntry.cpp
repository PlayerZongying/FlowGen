#include "imgui/imgui.h"
#include "LightEntry.h"
#include <glm/gtc/constants.hpp>

#include <iostream>

Flow::LightEntry::LightEntry()
{
    myLight = nullptr;
    Opened = false;
}

Flow::LightEntry::LightEntry(Light* aLight)
{
    myLight = aLight;
    Opened = false;
}

Light* Flow::LightEntry::GetLight()
{
    return myLight;
}

void Flow::LightEntry::Update()
{
    if (myLight == nullptr)
    {
        std::cout << "[Flow] Light entry has null light" << std::endl;
        return;
    }
    

    float* pos[] =
    {
        &myLight->position.x,
        &myLight->position.y,
        &myLight->position.z,
    };

    float* dir[] =
    {
        &myLight->direction.x,
        &myLight->direction.y,
        &myLight->direction.z,
    };


    float* intensity = &myLight->intensity;
    float* length = &myLight->length;
    float* angle = &myLight->angle;
    
    float* ambient[] =
    {
        &myLight->ambient.x,
        &myLight->ambient.y,
        &myLight->ambient.z,
    };

    float* diffuse[] =
    {
        &myLight->diffuse.x,
        &myLight->diffuse.y,
        &myLight->diffuse.z,
    };

    float* specular[] =
    {
        &myLight->specular.x,
        &myLight->specular.y,
        &myLight->specular.z,
    };

    UpdateLightType();

    ImGui::InputFloat3("Position ", *pos);
    ImGui::SliderFloat3("Direction ", *dir,-1.0f, 1.0f);

    ImGui::InputFloat("Intensity ", intensity);
    ImGui::InputFloat("Length ", length);
    ImGui::SliderFloat("Angle ", angle, 0, 180);

    
    ImGui::SliderFloat3("Ambient ", *ambient,0.0f, 1.0f);
    ImGui::SliderFloat3("Diffuse ", *diffuse,0.0f, 1.0f);
    ImGui::SliderFloat3("Specular ", *specular,0.0f, 1.0f);
    
    
}

void Flow::LightEntry::UpdateLightType()
{
    // Define labels for the combo box
    const char* lightTypeNames[] = { "None", "Directional", "Point", "Spot" };
    
    // Convert enum to integer for ImGui
    int currentItem = static_cast<int>(myLight->lightType);

    if (ImGui::Combo("Light Type", &currentItem, lightTypeNames, IM_ARRAYSIZE(lightTypeNames))) {
        myLight->lightType = static_cast<LightType>(currentItem); // Update enum value
    }
}
