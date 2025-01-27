#include "LightManager.h"

#include <iostream>

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    simpleDepthShader = new Shader("Assets/Shaders/ShadowMappingDepthVS.glsl", "Assets/Shaders/ShadowMappingDepthFS.glsl");
}

// in initialization
void LightManager::CreateDepthTexture()
{
    glGenFramebuffers(1, &depthMapFBO);
    glGenTextures(1, &depthMap);
    
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
}

// in render loop
void LightManager::RenderDepthToTextureFromSpotLight(Light* spotLight, std::vector<VirtualObject*> myObjects)
{
    lightProjection = glm::perspective(glm::radians(75.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
    // lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(spotLight->position, spotLight->position + spotLight->direction, glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view
    simpleDepthShader->Use();
    simpleDepthShader->SetMatrix4(lightSpaceMatrix,"lightSpaceMatrix");

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, woodTexture);

    

    
    // renderScene(simpleDepthShader);
    for (int i = 0; i < myObjects.size(); i++)
    {
        myObjects[i]->DrawShadow(simpleDepthShader);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // // reset viewport
    // glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glViewport(0, 0, 1280, 720);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
}


