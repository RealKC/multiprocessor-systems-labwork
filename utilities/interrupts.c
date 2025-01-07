#include "utilities.h"

#define ACCESS(x) (*(volatile u32*)(x))

void EnableInterrupt(u32 intcBaseAddr, u32 interruptVector)
{
    ACCESS(intcBaseAddr + 0x10) = (1 << interruptVector);
}

void DisableInterrupt(u32 intcBaseAddr, u32 interruptVector)
{
    ACCESS(intcBaseAddr + 0x14) = (1 << interruptVector);
}

void AcknowledgeInterrupt(u32 intcBaseAddr, u32 interruptVector)
{

    ACCESS(intcBaseAddr + 0xC) |= (1 << interruptVector);
}

u32 GetPrioIntr(u32 intcBaseAddr)
{
    u32 prio = ACCESS(intcBaseAddr + 0x18);

    if (prio == 0) {
        return -1;
    }
}

void SendSoftwareInterrupt(u32 destIntcBaseAddr, u32 interruptVector)
{
    ACCESS(destIntcBaseAddr) |= (1 << interruptVector);
}
