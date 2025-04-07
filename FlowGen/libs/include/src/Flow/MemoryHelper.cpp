#include "MemoryHelper.h"
#include <windows.h>
#include <iostream>

float MemoryHelper::CheckAvailableMemoryInMB()
{
    float AvailableMemoryInMB;

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&memInfo))
    {
        std::cout << "Memory Information:\n";
        // std::cout << "Total Physical Memory: " << memInfo.ullTotalPhys / (1024 * 1024) << " MB\n";
        std::cout << "Available Physical Memory: " << memInfo.ullAvailPhys / (1024 * 1024) << " MB\n";
        // std::cout << "Total Virtual Memory: " << memInfo.ullTotalVirtual / (1024 * 1024) << " MB\n";
        // std::cout << "Available Virtual Memory: " << memInfo.ullAvailVirtual / (1024 * 1024) << " MB\n";
        std::cout << "Memory Load: " << memInfo.dwMemoryLoad << " %\n";
        AvailableMemoryInMB = memInfo.ullAvailPhys / (1024 * 1024);
    }
    else
    {
        std::cerr << "Failed to retrieve memory status.\n";
    }

    return AvailableMemoryInMB;
}
