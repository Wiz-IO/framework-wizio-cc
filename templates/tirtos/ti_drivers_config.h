#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
    void retarget_uart(uint32_t base);

#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_ints.h>

#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26X2.h>

#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>
    extern const PIN_Config BoardGpioInitTable[];
#define CONFIG_PIN_0 0x00000006 /* dio led red */
#define CONFIG_PIN_1 0x00000007 /* dio led green */
#define CONFIG_PIN_2 0x00000002 /* dio uart rx */
#define CONFIG_PIN_3 0x00000003 /* dio uart tx */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOCC26XX.h>
#define CONFIG_GPIO_LED_RED 0
#define LED_RED CONFIG_GPIO_LED_RED

#define CONFIG_GPIO_LED_GREEN 1
#define LED_GREEN CONFIG_GPIO_LED_GREEN

#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTCC26XX.h>

#define CONFIG_UART_0 0

#ifdef __cplusplus
}
#endif
#endif // ti_drivers_config_h