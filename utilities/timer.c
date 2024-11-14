#include "xil_types.h"

void TimerSetLoadReg(u32 timerBaseAddr, u32 timerNumber, u32 loadValue)
{
    u32 timerOffset = timerNumber * 0x10;

    u32 volatile* loadReg = (u32 volatile*)(timerBaseAddr + timerOffset + 0x04);
    u32 volatile* csr = (u32 volatile*)(timerBaseAddr + timerOffset + 0x0);

    *loadReg = loadValue;
    *csr = *csr | (1 << 5);
    *csr = *csr & ~(1 << 5);
}

void TimerReset(u32 timerBaseAddr, u32 timerNumber)
{
    u32 timerOffset = timerNumber * 0x10;

    u32 volatile* csr = (u32 volatile*)(timerBaseAddr + timerOffset + 0x0);

    *csr = *csr | (1 << 5);
    *csr = *csr & ~(1 << 5);
}

void TimerStart(u32 timerBaseAddr, u32 timerNumber)
{
    u32 timerOffset = timerNumber * 0x10;

    u32 volatile* csr = (u32 volatile*)(timerBaseAddr + timerOffset + 0x0);

    *csr = *csr | (1 << 7);
}

void TimerStop(u32 timerBaseAddr, u32 timerNumber)
{
    u32 timerOffset = timerNumber * 0x10;

    u32 volatile* csr = (u32 volatile*)(timerBaseAddr + timerOffset + 0x0);

    *csr = *csr & ~(1 << 7);
}

u32 TimerGetStatus(u32 timerBaseAddr, u32 timerNumber)
{
    u32 timerOffset = timerNumber * 0x10;

    u32 volatile* csr = (u32 volatile*)(timerBaseAddr + timerOffset + 0x0);

    return *csr;
}

u32 TimerGetCounter(u32 timerBaseAddr, u32 timerNumber)
{
    u32 timerOffset = timerNumber * 0x10;

    u32 volatile* counter = (u32 volatile*)(timerBaseAddr + timerOffset + 0x8);

    return *counter;
}
