#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#ifdef __cplusplus
extern "C"
{
#endif

#define LED 7

#include <stdint.h>

#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_ints.h>

#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26X2.h>

#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>
    extern const PIN_Config BoardGpioInitTable[];
#define CONFIG_PIN_0 0x00000006
#define CONFIG_PIN_1 0x00000007

#define CONFIG_PIN_2 0x00000002
#define CONFIG_PIN_3 0x00000003

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOCC26XX.h>
#define CONFIG_GPIO_LED_RED 0
#define CONFIG_GPIO_LED_GREEN 1

#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTCC26XX.h>

#define CONFIG_UART_0 0

#ifdef __cplusplus
}
#endif
#endif // ti_drivers_config_h