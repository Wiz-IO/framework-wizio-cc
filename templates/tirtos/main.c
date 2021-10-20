/* 
    TIRTOS TEMPLATE: Blink 2021 Georgi Angelov 
            https://github.com/Wiz-IO/wizio-cc
*/

#include <string.h>
#include <stdio.h>
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include "ti_drivers_config.h"

UART_Handle uartHandle;

void blinkThread(UArg arg0, UArg arg1)
{
    while (1)
    {
        GPIO_write(LED_GREEN, 1);
        Task_sleep(10000);
        GPIO_write(LED_GREEN, 0);
        Task_sleep(10000);
    }
}

void mainThread(UArg arg0, UArg arg1)
{
    UART_init();
    uartHandle = UART_open(CONFIG_UART_0, NULL);
    UART_write(uartHandle, "\n[APP] Hello World\n", 19);
    while (1)
    {
        UART_write(uartHandle, "LOOP ", 5);
        GPIO_write(LED_RED, 0);
        Task_sleep(100000);
        GPIO_write(LED_RED, 1);
        Task_sleep(100000);
    }
}

int main(void)
{
    Power_init();
    PIN_init(BoardGpioInitTable);
    GPIO_init();
    GPIO_setConfig(CONFIG_GPIO_LED_GREEN, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_LED_RED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    Task_Params taskParams;
    Task_Params_init(&taskParams);
    taskParams.stackSize = 512;
    taskParams.priority = 1;
    Task_create(mainThread, &taskParams, Error_IGNORE);
    Task_create(blinkThread, &taskParams, Error_IGNORE);
    BIOS_start();
    return -1;
}