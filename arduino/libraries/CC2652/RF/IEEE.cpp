#include <stdio.h>
#include <driverlib/rfc.h>
#include <inc/hw_memmap.h>

/**
 * Error interrupt handler.
 */
void RFCCPE1IntHandler(void)
{
    printf("[INT] RFCCPE1\n");
    /* Clear INTERNAL_ERROR interrupt flag */
    HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = 0x7FFFFFFF;
}

/**
 * Command done handler.
 */
void RFCCPE0IntHandler(void)
{
    //printf("[INT] RFCCPE0\n");
    if (HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) & IRQ_LAST_COMMAND_DONE)
    {
        // CLEAR
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = ~IRQ_LAST_COMMAND_DONE;
        printf("[INT] IRQ_LAST_COMMAND_DONE\n");
    }

    if (HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) & IRQ_LAST_FG_COMMAND_DONE)
    {
        // CLEAR
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = ~IRQ_LAST_FG_COMMAND_DONE;
        printf("[INT] IRQ_LAST_FG_COMMAND_DONE\n");
    }
}