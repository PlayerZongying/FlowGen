#pragma once
#include <string>

class IWritable
{
public:
    // virtual bool WriteTo(const std::string& filePath) = 0;
    //
    // virtual bool ReadFrom(const std::string& filePath) = 0;
    //
    // virtual bool WriteTo(const std::ofstream& outFile) = 0;
    //
    // virtual bool ReadFrom(const std::ifstream& inFile) = 0;

    virtual bool WriteTo(std::ofstream* outFile) = 0;

    virtual bool ReadFrom(std::ifstream* inFile) = 0;

    // virtual bool ReadFrom(const std::string& filePath) = 0;
};
