﻿#include "FlowGraphics.h"
#include "VirtualObject.h"
#include "ObjLoader.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <direct.h>
#include "Shader.h"
#include <Windows.h>
#include "Triangle.h"
#include "Cube.h"
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "stb_image.h"
#include "Texture.h"
#include "Square.h"

#include <fstream>
#include <sstream>

#include "LightManager.h"
#include "src/Flow/ResourceHandler.h"
#include "src/FlowPhysics/BoxCollider.h"
#include "src/FlowPhysics/SphereCollider.h"



GLFWwindow* window;

Shader* myShader;
Shader* myBillboard;
Shader* NormalView;
Shader* BlinnPhong;
Shader* BlinnPhongMultiLights;

Square* mySquare;
Triangle* myTriangle;
Cube* myCube;

Texture* myTexture;
Texture* whiteTexture;
Texture* myConcreteTexture;
Texture* appleTexture;
Mesh* CubeMesh;
Mesh* PlaneMesh;
Mesh* FlagMesh;
Mesh* MonkeyMesh;
Mesh* TeapotMesh;
Mesh* SwordMesh;
Mesh* SphereMesh;
Mesh* AppleMesh;


float myWidth;
float myHeight;

float lastTime;
float currentTime;
float DeltaTime;

std::vector<VirtualObject*> myObjects;
VirtualObject* myBillboardObject = nullptr;


Flow::FlowInitializeData Flow::Initialize(int aWidth, int aHeight)
{
    FlowInitializeData someData;
    someData.aCamera = NULL;
    someData.aWindow = NULL;

    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw" << std::endl;
        return someData;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(aWidth, aHeight, "Flow", NULL, NULL);
    glfwMakeContextCurrent(window);

    myWidth = aWidth;
    myHeight = aHeight;

    if (window == NULL)
    {
        std::cout << "Failed to initialize window" << std::endl;
        return someData;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return someData;
    }

    ResourceHandler::Instance().CreateTexture("Assets/Images/Default.png", "myTexture");
    ResourceHandler::Instance().CreateTexture("Assets/Images/Apple.jpg","appleTexture");
    ResourceHandler::Instance().CreateTexture("Assets/Images/white.png","whiteTexture");

    myConcreteTexture = new Texture("Assets/Images/Grass.png");
    // myTexture = new Texture("Assets/Images/Default.png");
    // appleTexture = new Texture("Assets/Images/Apple.jpg");

    myTexture = ResourceHandler::Instance().GetTexture("myTexture");
    whiteTexture = ResourceHandler::Instance().GetTexture("whiteTexture");
    appleTexture = ResourceHandler::Instance().GetTexture("appleTexture");


    
    // myShader = new Shader("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShader.glsl");
    myBillboard = new Shader("Assets/Shaders/VertexBillboard.glsl", "Assets/Shaders/FragmentShader.glsl");

    // Blinn Phong Test
    BlinnPhong = new Shader("Assets/Shaders/BlinnPhongVS.glsl", "Assets/Shaders/BlinnPhongFS.glsl");
    // NormalView = new Shader("Assets/Shaders/NormalViewVS.glsl", "Assets/Shaders/NormalViewFS.glsl");

    ResourceHandler::Instance().CreateShader("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShader.glsl", "myShader");
    ResourceHandler::Instance().CreateShader("Assets/Shaders/NormalViewVS.glsl", "Assets/Shaders/NormalViewFS.glsl", "NormalView");
    ResourceHandler::Instance().CreateShader("Assets/Shaders/BlinnPhongMultiLightsVS.glsl", "Assets/Shaders/BlinnPhongMultiLightsFS.glsl", "BlinnPhongMultiLights");

    myShader = ResourceHandler::Instance().GetShader("myShader");
    NormalView = ResourceHandler::Instance().GetShader("NormalView");
    BlinnPhongMultiLights = ResourceHandler::Instance().GetShader("BlinnPhongMultiLights");
    
    std::vector<std::thread> meshLoadingThreads;

    meshLoadingThreads.emplace_back(&ResourceHandler::AddObj, &ResourceHandler::Instance(),"Assets/Models/plane.obj", "plane");
    meshLoadingThreads.emplace_back(&ResourceHandler::AddObj, &ResourceHandler::Instance(),"Assets/Models/monkey.obj", "monkey");
    meshLoadingThreads.emplace_back(&ResourceHandler::AddObj, &ResourceHandler::Instance(),"Assets/Models/teapot.obj", "teapot");
    meshLoadingThreads.emplace_back(&ResourceHandler::AddObj, &ResourceHandler::Instance(),"Assets/Models/Flag.obj", "Flag");
    meshLoadingThreads.emplace_back(&ResourceHandler::AddObj, &ResourceHandler::Instance(),"Assets/Models/sword.obj", "sword");
    meshLoadingThreads.emplace_back(&ResourceHandler::AddObj, &ResourceHandler::Instance(),"Assets/Models/sphere.obj", "sphere");
    meshLoadingThreads.emplace_back(&ResourceHandler::AddObj, &ResourceHandler::Instance(),"Assets/Models/appleTest.obj", "apple");
    
    for (auto& t : meshLoadingThreads) {
        t.join();
    }
    

    ResourceHandler::Instance().CreateMeshesfromObjMap();
    
    // ResourceHandler::Instance().CreateMesh("Assets/Models/plane.obj", "plane");
    // ResourceHandler::Instance().CreateMesh("Assets/Models/monkey.obj", "monkey");
    // ResourceHandler::Instance().CreateMesh("Assets/Models/teapot.obj", "teapot");
    // ResourceHandler::Instance().CreateMesh("Assets/Models/Flag.obj", "Flag");
    // ResourceHandler::Instance().CreateMesh("Assets/Models/sword.obj", "sword");
    // ResourceHandler::Instance().CreateMesh("Assets/Models/sphere.obj", "sphere");
    // ResourceHandler::Instance().CreateMesh("Assets/Models/appleTest.obj", "apple");
    
    ResourceHandler::Instance().AddMesh(new Cube(), "cube");



    FlagMesh = ResourceHandler::Instance().GetMesh("Flag");
    PlaneMesh = ResourceHandler::Instance().GetMesh("plane");
    MonkeyMesh = ResourceHandler::Instance().GetMesh("monkey");
    TeapotMesh = ResourceHandler::Instance().GetMesh("teapot");
    CubeMesh = ResourceHandler::Instance().GetMesh("cube");
    SwordMesh = ResourceHandler::Instance().GetMesh("sword");
    SphereMesh = ResourceHandler::Instance().GetMesh("sphere");
    AppleMesh = ResourceHandler::Instance().GetMesh("apple");
    // FlagMesh = LoadObjMesh("Assets/Models/Flag.obj");

    // MonkeyMesh = LoadObjMesh("Assets/Models/monkey.obj");

    ResourceHandler::Instance().ProcessMessages();

    myCube = new Cube();
    mySquare = new Square();

    Camera* camera = new Camera(aWidth, aHeight);

    someData.aCamera = camera;
    someData.aWindow = window;

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);


    LightManager::Allocate();
    LightManager* lightManager = LightManager::Instance();
    
    Light* light0 = lightManager->lights[0];
    light0->lightType = spot;
    light0->position = glm::vec3(-5,0.f,0);
    light0->direction = glm::vec3(1,0.f,0);
    light0->angle = 3;
    light0->ambient =  glm::vec3(0.05f);
    light0->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    light0->specular = glm::vec3(1.0f, 1.0f, 1.0f);
    
    // Light* light1 = lightManager->lights[1];
    // light1->lightType = point;
    // light1->position = glm::vec3(0,-15,0);
    // light1->ambient =  glm::vec3(0.05f);
    // light1->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    // light1->specular = glm::vec3(1.0f, 1.0f, 1.0f);

    // Light* light2 = lightManager->lights[2];
    // light2->lightType = directional;
    // light2->direction = glm::vec3(0,0,1);
    // light2->ambient =  glm::vec3(0.05f);
    // light2->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    // light2->specular = glm::vec3(1.0f, 1.0f, 1.0f);
    
    Light* light3 = lightManager->lights[3];
    light3->lightType = directional;
    light3->direction = glm::vec3(0,0,-1);
    light3->ambient =  glm::vec3(0.05f);
    light3->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    light3->specular = glm::vec3(1.0f, 1.0f, 1.0f);

    Light* light4 = lightManager->lights[4];
    light4->lightType = spot;
    light4->position = glm::vec3(0,8,0);
    light4->direction = glm::vec3(0,-1,.0f);
    light4->angle = 3;
    light4->ambient =  glm::vec3(0.15f);
    light4->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    light4->specular = glm::vec3(1.0f, 1.0f, 1.0f);
    

    for (Light* light : lightManager->lights)
    {
        std::cout<<light->lightType<<std::endl;
    }


    // physics test
    for (size_t i = 0; i < 3; i++)
    {
        VirtualObject* sphere = new VirtualObject(SphereMesh, myTexture, whiteTexture, myShader);
        
        sphere->ObjectName = "sphere_" + std::to_string(i);
        myObjects.push_back(sphere);
        sphere->Position = glm::vec3(i * 4.0f, 0.0f, 0);

        sphere->collider = new SphereCollider();
        sphere->SetCollider();
        sphere->collider->hasGravity = true;
        sphere->collider->isKinematic = false;
    }

    VirtualObject* sphere = new VirtualObject(SphereMesh, myTexture, whiteTexture,myShader);
        
    sphere->ObjectName = "static_sphere";
    myObjects.push_back(sphere);
    sphere->Position = glm::vec3(0.0f, -5.0f, 0);

    sphere->collider = new SphereCollider();
    sphere->SetCollider();
    sphere->collider->hasGravity = true;
    sphere->collider->isKinematic = true;

    VirtualObject* box = new VirtualObject(CubeMesh, myTexture, whiteTexture,myShader);
        
    box->ObjectName = "static_cube";
    myObjects.push_back(box);
    box->Position = glm::vec3(4.0f, -5.0f, 0);

    box->collider = new BoxCollider();
    BoxCollider* boxCollider = static_cast<BoxCollider*>(box->collider);
    boxCollider->extents = glm::vec3(.5f);
    box->SetCollider();
    box->collider->hasGravity = true;
    box->collider->isKinematic = true;



    


    // for (size_t i = 0; i < 2; i++)
    // {
    //     VirtualObject* apple = new VirtualObject(AppleMesh, appleTexture, BlinnPhongMultiLights);
    //     apple->ObjectName = "apple_" + std::to_string(i);
    //     myObjects.push_back(apple);
    //     apple->Position = glm::vec3(i * 5.0f,0.0f,0);
    //     apple->Scale = glm::vec3(20.0f/((i*5+1)));
    // }

    // for (size_t i = 0; i < 2; i++)
    // {
    //     VirtualObject* apple = new VirtualObject(AppleMesh, appleTexture, NormalView);
    //     apple->ObjectName = "normal_apple_" + std::to_string(i);
    //     myObjects.push_back(apple);
    //     apple->Position = glm::vec3(i * 5.0f,3.0f,0);
    //     apple->Scale = glm::vec3(20.0f/((i*5+1)));
    // }
    

    // for (size_t i = 0; i < 2; i++)
    // {
    //     VirtualObject* apple = new VirtualObject(AppleMesh, appleTexture, BlinnPhongMultiLights);
    //     apple->ObjectName = "apple_" + std::to_string(i);
    //     myObjects.push_back(apple);
    //     apple->Position = glm::vec3(0.f,i * 5.0f,0);
    //     apple->Scale = glm::vec3(20.0f);
    // }

    // for (size_t i = 0; i < 3; i++)
    // {
    //     VirtualObject* monkey = new VirtualObject(MonkeyMesh, myTexture, BlinnPhong);
    //     monkey->ObjectName = "monkey_" + std::to_string(i);
    //     myObjects.push_back(monkey);
    //     monkey->Position = glm::vec3(i * 2.0f, -1.0f, -2);
    // }
    //
    // for (size_t i = 0; i < 3; i++)
    // {
    //     VirtualObject* teapot = new VirtualObject(TeapotMesh, myTexture, myShader);
    //     teapot->ObjectName = "teapot_" + std::to_string(i);
    //     myObjects.push_back(teapot);
    //     teapot->Position = glm::vec3(i * 2.0f, -2.0f, 4);
    //     teapot->Scale = glm::vec3(.01f, .01f, .01f);
    // }

    lightManager->CreateDepthTexture();

    return someData;
}



void Flow::BeginRender(Camera* aCamera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    LightManager::instance->RenderDepthToTextureFromSpotLight(LightManager::instance->lights[0], myObjects);

    
    for (int i = 0; i < myObjects.size(); i++)
    {
        myObjects[i]->Draw(aCamera);
    }

    ResourceHandler::Instance().ProcessMessages();

    float time = glfwGetTime();
    myBillboard->SetFloat(time, "time");

    aCamera->CameraUpdate();
    //aCamera->CameraUpdate(window);
}

void Flow::End()
{
    glfwSwapBuffers(window);
    Input(window);
    glfwPollEvents();

    currentTime = glfwGetTime();
    DeltaTime = currentTime - lastTime;
    lastTime = currentTime;
}


bool Flow::ShouldClose()
{
    if (glfwWindowShouldClose(window))
    {
        glfwTerminate();
        return true;
    }
    return false;
}

void Flow::Input(GLFWwindow* aWindow)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Flow::CreateVirtualObject(Mesh* aMesh = CubeMesh, Texture* aTexture = myTexture, Texture* aSpecularMap = whiteTexture, Shader* aShader = myShader)
{
    VirtualObject* newObject = new VirtualObject(aMesh, aTexture, aSpecularMap, aShader);
    myObjects.push_back(newObject);
}

void Flow::CreateVirtualObject()
{
    VirtualObject* newObject = new VirtualObject(CubeMesh, myTexture, whiteTexture, myShader);

    int count = 0;
    for(int i = 0; i < myObjects.size(); i++)
    {
        if(myObjects[i]->ObjectName.find("new object") == 0)
        {
            count++;
        }
    }
    newObject->ObjectName = "new object";
    if(count > 0)
    {
        newObject->ObjectName = "new object " + std::to_string(count);
    }
    myObjects.push_back(newObject);
}

void Flow::DeleteVirtualObject(std::vector<VirtualObject*>& objects, VirtualObject* objectToDelete)
{
    auto it = std::find(objects.begin(), objects.end(), objectToDelete);
    if (it != objects.end()) {
        objects.erase(it);
    }
    delete objectToDelete;
    objectToDelete = nullptr;
}

void Flow::DeleteVirtualObject(VirtualObject* objectToDelete)
{
    // std::cout << "Size before erase: " << myObjects.size() << std::endl;
    auto it = std::find(myObjects.begin(), myObjects.end(), objectToDelete);
    if (it != myObjects.end()) {
        myObjects.erase(it);
    }

    // delete objectToDelete;
    // objectToDelete = nullptr;
    // std::cout << "Size after erase: " << myObjects.size() << std::endl;
}

std::vector<VirtualObject*> Flow::GetObjects()
{
    return myObjects;
}


