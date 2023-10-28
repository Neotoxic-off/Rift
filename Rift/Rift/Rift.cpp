#include "Rift.h"

Rift::Rift(): logger()
{
    logger.Log("wait", LOG_WAIT_LOADING_RIFT);
}

Rift::~Rift()
{
    logger.Log("wait", LOG_WAIT_DESTROYING_RIFT);
}

BOOL Rift::WriteMemory(HANDLE process, LPVOID address, LPVOID buffer, SIZE_T buffer_size, SIZE_T bytes_read)
{
    BOOL read = false;

    logger.Log("wait", "writing memory");
    read = WriteProcessMemory(process, address, &buffer, buffer_size, &bytes_read);

    if (read == true) {
        logger.Log("done", std::format("memory wrote at: {}", address));
        logger.Log("memory", std::format("[{}]: {}", address, buffer));
    }
    else {
        logger.Log("error", std::format("failed to write at: {}: {}", address, GetLastError()));
    }

    return (read);
}

BOOL Rift::ReadMemory(HANDLE process, LPCVOID address, LPVOID buffer, SIZE_T buffer_size, SIZE_T bytes_read)
{
    BOOL read = false;

    logger.Log("wait", "reading memory");
    read = ReadProcessMemory(process, (void *)address, &buffer, buffer_size, &bytes_read);

    if (read == true) {
        logger.Log("done", std::format("memory read at: {}", address));
        logger.Log("memory", std::format("[{}]: {}", address, buffer));
    }
    else {
        logger.Log("error", std::format("failed to read at: {}", address));
    }

    return (read);
}

HANDLE Rift::HandleProcessRead(DWORD process_id)
{
    HANDLE handle = NULL;

    logger.Log("wait", std::format("handling process {}", process_id));
    handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);
    if (handle != NULL) {
        logger.Log("done", std::format("handled process {}", process_id));
    }
    else {
        logger.Log("error", std::format("failed to open process {}", process_id));
    }

    return (handle);
}

HANDLE Rift::HandleProcessWrite(DWORD process_id)
{
    HANDLE handle = NULL;

    logger.Log("wait", std::format("handling process {}", process_id));
    handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);
    if (handle != NULL) {
        logger.Log("done", std::format("handled process {}", process_id));
    }
    else {
        logger.Log("error", std::format("failed to open process {}", process_id));
    }

    return (handle);
}

BOOL Rift::UnHandle(HANDLE handle)
{
    BOOL status = false;

    logger.Log("wait", std::format("unhandling {}", handle));
    status = CloseHandle(handle);

    if (status == true)
    {
        logger.Log("done", std::format("unhandled {} successfully", handle));
    } else
    {
        logger.Log("error", std::format("failed to unhandle {}", handle));
    }

    return (status);
}

HWND Rift::SearchWindow(LPCSTR class_name, LPCSTR window)
{
    HWND hwnd = NULL;

    logger.Log("wait", std::format("searching window {}", window));
    hwnd = FindWindowA(class_name, window);

    if (hwnd != NULL)
    {
        logger.Log("done", std::format("window found {}", window));
    }
    else
    {
        logger.Log("error", std::format("window not found {}", window));
    }

    return (hwnd);
}

DWORD Rift::GetProcess(HWND window)
{
    DWORD process = NULL;
    DWORD status = NULL;

    logger.Log("wait", "getting process");
    status = GetWindowThreadProcessId(window, &process);

    if (status != NULL)
    {
        logger.Log("done", "process found");
    }
    else
    {
        logger.Log("error", "process not found");
    }

    return (process);
}

LPVOID Rift::GetBaseAddress(HANDLE handle)
{
    DWORD needed;
    TCHAR moduleName[MAX_PATH];
    HMODULE moduleHandles[1024];
    BOOL status = EnumProcessModules(handle, moduleHandles, sizeof(moduleHandles), &needed);
    uint64_t base_address = 0;

    if (status > 0)
    {
        if (GetModuleBaseName(handle, moduleHandles[0], moduleName, sizeof(moduleName) / sizeof(TCHAR)) > 0)
        {
            base_address = reinterpret_cast<uint64_t>(moduleHandles[0]);
            logger.Log("memory", std::format("address of the process: 0x{:X}", (uint64_t)base_address));
        }
        else {
            logger.Log("error", std::format("fail to get module base name. Error code: {}", GetLastError()));
        }
    }
    else {
        logger.Log("error", std::format("fail to enumerate process modules. Error code: {}", GetLastError()));
    }

    return ((LPVOID)base_address);
}

LPVOID Rift::GetMemoryLimit(HANDLE handle, LPVOID base_address)
{
    MEMORY_BASIC_INFORMATION memInfo;
    LPVOID address = base_address;
    LPVOID limit = NULL;

    while (VirtualQueryEx(handle, address, &memInfo, sizeof(memInfo)) == sizeof(memInfo))
    {
        if (memInfo.AllocationBase == base_address)
        {
            address = LPVOID((uintptr_t)memInfo.BaseAddress + memInfo.RegionSize);
        }
        else
        {
            limit = (LPVOID)((uintptr_t)address - (uintptr_t)base_address);
            logger.Log("memory", std::format("limit of the process: {}", limit));
            return (limit);
        }
    }

    return (limit);
}