/* 
    BAREMETAL TEMPLATE: Blink 2021 Georgi Angelov 
            https://github.com/Wiz-IO/wizio-cc
*/

#include <interface.h>

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

int main(void)
{
    powerOn(PRCM_DOMAIN_SERIAL, PRCM_PERIPH_UART0, 0, 0);       // power on uart0
    IOCPinTypeUart(UART0_BASE, 2, 3, IOID_UNUSED, IOID_UNUSED); // pin as rx, tx
    UARTConfigSetExpClk(UART0_BASE, SysCtrlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTEnable(UART0_BASE);
    retarget_uart(UART0_BASE); // printf
    printf("[APP] Hello World\n");

    powerOn(PRCM_DOMAIN_PERIPH, PRCM_PERIPH_GPIO, 0, 0);           // power on gpio
    IOCPortConfigureSet(LED_GREEN, IOC_PORT_GPIO, IOC_STD_OUTPUT); // pin as gpio
    GPIO_setOutputEnableDio(LED_GREEN, GPIO_OUTPUT_ENABLE);        // pin dir output

    while (1)
    {
        printf("LOOP ");
        GPIO_writeDio(LED_GREEN, 1);
        CPUdelay(1000000);
        GPIO_writeDio(LED_GREEN, 0);
        CPUdelay(10000000);
    }
    return -1;
}