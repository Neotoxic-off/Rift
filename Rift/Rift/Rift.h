#pragma once

#include <windows.h>
#include <iostream>
#include <Psapi.h>

#include "Logs.h"
#include "Errors.h"
#include "Logger.h"

class Rift
{
    public:
        Rift();
        ~Rift();

        BOOL WriteMemory(HANDLE, void *, DWORD, size_t);
        BOOL ReadMemory(HANDLE, void *, DWORD, size_t);
        HANDLE HandleProcess(DWORD);
        BOOL UnHandle(HANDLE);

        void ApplyModifications();
        void RestoreOriginalState();

    private:
        Logger logger;
};