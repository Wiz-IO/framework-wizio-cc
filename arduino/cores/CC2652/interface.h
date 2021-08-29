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

#ifndef INTERFACE_H_
#define INTERFACE_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <limits.h>
#include <reent.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include <driverlib/cpu.h>
#include <driverlib/prcm.h>
#include <driverlib/ioc.h>
#include <driverlib/aon_rtc.h>
#include <driverlib/trng.h>
#include <driverlib/vims.h>
#include <driverlib/uart.h>

    typedef void (*voidFuncPtr)(void);
    typedef void (*voidFuncPtrParam)(void *);

    __attribute__((always_inline)) __STATIC_INLINE void __enable_irq(void)
    {
        __asm volatile("cpsie i"
                       :
                       :
                       : "memory");
    }

    __attribute__((always_inline)) __STATIC_INLINE void __disable_irq(void)
    {
        __asm volatile("cpsid i"
                       :
                       :
                       : "memory");
    }

    __attribute__((always_inline)) __STATIC_INLINE uint32_t __get_PRIMASK(void)
    {
        uint32_t result;
        __asm volatile("MRS %0, primask"
                       : "=r"(result));
        return (result);
    }

    __attribute__((always_inline)) __STATIC_INLINE void __set_PRIMASK(uint32_t priMask)
    {
        __asm volatile("MSR primask, %0"
                       :
                       : "r"(priMask)
                       : "memory");
    }

    __attribute__((always_inline)) __STATIC_INLINE uint32_t enter_critical(void)
    {
        uint32_t primask = __get_PRIMASK();
        __disable_irq();
        return primask;
    }

    __attribute__((always_inline)) __STATIC_INLINE void exit_critical(uint32_t primask)
    {
        __set_PRIMASK(primask);
        __enable_irq();
    }

#define ENTER_CRITICAL(PRIM) PRIM = enter_critical()
#define EXIT_CRITICAL(PRIM) exit_critical(PRIM)

    void interrupts(void);
    void noInterrupts(void);

#ifndef SERIAL_BUFFER_SIZE
#define SERIAL_BUFFER_SIZE 256
#endif

#define F_CPU SysCtrlClockGet()

#define clockCyclesPerMicrosecond() (F_CPU / 1000000L)
#define clockCyclesToMicroseconds(a) (((a)*1000L) / (F_CPU / 1000L))
#define microsecondsToClockCycles(a) ((a)*clockCyclesPerMicrosecond())
#define getSysTick() systick_hw->cvr

    extern char *utoa(unsigned int value, char *buffer, int radix);
    static inline char *ltoa(long value, char *result, int base) { return utoa(value, result, base); }
    static inline char *ultoa(unsigned long value, char *result, int base) { return utoa(value, result, base); }

#define digitalPinToPort(p)
#define digitalPinToBitMask(p)
#define digitalPinToClkid(p)
#define digitalPinSPIAvailiable(p)
#define digitalPinToSPIDevice(p)
#define digitalPinToSPIClockId(p)

    static inline void yield(void)
    {
    }

    extern volatile uint32_t msTicks;

    void delay(unsigned int ms);

    static inline unsigned int millis(void)
    {
        return msTicks;
    }

    unsigned int micros(void); // TODO

    static inline void delayMicroseconds(unsigned int us) // TODO ?
    {
        // At 48 MHz RCOSC and VIMS.CONTROL.PREFETCH = 0, there is 5 cycles
        CPUdelay(((uint32_t)(((us)*48.0) / 5.0)) - 1);
    }

    static inline unsigned int seconds(void) // helper
    {
        return AONRTCSecGet();
    }

    static inline void digitalToggle(uint8_t pin)
    { // protect?
        GPIO_toggleDio(pin);
    }

    static inline void digitalWrite(uint8_t pin, uint8_t val)
    { // protect?
        GPIO_writeDio(pin, val);
    }

    static inline int digitalRead(uint8_t pin)
    { // protect?
        return GPIO_readDio(pin);
    }

    void blink(int pin, uint32_t timeout); // helper, ONLY one led

    // STDIO
    typedef struct
    {
        void *ctx;
        uint32_t uart_base;
        int (*write_r)(struct _reent *r, _PTR p, const char *buf, int len);
        int (*read_r)(struct _reent *r, _PTR p, char *buf, int len);
    } drv_t;
    extern drv_t stdio_drv;
    void stdio_retarget(drv_t *p);

    // POWER
    //void powerOn(uint32_t domain, uint32_t periph, bool sleep, bool deep_sleep);
    //void powerOff(uint32_t domain, uint32_t periph);

    // only domain (+/-)
    bool soc_power_on_domain(uint32_t domain);
    bool soc_power_off_domain(uint32_t domain);

    // periphery and domain (+/-)
    bool soc_power_on_periphery(uint32_t periphery, bool normal, bool sleep, bool deep);
    bool soc_power_off_periphery(uint32_t periphery, bool normal, bool sleep, bool deep);

    // for SPI
    __attribute__((always_inline)) static inline uint32_t __RBIT(uint32_t value) // Bits in word
    {
        uint32_t result;
        __asm volatile("rbit %0, %1"
                       : "=r"(result)
                       : "r"(value));
        return (result);
    }

    __attribute__((always_inline)) static inline uint32_t __REV(uint32_t value) // Bytes in word
    {
        uint32_t result;
        __asm volatile("rev %0, %1"
                       : "=r"(result)
                       : "r"(value));
        return (result);
    }

    __attribute__((always_inline)) static inline uint32_t __REV16(uint32_t value) // Bytes in both halfwords
    {
        uint32_t result;
        __asm volatile("rev16 %0, %1"
                       : "=r"(result)
                       : "r"(value));
        return (result);
    }

    // for debug
    void dmp_buf(const char *text, const unsigned char *buf, unsigned int len);
#define DUMP(T, B, L) dmp_buf(T, (const unsigned char *)B, L) /* use printf() */

    void dmp_line(const unsigned char *buf, unsigned int len);
#define DUMP_LINE(B, L) dmp_line((const unsigned char *)B, L) /* use printf() */

#define PRINTF printf
#define PRINT_FUNC() PRINTF("[] %s\n", __func__)

#ifdef __cplusplus
}

// CPP functions

#endif
#endif /* INTERFACE_H_ */
