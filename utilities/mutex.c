#include "utilities.h"

void MutexLock(u32 mutexBaseAddr, u32 mutexNumber, u32 cpuId)
{
    u32 volatile* mutex = (u32 volatile*)(mutexBaseAddr + 256 * mutexNumber);

    u32 expected = cpu << 1 | 1;

    while (1) {
        *mutex = expected;

        if (*mutex == expected)
            return;
    }
}

int MutexUnlock(u32 mutexBaseAddr, u32 mutexNumber, u32 cpuId)
{
    u32 volatile* mutex = (u32 volatile*)(mutexBaseAddr + 256 * mutexNumber);

    *mutex = cpu << 1;

    if ((*mutex & 0x1) == 0) {
        return 1;
    }

    return 0;
}
