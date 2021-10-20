/* 
    FREERTOS TEMPLATE: Blink 2021 Georgi Angelov 
            https://github.com/Wiz-IO/wizio-cc
*/

#include <interface.h>
#include <FreeRTOS.h>
#include <task.h>

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

void setup(void)
{
    powerOn(PRCM_DOMAIN_SERIAL, PRCM_PERIPH_UART0, 0, 0);       // power on uart0
    IOCPinTypeUart(UART0_BASE, 2, 3, IOID_UNUSED, IOID_UNUSED); // pin as rx, tx
    UARTConfigSetExpClk(UART0_BASE, SysCtrlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTEnable(UART0_BASE);
    retarget_uart(UART0_BASE); // use stdio printf
    
    printf("[APP] Hello World\n");

    powerOn(PRCM_DOMAIN_PERIPH, PRCM_PERIPH_GPIO, 0, 0);           // power on gpio
    IOCPortConfigureSet(LED_GREEN, IOC_PORT_GPIO, IOC_STD_OUTPUT); // pin as gpio
    GPIO_setOutputEnableDio(LED_GREEN, GPIO_OUTPUT_ENABLE);        // pin dir output
    powerOn(PRCM_DOMAIN_PERIPH, PRCM_PERIPH_GPIO, 0, 0);           // power on gpio
    IOCPortConfigureSet(LED_RED, IOC_PORT_GPIO, IOC_STD_OUTPUT);   // pin as gpio
    GPIO_setOutputEnableDio(LED_RED, GPIO_OUTPUT_ENABLE);          // pin dir output
}

void loop(void *arg)
{
    while (1)
    {
        GPIO_toggleDio(LED_GREEN);
        vTaskDelay(100);
    }
}

void test(void *arg)
{
    while (1)
    {
        printf("LOOP ");
        GPIO_toggleDio(LED_RED);
        vTaskDelay(5000);
    }
}

int main(void)
{
    setup();
    xTaskCreate(loop, "LOOP", 256, NULL, 2, NULL);
    xTaskCreate(test, "TEST", 256, NULL, 2, NULL);
    vTaskStartScheduler();
    return -1;
}