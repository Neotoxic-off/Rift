#include "Rift.h"

Rift::Rift(): logger()
{
    logger.Log("wait", LOG_WAIT_LOADING_RIFT);
}

Rift::~Rift()
{
    logger.Log("wait", LOG_WAIT_DESTROYING_RIFT);
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
