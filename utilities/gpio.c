#include "utilities.h"

void InitLeds(void)
{
    u32 volatile* data_addr = (u32 volatile*)(XPAR_AXI_GPIO_1_BASEADDR);
    u32 volatile* tri_addr = (u32 volatile*)(XPAR_AXI_GPIO_1_BASEADDR + 0x4);

    *tri_addr = 0x0;
    *data_addr = 0xFF;
}

void SetLeds(u32 newLedVal)
{
    u32 volatile* data_addr = (u32 volatile*)(XPAR_AXI_GPIO_1_BASEADDR);

    *data_addr = ~newLedVal;
}

void SetLed(u32 ledNumber, u32 newLedVal)
{
    u32 volatile* data_addr = (u32 volatile*)(XPAR_AXI_GPIO_1_BASEADDR);

    if (newLedVal) {
        *data_addr |= (1 << ledNumber);
    } else {
        *data_addr &= ~(1 << ledNumber);
    }
}

u32 currentlyShownDigits[8];

#define INIT_ANODE (0x80)

static u32 gpio7SegAnode = INIT_ANODE;

u32 volatile* gpio_7_seg_cat_data_addr = (u32*)(XPAR_AXI_GPIO_0_BASEADDR);
u32 volatile* gpio_7_seg_cat_tri_addr = (u32*)(XPAR_AXI_GPIO_0_BASEADDR + 0x4);
u32 volatile* gpio_7_seg_and_data_addr = (u32*)(XPAR_AXI_GPIO_0_BASEADDR + 0x8);
u32 volatile* gpio_7_seg_and_tri_addr = (u32*)(XPAR_AXI_GPIO_0_BASEADDR + 0xC);

void Init7Seg(void)
{
    for (u32 i = 0; i < 8; ++i) {
        currentlyShownDigits[i] = 0;
    }

    // Set GPIOs as Input/Output
    *gpio_led_tri_addr = 0x0;
    *gpio_sw_tri_addr = 0xFFFF;
    *gpio_7_seg_cat_tri_addr = 0x0;
    *gpio_7_seg_and_tri_addr = 0x0;
}

static u32 const digits[16] = {
    // 0x0
    ~0x3F,
    // 0x1
    ~0x06,
    // 0x2
    ~0x5B,
    // 0x3
    ~0x4F,
    // 0x4
    ~0x66,
    // 0x5
    ~0x6D,
    // 0x6
    ~0x7D,
    // 0x7
    ~0x07,
    // 0x8
    ~0x7F,
    // 0x9
    ~0x6F,
    // 0xA
    0x77,
    // 0xB
    0x7C,
    // 0xC
    0x39,
    // 0xD
    0x5E,
    // 0xE
    0x79,
    // 0xF
    0x71
};

u32 HexToCat(u32 valToTranslate)
{
    return digits[valToTranslate % 16];
}

void DisplayHex7Seg(u32 numToDisplay)
{
    currentlyShownDigits[0] = HexToCat((numToDisplay & 0x0000000F) >> 0);
    currentlyShownDigits[1] = HexToCat((numToDisplay & 0x000000F0) >> 4);
    currentlyShownDigits[2] = HexToCat((numToDisplay & 0x00000F00) >> 8);
    currentlyShownDigits[3] = HexToCat((numToDisplay & 0x0000F000) >> 12);
    currentlyShownDigits[4] = HexToCat((numToDisplay & 0x000F0000) >> 16);
    currentlyShownDigits[5] = HexToCat((numToDisplay & 0x00F00000) >> 20);
    currentlyShownDigits[6] = HexToCat((numToDisplay & 0x0F000000) >> 24);
    currentlyShownDigits[7] = HexToCat((numToDisplay & 0xF0000000) >> 28);
}

void Write7SegToGPIO(void)
{
    u32 index = 0;

    gpio7SegAnode = INIT_ANODE;

    while (gpio7SegAnode != 0) {

        *gpio_7_seg_and_data_addr = ~gpio_7_seg_and;
        *gpio_7_seg_cat_data_addr = currentlyShownDigits[index++ % 8];

        gpio7SegAnode >>= 1;
    }
}
