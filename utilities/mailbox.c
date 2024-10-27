#include "xil_types.h"
#include "xparameters.h"

#define MBOX_STATUS_REG(MboxIfBaseAddr) ((u32 volatile*)((MboxIfBaseAddr) + 0x10))
#define MBOX_CTRL_REG(MboxIfBaseAddr) ((u32 volatile*)((MboxIfBaseAddr) + 0x2c))
#define MBOX_READ_REG(MboxIfBaseAddr) ((u32 volatile*)((MboxIfBaseAddr) + 0x8))
#define MBOX_WRITE_REG(MboxIfBaseAddr) ((u32 volatile*)((MboxIfBaseAddr) + 0x0))

int MboxIsEmpty(u32 MboxIfBaseAddr)
{
    u32 status = *MBOX_STATUS_REG(MboxIfBaseAddr);

    return status & 0x1;
}

int MboxIsFull(u32 MboxIfBaseAddr)
{
    u32 status = *MBOX_STATUS_REG(MboxIfBaseAddr);

    return (status & 0x2) >> 1;
}

int MboxFlushReceive(u32 MboxIfBaseAddr)
{
    *MBOX_CTRL_REG(MboxIfBaseAddr) = 0x2;
}

void MboxFlushTransmit(u32 MboxIfBaseAddr)
{
    *MBOX_CTRL_REG(MboxIfBaseAddr) = 0x1;
}

void MboxReadBlocking(u32 MboxIfBaseAddr, u32* destDataPtr, u32 dataLen)
{
    u32 read = 0;

    while (read < dataLen) {
        while (MboxIsEmpty(MboxIfBaseAddr)) {
            /* wait for data */;
        }

        destDataPtr[read] = *MBOX_READ_REG(MboxIfBaseAddr);
        read++;
    }
}

void MboxWriteBlocking(u32 MboxIfBaseAddr, u32* srcDataPtr, u32 dataLen)
{
    int i = 0;

    for (i = 0; i < dataLen; ++i) {
        while (MboxIsFull(MboxIfBaseAddr)) {
            /* wait for space in the mailbox */;
        }

        *MBOX_WRITE_REG(MboxIfBaseAddr) = srcDataPtr[i];
    }
}
