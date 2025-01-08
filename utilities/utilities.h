#ifndef KC_UTILITIES_H
#define KC_UTILITIES_H

#include "xil_exception.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "xparameters.h"

#define CPU_ID XPAR_CPU_ID

// Mailbox functions
u32 MboxIsEmpty(u32 mboxIfBaseAddr);
u32 MboxIsFull(u32 mboxIfBaseAddr);
void MboxFlushReceive(u32 mboxIfBaseAddr);
void MboxFlushWrite(u32 mboxIfBaseAddr);
void MboxReadBlocking(u32 mboxIfBaseAddr, u32* destDataPtr, u32 dataLen);
void MboxWriteBlocking(u32 mboxIfBaseAddr, u32* srcDataPtr, u32 dataLen);

// Mutex functions
void MutexLock(u32 mutexBaseAddr, u32 mutexNumber, u32 cpuId);
int MutexUnlock(u32 mutexBaseAddr, u32 mutexNumber, u32 cpuId);

// Serial communication functions
u32 UartGetStatus(u32 uartBaseAddr);
void UartTransmitBlocking(u32 uartBaseAddr, u8 const* srcDataPtr, u32 dataLen);
u16 UartReceiveBlocking(u32 uartBaseAddr, u8* destDataPtr, u32 dataLen);

// Timer functions
void TimerSetLoadReg(u32 timerBaseAddr, u32 timerNumber, u32 loadValue);
void TimerReset(u32 timerBaseAddr, u32 timerNumber);
void TimerStart(u32 timerBaseAddr, u32 timerNumber);
void TimerStop(u32 timerBaseAddr, u32 timerNumber);
u32 TimerGetStatus(u32 timerBaseAddr, u32 timerNumber);
u32 TimerGetCounter(u32 timerBaseAddr, u32 timerNumber);

// String functions
int mystrcmp(u8 const* s, u8 const* t);
int mystrlen(u8 const* s);

// PRNG
u32 xorshift32(u32 x);

// Interrupts
void EnableInterrupt(u32 intcBaseAddr, u32 interruptVector);
void DisableInterrupt(u32 intcBaseAddr, u32 interruptVector);
void AcknowledgeInterrupt(u32 intcBaseAddr, u32 interruptVector);
u32 GetPrioIntr(u32 intcBaseAddr);
void SendSoftwareInterrupt(u32 destIntcBaseAddr, u32 interruptVector);

// GPIO / LEDs
void InitLeds(void);
void SetLeds(u32 newLedVal);
void SetLed(u32 ledNumber, u32 newLedVal);
void Init7Seg(void);
u32 HexToCat(u32 valToTranslate);
void DisplayHex7Seg(u32 numToDisplay);

// Should be called in response to a timer interrupt at a frequency from 1kHz to 60Hz (62.5Hz -> 16ms period)
void Write7SegToGPIO(void);

extern u32 currentlyShownDigits[];

#endif
