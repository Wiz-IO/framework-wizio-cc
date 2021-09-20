#include "hard_trap.h"
#include <stdio.h>

#include <driverlib/uart.h>
volatile uint32_t gUartBase; // UART0_BASE

static void printErrorMsg(const char *errMsg);
static void printUsageErrorMsg(uint32_t CFSRValue);
static void printBusFaultErrorMsg(uint32_t CFSRValue);
static void printMemoryManagementErrorMsg(uint32_t CFSRValue);
static void stackDump(uint32_t stack[]);

void Hard_Fault_Handler(uint32_t stack[])
{
    static char msg[80];
    //if((CoreDebug->DHCSR & 0x01) != 0) {
    printErrorMsg("\n\n[ERROR] Hard Fault Handler\n");
    sprintf(msg, "SCB->HFSR = 0x%08x\n", (int)SCB->HFSR);
    printErrorMsg(msg);
    if ((SCB->HFSR & (1 << 30)) != 0)
    {
        printErrorMsg("Forced Hard Fault\n");
        sprintf(msg, "SCB->CFSR = 0x%08x\n", (int)SCB->CFSR);
        printErrorMsg(msg);
        if ((SCB->CFSR & 0xFFFF0000) != 0)
        {
            printUsageErrorMsg(SCB->CFSR);
        }
        if ((SCB->CFSR & 0xFF00) != 0)
        {
            printBusFaultErrorMsg(SCB->CFSR);
        }
        if ((SCB->CFSR & 0xFF) != 0)
        {
            printMemoryManagementErrorMsg(SCB->CFSR);
        }
    }
    stackDump(stack);

    //asm volatile("BKPT #01");
    //}
    while (1)
        ;
}

void FaultISR(void)
{
    __asm("TST lr, #4          \n"
          "ITE EQ              \n"
          "MRSEQ r0, MSP       \n"
          "MRSNE r0, PSP       \n"
          "B Hard_Fault_Handler\n");
}

static void printErrorMsg(const char *errMsg)
{
    while (*errMsg != '\0')
    {
        UARTCharPut(gUartBase, *errMsg++); // UART0_BASE 
    }
}

static void printUsageErrorMsg(uint32_t CFSRValue)
{
    printErrorMsg("Usage fault: \n");
    CFSRValue >>= 16; // right shift to lsb
    if ((CFSRValue & (1 << 9)) != 0)
    {
        printErrorMsg("Divide by zero\n");
    }
}

static void printBusFaultErrorMsg(uint32_t CFSRValue)
{
    printErrorMsg("Bus fault: \n");
    CFSRValue = ((CFSRValue & 0x0000FF00) >> 8); // mask and right shift to lsb
}

static void printMemoryManagementErrorMsg(uint32_t CFSRValue)
{
    printErrorMsg("Memory Management fault: ");
    CFSRValue &= 0x000000FF; // mask just mem faults
}

enum{ r0, r1, r2, r3,  r12,  lr, pc, psr };

static void stackDump(uint32_t stack[])
{
    static char msg[80];
    sprintf(msg, "   pc  = 0x%08X\n", (int)stack[pc]);
    printErrorMsg(msg);
    sprintf(msg, "   lr  = 0x%08X\n", (int)stack[lr]);
    printErrorMsg(msg);
    sprintf(msg, "   psr = 0x%08X\n", (int)stack[psr]);
    printErrorMsg(msg);
    sprintf(msg, "   r0  = 0x%08X\n", (int)stack[r0]);
    printErrorMsg(msg);
    sprintf(msg, "   r1  = 0x%08X\n", (int)stack[r1]);
    printErrorMsg(msg);
    sprintf(msg, "   r2  = 0x%08X\n", (int)stack[r2]);
    printErrorMsg(msg);
    sprintf(msg, "   r3  = 0x%08X\n", (int)stack[r3]);
    printErrorMsg(msg);
    sprintf(msg, "   r12 = 0x%08X\n", (int)stack[r12]);
    printErrorMsg(msg);
}

// hard_trap_init(Serial.getBase()); or UARTx_BASE
void hard_trap_init(uint32_t UartBase) // UART0_BASE
{
    gUartBase = UartBase;
    SCB->CCR |= 0x10;
}

//hard_trap_test((cb_hf_t)1234567);
void hard_trap_test(cb_hf_t fake_call) { fake_call(); }