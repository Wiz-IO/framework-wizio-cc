////////////////////////////////////////////////////////////////////////////////////////
//
//      2021 Georgi Angelov
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>

#include <driverlib/prcm.h>
static void gpio_on(void)
{
    static bool on = false;
    if (on)
        return;
#if 1
    soc_power_on_periphery(PRCM_PERIPH_GPIO, 1, 0, 0);
#else
    /* GPIO power up*/
    PRCMPowerDomainOn(PRCM_DOMAIN_PERIPH);
    while (PRCMPowerDomainsAllOn(PRCM_DOMAIN_PERIPH) != PRCM_DOMAIN_POWER_ON)
        ;
    PRCMPeripheralRunEnable(PRCM_PERIPH_GPIO);
    PRCMLoadSet();
    while (!PRCMLoadGet())
        ;
#endif
    on = true;
}

void pinMode(uint8_t pin /*IOID_XX*/, uint8_t mode)
{
    if (pin >= IOID_31) // protect pin array
        return;
#if 1
    soc_power_on_periphery(PRCM_PERIPH_GPIO, 1, 0, 0);
#else
        //gpio_on();
#endif
    if (mode & (OUTPUT | OUTPUT_LO | OUTPUT_HI))
    {
        IOCPortConfigureSet(pin, IOC_PORT_GPIO, IOC_STD_OUTPUT);
        GPIO_setOutputEnableDio(pin, GPIO_OUTPUT_ENABLE);
        GPIO_writeDio(pin, mode & OUTPUT_HI);
    }
    else if (mode & (INPUT | INPUT_PULLUP | INPUT_PULLDOWN))
    {
        IOCPortConfigureSet(pin, IOC_PORT_GPIO, IOC_STD_INPUT);
        if (mode & INPUT_PULLUP)
        {
            // TODO
        }
        else
        {
            // TODO
        }
    }
}

// ONLY one led
void blink(int led, uint32_t timeout)
{
    static uint32_t start = 0;
    if (millis() - start > timeout)
    {
        start = millis();
        digitalToggle(led);
    }
}

////////////////////////////////////////////////////////////////////////////////////////

static void irq_gpio_callback(uint gpio, uint32_t events)
{
    // TODO
}

void attachInterrupt(uint8_t pin, void (*cb)(void), int mode)
{
    // TODO
}

void detachInterrupt(uint8_t pin)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////////////

static uint32_t arduino_lock;

inline void interrupts(void)
{
    exit_critical(arduino_lock);
}

inline void noInterrupts(void)
{
    arduino_lock = enter_critical();
}

////////////////////////////////////////////////////////////////////////////////////////

bool analogSetFrequency(uint8_t pin, uint32_t freq)
{
    // TODO
    return 0;
}

void analogWrite(uint8_t pin, int duty)
{
    // PWM, DAC
    // TODO
}

void analogInit(uint8_t adc_channel)
{
    // PWM, ADC, DAC
    // TODO
}

int analogRead(uint8_t adc_channel)
{
    // ADC
    // TODO
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////

#include <driverlib/systick.h>
#include <driverlib/sys_ctrl.h>

volatile uint32_t msTicks; /* counts 1 msec */

void SysTickIntHandler(void)
{
    msTicks++;
    //GPIO_writeDio(30, msTicks & 1);
}

void SysTickSetup(void)
{
    unsigned long clockval;
    clockval = SysCtrlClockGet(); // 48000000
    /* 1ms period for systick */
    SysTickPeriodSet(clockval / 1000);
    /* Enable SysTick */
    SysTickEnable();
    /* Enable Systick interrupt */
    SysTickIntEnable();
}

unsigned int micros(void)
{
    return 0; // TODO ???
}

void delay(unsigned int ms)
{
    uint32_t curTicks = msTicks;
    while ((msTicks - curTicks) < ms)
    {
    }
}