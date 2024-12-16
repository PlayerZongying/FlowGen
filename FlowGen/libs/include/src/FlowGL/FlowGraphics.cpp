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

Square* mySquare;
Triangle* myTriangle;
Cube* myCube;

Texture* myTexture;
Texture* myConcreteTexture;
Mesh* CubeMesh;
Mesh* PlaneMesh;
Mesh* FlagMesh;
Mesh* MonkeyMesh;
Mesh* TeapotMesh;

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
    myShader = new Shader("Assets/Shaders/VertexShader.glsl", "Assets/Shaders/FragmentShader.glsl");
    myBillboard = new Shader("Assets/Shaders/VertexBillboard.glsl", "Assets/Shaders/FragmentShader.glsl");

    ResourceHandler::Instance().CreateMesh("Assets/Models/plane.obj", "plane");
    ResourceHandler::Instance().CreateMesh("Assets/Models/monkey.obj", "monkey");
    ResourceHandler::Instance().CreateMesh("Assets/Models/teapot.obj", "teapot");
    ResourceHandler::Instance().CreateMesh("Assets/Models/Flag.obj", "Flag");
    ResourceHandler::Instance().AddMesh(new Cube(), "cube");


    FlagMesh = ResourceHandler::Instance().GetMesh("Flag");
    PlaneMesh = ResourceHandler::Instance().GetMesh("plane");
    MonkeyMesh = ResourceHandler::Instance().GetMesh("monkey");
    TeapotMesh = ResourceHandler::Instance().GetMesh("teapot");
    CubeMesh = ResourceHandler::Instance().GetMesh("cube");
    // FlagMesh = LoadObjMesh("Assets/Models/Flag.obj");

    // MonkeyMesh = LoadObjMesh("Assets/Models/monkey.obj");

    myCube = new Cube();
    mySquare = new Square();

    Camera* camera = new Camera(aWidth, aHeight);

    someData.aCamera = camera;
    someData.aWindow = window;

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);

    for (size_t i = 0; i < 3; i++)
    {
        VirtualObject* flag = new VirtualObject(FlagMesh, myTexture, myShader);
        flag->ObjectName = "flag_" + std::to_string(i);
        myObjects.push_back(flag);
        flag->Position = glm::vec3(i * 2.0f, 0.0f, 0);
    }

    for (size_t i = 0; i < 3; i++)
    {
        VirtualObject* monkey = new VirtualObject(FlagMesh, myTexture, myShader);
        monkey->ObjectName = "monkey_" + std::to_string(i);
        myObjects.push_back(monkey);
        monkey->Position = glm::vec3(i * 2.0f, -1.0f, -2);
    }

    for (size_t i = 0; i < 3; i++)
    {
        VirtualObject* teapot = new VirtualObject(CubeMesh, myTexture, myShader);
        teapot->ObjectName = "teapot_" + std::to_string(i);
        myObjects.push_back(teapot);
        teapot->Position = glm::vec3(i * 2.0f, -2.0f, 4);
    }

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
