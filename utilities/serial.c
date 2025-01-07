#include "utilities.h"

u32 UartGetStatus(u32 uartBaseAddr)
{
    return *(u32 volatile*)(uartBaseAddr + 0x08);
}

void UartTransmitBlocking(u32 uartBaseAddr, u8 const* srcDataPtr, u32 dataLen)
{
    u16 i;

    u8 volatile* tx = (u8 volatile*)(uartBaseAddr + 0x04);

    for (i = 0; i < dataLen; ++i) {
        while ((UartGetStatus(uartBaseAddr) & 0x8)) {
            ; // block to wait for space in the queue
        }

        *tx = srcDataPtr[i];
    }
}

u16 UartReceiveBlocking(u32 uartBaseAddr, u8* destDataPtr, u32 dataLen)
{
    u16 i = 0;
    u8 volatile* rx = (u8 volatile*)(uartBaseAddr + 0x00);

    while (i < dataLen) {
        // maybe check parity and frame errors?

        while (!(UartGetStatus(uartBaseAddr) & 0x1)) {
            ; // block to wait for a character
        }

        read_buf[i] = *rx;
        i++;
    }

    return i;
}
