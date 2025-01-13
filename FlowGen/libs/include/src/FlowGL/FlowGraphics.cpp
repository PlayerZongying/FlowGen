#include "FlowGraphics.h"
#include "VirtualObject.h"
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

#include "src/Flow/ResourceHandler.h"


GLFWwindow* window;

Shader* myShader;
Shader* myBillboard;
Shader* NormalView;
Shader* BlinnPhong;

Square* mySquare;
Triangle* myTriangle;
Cube* myCube;

Texture* myTexture;
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

    myConcreteTexture = new Texture("Assets/Images/Grass.png");
    myTexture = new Texture("Assets/Images/Default.png");
    appleTexture = new Texture("Assets/Images/Apple.jpg");
    myShader = new Shader("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShader.glsl");
    myBillboard = new Shader("Assets/Shaders/VertexBillboard.glsl", "Assets/Shaders/FragmentShader.glsl");

    // Blinn Phong Test
    BlinnPhong = new Shader("Assets/Shaders/BlinnPhongVS.glsl", "Assets/Shaders/BlinnPhongFS.glsl");
    NormalView = new Shader("Assets/Shaders/NormalViewVS.glsl", "Assets/Shaders/NormalViewFS.glsl");
    
    
    ResourceHandler::Instance().CreateMesh("Assets/Models/plane.obj", "plane");
    ResourceHandler::Instance().CreateMesh("Assets/Models/monkey.obj", "monkey");
    ResourceHandler::Instance().CreateMesh("Assets/Models/teapot.obj", "teapot");
    ResourceHandler::Instance().CreateMesh("Assets/Models/Flag.obj", "Flag");
    ResourceHandler::Instance().CreateMesh("Assets/Models/sword.obj", "sword");
    ResourceHandler::Instance().CreateMesh("Assets/Models/sphere.obj", "sphere");
    ResourceHandler::Instance().CreateMesh("Assets/Models/apple.obj", "apple");
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

    myCube = new Cube();
    mySquare = new Square();

    Camera* camera = new Camera(aWidth, aHeight);

    someData.aCamera = camera;
    someData.aWindow = window;

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);

    // for (size_t i = 0; i < 1; i++)
    // {
    //     VirtualObject* sphere = new VirtualObject(SphereMesh, myTexture, BlinnPhong);
    //     sphere->ObjectName = "sphere_" + std::to_string(i);
    //     myObjects.push_back(sphere);
    //     sphere->Position = glm::vec3(i * 2.0f, 0.0f, 0);
    // }

    for (size_t i = 0; i < 1; i++)
    {
        VirtualObject* apple = new VirtualObject(AppleMesh, appleTexture, BlinnPhong);
        apple->ObjectName = "apple_" + std::to_string(i);
        myObjects.push_back(apple);
        apple->Position = glm::vec3(i * 2.0f, 0.0f, 0);
        apple->Scale = glm::vec3(20);
    }

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

    return someData;
}



void Flow::BeginRender(Camera* aCamera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < myObjects.size(); i++)
    {
        myObjects[i]->Draw(aCamera);
    }

    float time = glfwGetTime();
    myBillboard->SetFloat(time, "time");

    aCamera->CameraUpdate();
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

void Flow::CreateVirtualObject(Mesh* aMesh, Texture* aTexture, Shader* aShader)
{
    VirtualObject* newObject = new VirtualObject(aMesh, aTexture, aShader);
    myObjects.push_back(newObject);
}

std::vector<VirtualObject*> Flow::GetObjects()
{
    return myObjects;
}
