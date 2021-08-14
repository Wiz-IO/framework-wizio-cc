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

#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus

#include <HardwareSerial.h>
#include <RingBuffer.h>

#include <inc/hw_memmap.h>
#include <inc/hw_uart.h>
#include <driverlib/ioc.h>
#include <driverlib/prcm.h>
#include <driverlib/sys_ctrl.h>
#include <driverlib/uart.h>

class Uart;

#define SERIALS 2

typedef struct
{
    Uart *THIS; // class instance for isr
    uint32_t base;
    uint32_t domain;
    uint32_t peripheral;
    uint32_t idRx, idTx, idCts, idRts;

    void (*isr_rx)(void);

} UART_CONTEXT, *pUART_CONTEXT;

extern UART_CONTEXT UartContext[SERIALS];

class Uart : public HardwareSerial
{
private:
    pUART_CONTEXT ctx;
    RingBuffer rx_ring; // default SERIAL_BUFFER_SIZE = 256
    bool enabled;       // need ?
    drv_t stdio;

public:
    Uart(uint8_t id)
    {
        if (id >= SERIALS)
            abort(); // WRONG UART
        ctx = &UartContext[id];
        ctx->THIS = this;
        enabled = false;
        stdio.write_r = u_write_r;
        stdio.read_r = u_read_r;
        stdio.uart_base = ctx->base;
        stdio.ctx = this;
    }

    ~Uart() { end(); }

    void begin(unsigned long baud, uint8_t data_bits, uint8_t stop_bits, uint8_t parity, bool retarget = false)
    {
        if (enabled)
            end();
#if 1 /* 0 for printf debug  soc_powers */
        soc_power_on_periphery(ctx->peripheral, 1, 0, 0);
#else
        PRCMPowerDomainOn(ctx->domain);
        while (PRCMPowerDomainsAllOn(ctx->domain) != PRCM_DOMAIN_POWER_ON)
            ;
        PRCMPeripheralRunEnable(ctx->peripheral);
        PRCMPeripheralSleepEnable(ctx->peripheral);
        PRCMPeripheralDeepSleepEnable(ctx->peripheral);
        PRCMLoadSet();
        while (!PRCMLoadGet())
            ;
#endif
        IOCPinTypeUart(ctx->base, ctx->idRx, ctx->idTx, ctx->idCts, ctx->idRts);

        // TODO
        UARTConfigSetExpClk(ctx->base, SysCtrlClockGet(), baud, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

        UARTIntEnable(ctx->base, UART_INT_RX | UART_INT_RT);
        UARTIntRegister(ctx->base, ctx->isr_rx);

        UARTEnable(ctx->base);

        if (retarget) // printf
        {
            stdio_retarget(&stdio);
        }

        enabled = true;
    }

    void begin(unsigned long baud, bool retarget = false)
    {
        begin(baud, 8, 1, 0, retarget);
    }

    void begin(unsigned long baud, int config, bool retarget = false)
    {
        // TODO config
    }

    void end(void)
    {
        if (false == enabled)
            end();
        UARTDisable(ctx->base);
        UARTIntUnregister(ctx->base);
        UARTIntDisable(ctx->base, UART_INT_RX | UART_INT_RT);
#if 1
        soc_power_off_periphery(ctx->peripheral, 1, 0, 0);
#else
        IOCPortConfigureSet(ctx->idRx, IOC_PORT_GPIO, IOC_STD_INPUT);
        IOCPortConfigureSet(ctx->idTx, IOC_PORT_GPIO, IOC_STD_INPUT);
        PRCMPeripheralRunDisable(ctx->peripheral);
        PRCMPeripheralSleepDisable(ctx->peripheral);
        PRCMPeripheralDeepSleepDisable(ctx->peripheral);
        PRCMLoadSet();
        PRCMPowerDomainOff(ctx->domain);
#endif
        rx_ring.clear();
    }

    inline size_t write(uint8_t c)
    {
        UARTCharPut(ctx->base, c);
        return 1;
    }

    size_t write(const uint8_t *buf, size_t size)
    {
        size_t c = size;
        while (size--)
            UARTCharPut(ctx->base, *buf++);
        return c;
    }

    int read()
    {
        if (!rx_ring.available())
            return -1;
        UARTIntDisable(ctx->base, UART_INT_RX | UART_INT_RT);
        uint8_t b = rx_ring.read_char();
        UARTIntEnable(ctx->base, UART_INT_RX | UART_INT_RT);
        return b;
    }

    int read(uint8_t *buf, size_t size)
    {
        int cnt = 0;
        while (available() > 0 && size)
        {
            *buf++ = read();
            size--;
            cnt++;
        }
        return cnt ? cnt : -1;
    }

    inline int read(char *buf, size_t size) { return read((uint8_t *)buf, size); }

    int available(void) { return rx_ring.available(); }
    int peek(void) { return rx_ring.peek(); }
    void flush(void) {}
    operator bool() { return true; }
    using Print::write;

    void isr_save() // PRIVATE HANDLER
    {
        while (UARTCharsAvail(ctx->base))
        {
            if (rx_ring.availableForStore())
            {
                char c = UARTCharGet(ctx->base);
                UARTIntDisable(ctx->base, UART_INT_RX | UART_INT_RT);
                rx_ring.store_char(c);
                UARTIntEnable(ctx->base, UART_INT_RX | UART_INT_RT);
            }
            else
                break;
        }
    }

    // STDIO
    static int u_write_r(struct _reent *r, _PTR p, const char *buf, int len)
    {
        drv_t *drv = (drv_t *)p;
        size_t c = len;
        while (len--)
            UARTCharPut(drv->uart_base, *buf++);
        return c;
    }

    static int u_read_r(struct _reent *r, _PTR p, char *buf, int len)
    {
        return -1;
    }
};

extern Uart Serial;
extern Uart Serial1;

#endif
#endif // _UART_H_