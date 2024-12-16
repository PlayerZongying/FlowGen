#include "Level.h"
#include <src/FlowGL/FlowGraphics.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include <filesystem>
#include "VirtualObject.h"

void Level::SaveLevel(const std::string& levelName)
{
    std::string filePath = "Assets/Levels/" + levelName + ".bin";
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return;
    }
    std::vector<VirtualObject*> myObjects = Flow::GetObjects();
    size_t objectsAmount = myObjects.size();

    outFile.write(reinterpret_cast<const char*>(&objectsAmount), sizeof(objectsAmount));

    for (VirtualObject* object : myObjects)
    {
        object->WriteTo(&outFile);
    }

    std::cout << levelName << " Saved!" << std::endl;
}

void Level::LoadLevel(const std::string& levelName)
{
    std::string filePath = "Assets/Levels/" + levelName + ".bin";
    std::ifstream inFile(filePath, std::ios::binary);

    if (!inFile.is_open())
    {
        std::cerr << "Failed to open file for reading: " << filePath << std::endl;
        return;
    }

    size_t objectsAmount;
    inFile.read(reinterpret_cast<char*>(&objectsAmount), sizeof(objectsAmount));

    std::cout << "objects amount: " << objectsAmount << std::endl;

    std::vector<VirtualObject*> myObjects = Flow::GetObjects();
    // clean objects

    for(unsigned int i = 0; i < objectsAmount; i++)
    {
        // create virtual objects
        if(i < myObjects.size())
        {
            myObjects[i]->ReadFrom(&inFile);
        }
    }
}
