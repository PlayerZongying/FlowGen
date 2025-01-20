#include "LightManager.h"

#include <iostream>
LightManager* LightManager::instance = nullptr;

void LightManager::Allocate()
{
    if (!instance)
    {
        instance = new LightManager();
    }
};

LightManager::LightManager()
{
    for (int i = 0; i < lightsAmount; i++)
    {
        lights[i] = new Light();
    }
}
