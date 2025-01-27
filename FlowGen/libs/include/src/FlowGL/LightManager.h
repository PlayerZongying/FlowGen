#pragma once
#include <vector>

#include "Light.h"
#include "Shader.h"
#include "VirtualObject.h"


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


    void CreateDepthTexture();
    void RenderDepthToTextureFromSpotLight(Light* spotLight, std::vector<VirtualObject*> myObjects);
    

private:
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    unsigned int depthMap;

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.f, far_plane = 50.f;

   
    Shader* simpleDepthShader;


    

    
    LightManager(const LightManager&) = delete;            // forbid copy
    LightManager& operator=(const LightManager&) = delete; // forbid assign
};
