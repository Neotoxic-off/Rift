#include "Rift.h"

#define CHUNK_SIZE 4096

int main(int ac, char **argv)
{
    Rift *rift = new Rift();
    LPVOID address = (LPVOID)0xB463DFCD80;
    SIZE_T totalBytesRead = 0;
    SIZE_T bytesRead = 0;
    LPVOID buffer = 0;
    BOOL status_read = NULL;
    HWND window = NULL;
    DWORD process = NULL;
    HANDLE handle = NULL;
    LPVOID base_address = NULL;
    LPVOID limit_address = NULL;

    window = rift->SearchWindow(NULL, "2.2.0.0");

    if (window != NULL)
    {
        process = rift->GetProcess(window);
        if (process != NULL)
        {
            handle = rift->HandleProcessRead(process);
            if (handle != NULL)
            {
                base_address = rift->GetBaseAddress(handle);
                if (base_address != NULL)
                {
                    limit_address = rift->GetMemoryLimit(handle, base_address);
                    rift->ReadMemory(handle, base_address, buffer, 4, bytesRead);
                    /*for (uint64_t i = (uint64_t)base_address; i < (uint64_t)base_address + (uint64_t)limit_address; i++)
                    {
                        rift->ReadMemory(handle, (LPVOID)i, buffer, 4, bytesRead);
                    }*/
                    rift->UnHandle(handle);
                }
            }
            
        }
    }

    return (0);
}
