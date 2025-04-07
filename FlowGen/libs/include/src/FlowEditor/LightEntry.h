#pragma once
#include "src/FlowGL/Light.h"

namespace Flow
{
    class LightEntry
    {
    public:
        LightEntry();
        LightEntry(Light* aLight);
        ~LightEntry();
        Light* GetLight();

        void Update();
        void UpdateLightType();

        bool Opened = false;

    private:
        Light* myLight;

        int selectedLightType;
    };
}
