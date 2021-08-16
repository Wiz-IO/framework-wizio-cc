// NOT READY
// NOT TESTED
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

#ifndef __SPI_CLASS_H__
#define __SPI_CLASS_H__

#ifdef __cplusplus

#include "interface.h"
#include "constants.h"
#include "Stream.h"
#include "variant.h"
#include "RingBuffer.h"
#include <driverlib/ssi.h>

#define DEBUG_SPI
//::printf

typedef enum
{
    SPI_MODE0 = SSI_FRF_MOTO_MODE_0, // CPOL : 0  | CPHA : 0
    SPI_MODE1 = SSI_FRF_MOTO_MODE_1, // CPOL : 0  | CPHA : 1
    SPI_MODE2 = SSI_FRF_MOTO_MODE_2, // CPOL : 1  | CPHA : 0
    SPI_MODE3 = SSI_FRF_MOTO_MODE_3  // CPOL : 1  | CPHA : 1
} SPIDataMode;

class SPISettings
{
public:
    SPISettings(uint32_t clockFrequency, uint8_t bitOrder, uint8_t dataMode)
    {
        clock = clockFrequency;
        order = bitOrder;
        mode = dataMode;
    }

    SPISettings()
    {
        clock = 1000; // kHz
        order = MSBFIRST;
        mode = SPI_MODE0;
    }

private:
    uint32_t clock;
    uint8_t order;
    uint8_t mode;
    friend class SPIClass;
};

class SPIClass
{
private:
    int _sck, _miso, _mosi, _cs;
    int _bit_order; // MSB
    int _data_bits; // 4..16
    int _mode;
    uint32_t _brg_hz;
    bool change;
    uint32_t base;
    //uint32_t domain;
    uint32_t periph;

public:
    SPIClass(int id)
    {
        if (0 == id)
        {
            _miso = 9;
            _mosi = 10;
            _cs = 11;
            _sck = 12;
            //domain = PRCM_DOMAIN_SERIAL;
            periph = PRCM_PERIPH_SSI0;
            base = SSI0_BASE;
        }
        else
        {
            _miso = 33;
            _mosi = 34;
            _cs = 35;
            _sck = 36;
            //domain = PRCM_DOMAIN_PERIPH;
            periph = PRCM_PERIPH_SSI1;
            base = SSI1_BASE;
        }
        _bit_order = MSBFIRST;
        _data_bits = 8;
        _mode = SPI_MODE0;
        _brg_hz = 1000000;
        change = true;
    }

    ~SPIClass() { end(); }

    void end()
    {
        //powerOff(0, periph);
        soc_power_off_periphery(periph, 1, 0, 0);
    }

    void begin()
    {
        //powerOn(domain, periph, false, false);
        soc_power_on_periphery(periph, 1, 0, 0);
        IOCPinTypeSsiMaster(base, _miso, _mosi, _cs, _sck);
        beginTransaction(SPISettings());
    }

    void beginTransaction(SPISettings settings)
    {
        setFrequency(settings.clock);
        setDataMode(settings.mode);
        setBitOrder(settings.order);
        if (change)
        {
            /* Disable SSI before making configuration changes */
            SSIDisable(base);
            /* Configure SSI */
            SSIConfigSetExpClk(base, SysCtrlClockGet(), _mode, SSI_MODE_MASTER, _brg_hz, _data_bits);
            /* Re-enable SSI after making configuration changes */
            SSIEnable(base);
            change = false;
        }
    }

    uint8_t transfer(uint8_t data)
    {
        uint32_t d = data;
        if (_bit_order == LSBFIRST)
            d = __REV(__RBIT(d));
        SSIDataPut(base, d);
        SSIDataGet(base, &d);
        if (_bit_order == LSBFIRST)
            return __REV(__RBIT(d));
        return d;
    }

    uint16_t transfer16(uint16_t data) // 2 x 8
    {
        union
        {
            uint16_t val;
            struct
            {
                uint8_t lsb;
                uint8_t msb;
            };
        } t;
        t.val = data;
        if (_bit_order == LSBFIRST)
        {
            t.lsb = transfer(t.lsb);
            t.msb = transfer(t.msb);
        }
        else
        {
            t.msb = transfer(t.msb);
            t.lsb = transfer(t.lsb);
        }
        return t.val;
    }

    int transfer(void *buffer, size_t count)
    {
        if (buffer && count)
        {
            uint8_t *buf = (uint8_t *)buffer;
            if (_bit_order == MSBFIRST)
            {
                for (int i = 0; i < count; i++, buf++)
                {
                    *buf = transfer(*buf);
                }
            }
            else
            {
                buf += count - 1;
                for (int i = 0; i < count; i++, buf--)
                {
                    *buf = transfer(*buf);
                }
            }
        }
        return count;
    }

    int transfer(void *tx_buffer, void *rx_buffer, size_t count)
    {
        uint8_t *tx = (uint8_t *)tx_buffer;
        uint8_t *rx = (uint8_t *)rx_buffer;
        if (count)
        {
            int i = 0;
            if (_bit_order == MSBFIRST)
            {
                if (NULL == rx)
                {
                    for (; i < count; i++, tx++)
                        transfer(*tx);
                }
                else if (NULL == tx)
                {
                    for (; i < count; i++, rx++)
                        *rx = transfer(0xFF);
                }
                else
                {
                    for (; i < count; i++, rx++, tx++)
                        *rx = transfer(*tx);
                }
            }
            else
            {
                if (NULL == rx)
                {
                    tx += count - 1;
                    for (; i < count; i++, tx--)
                        transfer(*tx);
                }
                else if (NULL == tx)
                {
                    rx += count - 1;
                    for (; i < count; i++, rx--)
                        *rx = transfer(0xFF);
                }
                else
                {
                    tx += count - 1;
                    rx += count - 1;
                    for (; i < count; i++, rx--, tx--)
                        *rx = transfer(*tx);
                }
            }
        }
        return count;
    }

    void setDataMode(uint8_t mode)
    {
        if (_mode != mode)
        {
            _mode = mode;
            change = true;
        }
    }

    void setFrequency(uint32_t Hz)
    {
        if (_brg_hz != Hz)
        {
            _brg_hz = Hz;
            change = true;
        }
    }

    void setBitOrder(uint8_t order)
    {
        if (_bit_order != order)
        {
            _bit_order = order;
            change = true;
        }
    }

    uint32_t getClockDivider() { return 0; }
    void setClockDivider(uint8_t div) {}
    void endTransaction(void) {}
    void usingInterrupt(int interruptNumber) {}
    void notUsingInterrupt(int interruptNumber) {}
    void attachInterrupt(){};
    void detachInterrupt(){};
};

extern SPIClass SPI;

#endif // __cplusplus
#endif //__SPI_CLASS_H__