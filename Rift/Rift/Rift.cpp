#include "Rift.h"

Rift::Rift(): logger()
{
    logger.Log("info", "building rift");
}

Rift::~Rift()
{
    logger.Log("info", "destroying rift");
}

void Rift::WriteMemory(DWORD address, const void* data, size_t size)
{
    // Use WriteProcessMemory to write data to the game's memory
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(address), data, size, nullptr);
}

void Rift::ReadMemory(DWORD address, void* buffer, size_t size)
{
    // Use ReadProcessMemory to read data from the game's memory
    ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), buffer, size, nullptr);
}

void Rift::ApplyModifications()
{
    // Apply game modifications here
}

void Rift::RestoreOriginalState()
{
    // Restore game's original state here
}
