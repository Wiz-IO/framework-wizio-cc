#include "SerialUart.h"

void int_UART0IntHandler(void)
{
    Serial.isr_save();
}

void int_UART1IntHandler(void)
{
    Serial1.isr_save();
}

Uart Serial(0);
Uart Serial1(1);

UART_CONTEXT UartContext[SERIALS] = {
    {
        NULL, // Serial
        UART0_BASE,
        PRCM_DOMAIN_SERIAL,
        PRCM_PERIPH_UART0,
        IOID_2,
        IOID_3,
        IOID_UNUSED,
        IOID_UNUSED,
        int_UART0IntHandler,
    },
    {
        NULL, // Serial1
        UART1_BASE,
        PRCM_DOMAIN_PERIPH,
        PRCM_PERIPH_UART1,
        IOID_1,
        IOID_0,
        IOID_UNUSED,
        IOID_UNUSED,
        int_UART1IntHandler,
    },
};