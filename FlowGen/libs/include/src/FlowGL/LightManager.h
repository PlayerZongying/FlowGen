#pragma once
#include "Light.h"

class LightManager
{
public:
    static LightManager* instance;

    static LightManager* Instance()
    {
        return instance;
    }

    static void Allocate();

    inline static constexpr int lightsAmount = 9;

    LightManager();
    Light* lights[lightsAmount];

private:
    LightManager(const LightManager&) = delete;            // forbid copy
    LightManager& operator=(const LightManager&) = delete; // forbid assign
};
