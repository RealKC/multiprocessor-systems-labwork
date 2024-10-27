#include "xil_types.h"
#include "xparameters.h"

void MutexLock(int mutexNumber, int cpu)
{
    u32 volatile* mutex = (u32 volatile*)(XPAR_MUTEX_0_BASEADDR + 256 * mutexNumber);

    u32 expected = cpu << 1 | 1;

    while (TRUE) {
        *mutex = expected;

        if (*mutex == expected)
            return;
    }
}

int MutexUnlock(int mutexNumber, int cpu)
{
    u32 volatile* mutex = (u32 volatile*)(XPAR_MUTEX_0_BASEADDR + 256 * mutexNumber);

    *mutex = cpu << 1;

    if ((*mutex & 0x1) == 0) {
        return TRUE;
    }

    return FALSE;
}
