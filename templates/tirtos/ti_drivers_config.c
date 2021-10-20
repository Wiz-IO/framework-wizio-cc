#include "ti_drivers_config.h"

/* Power ********************************************************************************/

extern void PowerCC26XX_standbyPolicy(void);
extern bool PowerCC26XX_calibrate(unsigned int);
const PowerCC26X2_Config PowerCC26X2_config = {
    .enablePolicy = true,
    .policyInitFxn = NULL,
    .policyFxn = PowerCC26XX_standbyPolicy,
    .calibrateFxn = PowerCC26XX_calibrate,
    .calibrateRCOSC_LF = true,
    .calibrateRCOSC_HF = true,
    .enableTCXOFxn = NULL};

/* PIN *********************************************************************************/

#define CONFIG_PIN_COUNT 4

const PIN_Config BoardGpioInitTable[CONFIG_PIN_COUNT + 1] = {
    /* LED Red, Parent Signal: CONFIG_GPIO_LED_0 GPIO Pin, (DIO6) */
    CONFIG_PIN_0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED,
    /* LED Red, Parent Signal: CONFIG_GPIO_LED_1 GPIO Pin, (DIO7) */
    CONFIG_PIN_1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED,

    /* UART, Parent Signal: CONFIG_UART_0 RX, (DIO2) */
    CONFIG_PIN_2 | PIN_INPUT_EN | PIN_PULLDOWN | PIN_IRQ_DIS,
    /* UART, Parent Signal: CONFIG_UART_0 TX, (DIO3) */
    CONFIG_PIN_3 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED,

    PIN_TERMINATE,
};

const PINCC26XX_HWAttrs PINCC26XX_hwAttrs = {
    .intPriority = ~0,
    .swiPriority = 0,
};

/* GPIO *********************************************************************************/

#define CONFIG_GPIO_COUNT 2
GPIO_PinConfig gpioPinConfigs[] = {
    /* CONFIG_GPIO_LED_6 : LED Red [0] */
    GPIOCC26XX_DIO_06 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_GPIO_LED_7 : LED Green [1] */
    GPIOCC26XX_DIO_07 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
};
GPIO_CallbackFxn gpioCallbackFunctions[] = {0};
const GPIOCC26XX_Config GPIOCC26XX_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = CONFIG_GPIO_COUNT,
    .numberOfCallbacks = CONFIG_GPIO_COUNT,
    .intPriority = (~0)};

/* UART ********************************************************************************/

#define CONFIG_UART_COUNT 1
const uint_least8_t UART_count = CONFIG_UART_COUNT;
UARTCC26XX_Object uartCC26XXObjects[CONFIG_UART_COUNT];
static unsigned char uartCC26XXRingBuffer0[32];
static const UARTCC26XX_HWAttrsV2 uartCC26XXHWAttrs[CONFIG_UART_COUNT] = {
    {.baseAddr = UART0_BASE,
     .intNum = INT_UART0_COMB,
     .intPriority = (~0),
     .swiPriority = 0,
     .powerMngrId = PowerCC26XX_PERIPH_UART0,
     .ringBufPtr = uartCC26XXRingBuffer0,
     .ringBufSize = sizeof(uartCC26XXRingBuffer0),
     .rxPin = IOID_2,
     .txPin = IOID_3,
     .ctsPin = PIN_UNASSIGNED,
     .rtsPin = PIN_UNASSIGNED,
     .txIntFifoThr = UARTCC26XX_FIFO_THRESHOLD_1_8,
     .rxIntFifoThr = UARTCC26XX_FIFO_THRESHOLD_4_8,
     .errorFxn = NULL},
};

const UART_Config UART_config[CONFIG_UART_COUNT] = {
    {
        /* CONFIG_UART_0 */
        .fxnTablePtr = &UARTCC26XX_fxnTable,
        .object = &uartCC26XXObjects[CONFIG_UART_0],
        .hwAttrs = &uartCC26XXHWAttrs[CONFIG_UART_0],
    },
};

/* OTHER ****************************************************************************/