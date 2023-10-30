#include "Rift.h"

Rift::Rift(): logger(true)
{
    logger.Log("wait", LOG_WAIT_LOADING_RIFT);

    disassembler = Disassembler();
}

Rift::~Rift()
{
    logger.Log("wait", LOG_WAIT_DESTROYING_RIFT);
}

BOOL Rift::WriteMemory(HANDLE process, LPVOID address, LPVOID buffer, SIZE_T buffer_size, SIZE_T *bytes_read)
{
    BOOL read = false;

    logger.Log("wait", LOG_WAIT_MEMORY_WRITE);
    read = WriteProcessMemory(process, address, buffer, buffer_size, bytes_read);

    if (read == true)
    {
        logger.Log("done", std::format("{} {}", LOG_DONE_MEMORY_WRITE, (LPVOID)address));
        logger.Log("memory", std::format("[{}]: {}", (LPVOID)address, buffer));
    }
    else {
        logger.Log("error", std::format("{} {}: {}", LOG_FAIL_MEMORY_WRITE, (LPVOID)address, GetLastError()));
    }

    return (read);
}

BOOL Rift::ReadMemory(HANDLE process, LPCVOID address, LPVOID buffer, SIZE_T buffer_size, SIZE_T *bytes_read)
{
    BOOL read = false;

    logger.Log("wait", LOG_WAIT_MEMORY_READ);
    read = ReadProcessMemory(process, address, buffer, buffer_size, bytes_read);

    if (read == true)
    {
        logger.Log("done", std::format("{} {}", LOG_DONE_MEMORY_READ, (LPVOID)address));
        logger.Log("memory", std::format("[{}]: {} ({} bytes)", (LPVOID)address, buffer, (SIZE_T)buffer_size));
    }
    else
    {
        logger.Log("error", std::format("{} {}", LOG_FAIL_MEMORY_READ, (LPVOID)address));
    }

    return (read);
}

HANDLE Rift::HandleProcessRead(DWORD process_id)
{
    HANDLE handle = NULL;

    logger.Log("wait", std::format("{} {}", LOG_WAIT_HANDLING, process_id));
    handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);
    if (handle != NULL)
    {
        logger.Log("done", std::format("{} {}", LOG_DONE_HANDLING, process_id));
    }
    else
    {
        logger.Log("error", std::format("{} {}", LOG_FAIL_HANDLING, process_id));
    }

    return (handle);
}

HANDLE Rift::HandleProcessWrite(DWORD process_id)
{
    HANDLE handle = NULL;

    logger.Log("wait", std::format("{} {}", LOG_WAIT_HANDLING, process_id));
    handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, process_id);
    if (handle != NULL)
    {
        logger.Log("done", std::format("{} {}", LOG_DONE_HANDLING, process_id));
    }
    else
    {
        logger.Log("error", std::format("{} {}", LOG_FAIL_HANDLING, process_id));
    }

    return (handle);
}

BOOL Rift::UnHandle(HANDLE handle)
{
    BOOL status = false;

    logger.Log("wait", std::format("{} {}", LOG_WAIT_UNHANDLE, handle));
    status = CloseHandle(handle);

    if (status == true)
    {
        logger.Log("done", std::format("{} {}", LOG_DONE_UNHANDLE, handle));
    } else
    {
        logger.Log("error", std::format("{} {}", LOG_FAIL_UNHANDLE, handle));
    }

    return (status);
}

HWND Rift::SearchWindow(LPCSTR class_name, LPCSTR window)
{
    HWND hwnd = NULL;

    logger.Log("wait", std::format("{} {}", LOG_WAIT_SEARCH_WINDOW, window));
    hwnd = FindWindowA(class_name, window);

    if (hwnd != NULL)
    {
        logger.Log("done", std::format("{} {}", LOG_DONE_SEARCH_WINDOW, window));
    }
    else
    {
        logger.Log("error", std::format("{} {}", LOG_FAIL_SEARCH_WINDOW, window));
    }

    return (hwnd);
}

DWORD Rift::GetProcess(HWND window)
{
    DWORD process = NULL;
    DWORD status = NULL;

    logger.Log("wait", std::format("{}", LOG_WAIT_GET_PROCESS));
    status = GetWindowThreadProcessId(window, &process);

    if (status != NULL)
    {
        logger.Log("done", std::format("{} {}", LOG_DONE_GET_PROCESS, process));
    }
    else
    {
        logger.Log("error", std::format("{}", LOG_FAIL_GET_PROCESS));
    }

    return (process);
}

LPVOID Rift::GetBaseAddress(HANDLE handle)
{
    DWORD needed;
    TCHAR moduleName[MAX_PATH];
    HMODULE moduleHandles[1024];
    uint64_t base_address = 0;
    BOOL status = false;

    logger.Log("wait", std::format("{} {}", LOG_WAIT_ENUMERATE_MODULES, handle));
    status = EnumProcessModules(handle, moduleHandles, sizeof(moduleHandles), &needed);

    if (status > 0)
    {
        logger.Log("done", std::format("{} {}", LOG_DONE_ENUMERATE_MODULES, handle));
        if (GetModuleBaseName(handle, moduleHandles[0], moduleName, sizeof(moduleName) / sizeof(TCHAR)) > 0)
        {
            base_address = reinterpret_cast<uint64_t>(moduleHandles[0]);
            logger.Log("memory", std::format("{} 0x{:X}", LOG_MEMORY_BASE_ADDRESS, (uint64_t)base_address));
        }
        else
        {
            logger.Log("error", std::format("[{}] {}", GetLastError(), LOG_FAIL_BASE_ADDRESS));
        }
    }
    else
    {
        logger.Log("error", std::format("[{}] {} {}", GetLastError(), LOG_FAIL_ENUMERATE_MODULES, handle));
    }

    return ((LPVOID)base_address);
}

LPVOID Rift::GetProcessMemorySize(HANDLE handle, LPVOID base_address)
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
            logger.Log("memory", std::format("memory size of the process: {}", limit));
            return (limit);
        }
    }

    return (limit);
}
