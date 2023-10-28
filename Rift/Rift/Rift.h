#pragma once

#include <windows.h>
#include <iostream>
#include <psapi.h>
#include <tlhelp32.h>
#include <iomanip>

#include "Logs.h"
#include "Errors.h"
#include "Logger.h"

class Rift
{
    public:
        Rift();
        ~Rift();

        BOOL WriteMemory(HANDLE, LPVOID, LPVOID, SIZE_T, SIZE_T);
        BOOL ReadMemory(HANDLE, LPCVOID, LPVOID, SIZE_T, SIZE_T);
        HANDLE HandleProcessRead(DWORD);
        HANDLE HandleProcessWrite(DWORD);
        BOOL UnHandle(HANDLE);

        DWORD GetProcess(HWND);
        HWND SearchWindow(LPCSTR, LPCSTR);
        LPVOID GetBaseAddress(HANDLE);
        LPVOID GetMemoryLimit(HANDLE, LPVOID);

    private:
        Logger logger;
};