#include "Rift.h"

int main(int ac, char **argv)
{
    Rift rift = Rift();

    DWORD value = 0;
    size_t read = 0;
    DWORD new_value = 100;
    DWORD process = 12792;
    void *address = (void *)0x1663B6B0;
    HANDLE handle = rift.HandleProcess(process);

    rift.ReadMemory(handle, address, value, read);
    rift.WriteMemory(handle, address, new_value, read);
    rift.UnHandle(handle);

    return (0);
}
