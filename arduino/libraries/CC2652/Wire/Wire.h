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

#ifndef __WIRE_H__
#define __WIRE_H__
#ifdef __cplusplus

#include "interface.h"
#include "Stream.h"
#include "variant.h"
#include "RingBuffer.h"
#include "driverlib/i2c.h"

#define WIRE_PRINT Serial.printf

class TwoWire : public Stream
{
private:
    bool _fast;           // have only two speed 100k or 400k
    uint8_t _address;     // is a 7-bit slave address
    int _sda, _scl;       // 13 & 14
    uint32_t _timeout_ms; // 100 msec default

    bool transmissionBegun;
    RingBuffer rx, tx;

public:
    int command(uint32_t cmd, bool only_control = false);

    TwoWire(uint32_t speed_Hz = 100000 /* or 400000 */)
    {
        _fast = speed_Hz > 100000;
        _timeout_ms = 100;
        _address = 0x5A;
        transmissionBegun = false;
    }

    ~TwoWire() { end(); }

    void end()
    {
        I2CMasterDisable(I2C0_BASE);
        //powerOff(0, PRCM_PERIPH_I2C0);
        soc_power_off_periphery(PRCM_PERIPH_I2C0, 1, 0, 0);
    }

    void begin()
    {
        //powerOn(PRCM_DOMAIN_SERIAL, PRCM_PERIPH_I2C0, false, false);
        soc_power_on_periphery(PRCM_PERIPH_I2C0, 1, 0, 0);
        IOCPinTypeI2c(I2C0_BASE, 13, 14);
        I2CMasterIntClear(I2C0_BASE);
        I2CMasterEnable(I2C0_BASE);
        I2CMasterInitExpClk(I2C0_BASE, SysCtrlClockGet(), _fast);
    }

    void setClock(uint32_t speed_Hz)
    {
        _fast = speed_Hz > 100000;
        I2CMasterInitExpClk(I2C0_BASE, SysCtrlClockGet(), _fast);
    }

    void setTimeOut(uint32_t timeout_millis) { _timeout_ms = timeout_millis; }

    void beginTransmission(uint8_t);
    uint8_t endTransmission(bool stopBit);
    uint8_t endTransmission(void);

    uint8_t requestFrom(uint8_t address, size_t size, bool stopBit);
    uint8_t requestFrom(uint8_t address, size_t size);

    size_t write(uint8_t data);
    size_t write(const uint8_t *data, size_t size);

    virtual int available(void) { return rx.available(); }
    virtual int read(void) { return rx.read_char(); }
    virtual int peek(void) { return rx.peek(); }
    virtual void flush(void) {}

    using Print::write;

    void onService(void){};
    void onReceive(void (*)(int)){};
    void onRequest(void (*)(void)){};
};

extern TwoWire Wire;

#endif // cpp
#endif // h