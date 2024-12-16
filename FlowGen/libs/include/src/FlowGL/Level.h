#pragma once
#include <string>

class Level
{
public:
    char* LevelName;
    char* LevelPath;

    static void SaveLevel(const std::string& levelName);

    static void LoadLevel(const std::string& levelName);
    
};
