#pragma once

#include <windows.h>
#include <iostream>

#include "Logs.h"
#include "Logger.h"

class Rift
{
    public:
        Rift();
        ~Rift();

        void WriteMemory(DWORD address, const void* data, size_t size);
        void ReadMemory(DWORD address, void* buffer, size_t size);

        void ApplyModifications();
        void RestoreOriginalState();

    private:
        Logger logger;
};