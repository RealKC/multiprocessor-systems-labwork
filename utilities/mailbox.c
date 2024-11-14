#include "utilities.h"

#define MBOX_STATUS_REG(MboxIfBaseAddr) ((u32 volatile*)((MboxIfBaseAddr) + 0x10))
#define MBOX_CTRL_REG(MboxIfBaseAddr) ((u32 volatile*)((MboxIfBaseAddr) + 0x2c))
#define MBOX_READ_REG(MboxIfBaseAddr) ((u32 volatile*)((MboxIfBaseAddr) + 0x8))
#define MBOX_WRITE_REG(MboxIfBaseAddr) ((u32 volatile*)((MboxIfBaseAddr) + 0x0))

u32 MboxIsEmpty(u32 mboxIfBaseAddr)
{
    u32 status = *MBOX_STATUS_REG(mboxIfBaseAddr);

    return status & 0x1;
}

u32 MboxIsFull(u32 mboxIfBaseAddr)
{
    u32 status = *MBOX_STATUS_REG(mboxIfBaseAddr);

    return (status & 0x2) >> 1;
}

void MboxFlushReceive(u32 mboxIfBaseAddr)
{
    *MBOX_CTRL_REG(mboxIfBaseAddr) = 0x2;
}

void MboxFlushWrite(u32 mboxIfBaseAddr)
{
    *MBOX_CTRL_REG(mboxIfBaseAddr) = 0x1;
}

void MboxReadBlocking(u32 mboxIfBaseAddr, u32* destDataPtr, u32 dataLen)
{
    u32 read = 0;

    while (read < dataLen) {
        while (MboxIsEmpty(mboxIfBaseAddr)) {
            /* wait for data */;
        }

        destDataPtr[read] = *MBOX_READ_REG(mboxIfBaseAddr);
        read++;
    }
}

void MboxWriteBlocking(u32 mboxIfBaseAddr, u32* srcDataPtr, u32 dataLen)
{
    int i = 0;

    for (i = 0; i < dataLen; ++i) {
        while (MboxIsFull(mboxIfBaseAddr)) {
            /* wait for space in the mailbox */;
        }

        *MBOX_WRITE_REG(mboxIfBaseAddr) = srcDataPtr[i];
    }
}
