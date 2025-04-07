#include "LightEditor.h"
#include "imgui/imgui.h"

LightEditor::LightEditor(LightManager* aLightManager)
{
    myLightManager = aLightManager;
    for (Light* light : aLightManager->lights)
    {
        myLightEntires.push_back(new Flow::LightEntry(light));
    }
}
int selectedLight = -1;
// ImVec2 availableSpace = ImGui::GetContentRegionAvail();
void LightEditor::Update()
{
    ImGui::BeginChild("Scrolling", ImVec2(0, 800), true);
    for (size_t i = 0; i < myLightEntires.size(); i++)
    {
        std::string number = std::to_string(i);
        std::string Title = "Object " + number;
        
        Title = "Light_" + std::to_string(i);

        if (ImGui::Button(Title.c_str()))
        {
            myLightEntires[i]->Opened = !myLightEntires[i]->Opened;
            selectedLight = i;
        }
        
        if (!myLightEntires[i]->Opened)
        {
            continue;
        }
        
        if (selectedLight == i)
        {
            myLightEntires[i]->Update();
        }
        else
        {
            myLightEntires[i]->Opened = false;
        }
    }
    ImGui::EndChild();
}
