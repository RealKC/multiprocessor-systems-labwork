#include "xil_types.h"
#include "xparameters.h"

#define TX_ADDR (XPAR_UARTLITE_0_BASEADDR + 0x04)
#define STATUS_REG (XPAR_UARTLITE_0_BASEADDR + 0x08)
#define RX_ADDR (XPAR_UARTLITE_0_BASEADDR)

#define ACCESS(type, addr) (*(volatile type*)(addr))

void write_serial(u8 const* data, u16 len)
{
    u16 i;

    for (i = 0; i < len; ++i) {
        while (ACCESS(u32, STATUS_REG) & (0x1 << 3)) {
            ; // block to wait for queue to empty
        }

        ACCESS(u8, TX_ADDR) = data[i];
    }
}

u16 read_serial(u8* read_buf, u8 terminator)
{
    u16 i = 0;
    u8 recv;

    while (1) {
        // maybe check parity and frame errors?

        while (!(ACCESS(u32, STATUS_REG) & 0x1)) {
            ; // block to wait for receiving a character
        }

        recv = ACCESS(u8, RX_ADDR);

        read_buf[i] = recv;
        i++;

        if (recv == terminator) {
            break;
        }
    }

    return i;
}
