#pragma once
#include "LightEntry.h"
#include "src/FlowGL/LightManager.h"

class LightEditor
{
public:
    LightEditor(LightManager* aLightManager);
    void Update();

private:
    LightManager* myLightManager;
    std::vector<Flow::LightEntry*> myLightEntires;
    
};
