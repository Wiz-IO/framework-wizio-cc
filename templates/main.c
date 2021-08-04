/* TEMPLATE: blink 2021 Georgi Angelov */

#include <string.h>
#include <stdio.h>
#include <driverlib/sys_ctrl.h>
#include <driverlib/prcm.h>
#include <driverlib/ioc.h>
#include <driverlib/uart.h>

#define LED 7

void powerOn(uint32_t domain, uint32_t periph, bool sleep, bool deep_sleep)
{
    if (domain)
    {
        PRCMPowerDomainOn(domain);
        while (PRCMPowerDomainsAllOn(domain) != PRCM_DOMAIN_POWER_ON)
            ;
    }
    if (periph)
    {
        PRCMPeripheralRunEnable(periph);
        if (sleep)
            PRCMPeripheralSleepEnable(periph);
        if (deep_sleep)
            PRCMPeripheralDeepSleepEnable(periph);
        PRCMLoadSet();
        while (!PRCMLoadGet())
            ;
    }
}

void print(const char *str)
{
    while (*str)
        UARTCharPut(UART0_BASE, *str++);
}

static char DBG_BUFFER[256];
#define PRINTF(FORMAT, ...)                                              \
    {                                                                    \
        snprintf(DBG_BUFFER, sizeof(DBG_BUFFER), FORMAT, ##__VA_ARGS__); \
        print(DBG_BUFFER);                                               \
    }

int main(void)
{
    // SETUP
    
    powerOn(PRCM_DOMAIN_SERIAL, PRCM_PERIPH_UART0, 0, 0);       // power on uart0
    IOCPinTypeUart(UART0_BASE, 2, 3, IOID_UNUSED, IOID_UNUSED); // pin as rx, tx
    UARTConfigSetExpClk(UART0_BASE, SysCtrlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTEnable(UART0_BASE);
    PRINTF("Hello World\n");

    powerOn(PRCM_DOMAIN_PERIPH, PRCM_PERIPH_GPIO, 0, 0);     // power on gpio
    IOCPortConfigureSet(LED, IOC_PORT_GPIO, IOC_STD_OUTPUT); // pin as gpio
    GPIO_setOutputEnableDio(LED, GPIO_OUTPUT_ENABLE);        // pin dir output

    // LOOP
    while (1)
    {
        GPIO_writeDio(LED, 0);
        CPUdelay(1000000);
        GPIO_writeDio(LED, 1);
        CPUdelay(1000000);
        PRINTF("# ");
    }
    return -1;
}