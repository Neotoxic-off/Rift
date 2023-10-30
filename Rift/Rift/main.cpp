#include "Rift.h"

int main(int ac, char **argv)
{
    Rift *rift = new Rift();
    LPVOID address = (LPVOID)0xB463DFCD80;
    SIZE_T bytes_read = 0;
    unsigned char *buffer = (unsigned char*)calloc(1, 4);
    int byte = 0x0;
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
                    limit_address = rift->GetProcessMemorySize(handle, base_address);
                    for (uint64_t i = (uint64_t)base_address; i < ((uint64_t)base_address + (uint64_t)limit_address); ++i) {
                        LPVOID current_address = reinterpret_cast<LPVOID>(i);
                        rift->ReadMemory(handle, current_address, &buffer, 1, &bytes_read);

                        byte = static_cast<int>(*reinterpret_cast<unsigned char*>(buffer));
                        rift->disassembler.Add(current_address, byte);
                    }
                    rift->UnHandle(handle);
                }
            }
        }
    }

    return (0);
}
