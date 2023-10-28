#include "Rift.h"

Rift::Rift(): logger()
{
    logger.Log("wait", LOG_WAIT_LOADING_RIFT);
}

Rift::~Rift()
{
    logger.Log("wait", LOG_WAIT_DESTROYING_RIFT);
}

BOOL Rift::WriteMemory(HANDLE process, void *address, DWORD buffer, size_t bytes_read)
{
    BOOL read = false;

    logger.Log("wait", "writing memory");
    read = WriteProcessMemory(process, address, &buffer, sizeof(buffer), &bytes_read);

    if (read == true) {
        logger.Log("done", std::format("memory wrote at: {}", address));
        logger.Log("memory", std::format("[{}]: {}", address, buffer));
    }
    else {
        logger.Log("error", std::format("failed to write at: {}: {}", address, GetLastError()));
    }

    return (read);
}

BOOL Rift::ReadMemory(HANDLE process, void *address, DWORD buffer, size_t bytes_read)
{
    BOOL read = false;

    logger.Log("wait", "reading memory");
    read = ReadProcessMemory(process, address, &buffer, sizeof(buffer), &bytes_read);

    if (read == true) {
        logger.Log("done", std::format("memory read at: {}", address));
        logger.Log("memory", std::format("[{}]: {}", address, buffer));
    }
    else {
        logger.Log("error", std::format("failed to read at: {}", address));
    }

    return (read);
}

HANDLE Rift::HandleProcess(DWORD process_id)
{
    HANDLE handle = NULL;

    logger.Log("wait", std::format("handling process {}", process_id));
    handle = OpenProcess(PROCESS_VM_READ, FALSE, process_id);
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

    if (status == true) {
        logger.Log("done", std::format("unhandled {} successfully", handle));
    } else {
        logger.Log("error", std::format("failed to unhandle {}", handle));
    }

    return (status);
}

void Rift::ApplyModifications()
{
    // Apply game modifications here
}

void Rift::RestoreOriginalState()
{
    // Restore game's original state here
}
