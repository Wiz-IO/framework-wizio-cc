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

#include <Arduino.h>
#include "Wire.h"

int TwoWire::command(uint32_t cmd, bool only_control)
{
    I2CMasterControl(I2C0_BASE, cmd);
    if (only_control)
    {
        I2CMasterIntClear(I2C0_BASE); // ???
        return 0;
    }
    uint32_t _startMillis = millis();
    do
    {
        if (I2CMasterIntStatus(I2C0_BASE, true))
        {
            I2CMasterIntClear(I2C0_BASE);
            int res = I2CMasterErr(I2C0_BASE);
            WIRE_PRINT("[I2C] err = %d\n", res);
            return res; // 0 = OK
        }
    } while (millis() - _startMillis < _timeout_ms);
    I2CMasterIntClear(I2C0_BASE); // ???
    WIRE_PRINT("[ERROR] I2C TIMEOUT\n");
    return -1;
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t size, bool stopBit)
{
    if (size == 0 || size > sizeof(rx._aucBuffer)) // LIMIT ? SERIAL_BUFFER_SIZE
        return 0;
    if (!stopBit)
        return 0;
    rx.clear();
    int res = -1;
    I2CMasterSlaveAddrSet(I2C0_BASE, address, true);
    if (1 == size)
    {
        if (command(I2C_MASTER_CMD_SINGLE_RECEIVE))
            goto ERROR;
        rx._aucBuffer[0] = I2CMasterDataGet(I2C0_BASE);
        return 1;
    }
    else
    {
        if (command(I2C_MASTER_CMD_BURST_RECEIVE_START))
            goto ERROR;

        rx._aucBuffer[0] = I2CMasterDataGet(I2C0_BASE);
        for (int i = 1; i < size - 1; i++)
        {
            if (command(I2C_MASTER_CMD_BURST_RECEIVE_CONT))
                goto ERROR;
            if (rx.availableForStore())
            {
                rx.store_char(I2CMasterDataGet(I2C0_BASE));
            }
            else
            {
                goto ERROR;
            }
        }
        if (command(I2C_MASTER_CMD_BURST_RECEIVE_FINISH))
            goto ERROR;
        if (rx.availableForStore())
        {
            rx.store_char(I2CMasterDataGet(I2C0_BASE));
        }
        else
        {
            goto ERROR;
        }
    }
    return rx.available();
ERROR:
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);
    return 0;
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t size)
{
    return requestFrom(address, size, true);
}

void TwoWire::beginTransmission(uint8_t address)
{
    _address = address;
    tx.clear();
    transmissionBegun = true;
}

uint8_t TwoWire::endTransmission(bool stopBit)
{
    if (!stopBit)
        return 1;
    int res = 0;
    transmissionBegun = false;
    int size = tx.available();
    if (0 == size)
        return 4;
    I2CMasterSlaveAddrSet(I2C0_BASE, _address, false);
    if (1 == size)
    {
        I2CMasterDataPut(I2C0_BASE, tx._aucBuffer[0]);
        if (command(I2C_MASTER_CMD_SINGLE_SEND))
            goto ERROR;
    }
    else
    {
        I2CMasterDataPut(I2C0_BASE, tx._aucBuffer[0]);
        for (int i = 1; i < size - 1; i++)
        {
            I2CMasterDataPut(I2C0_BASE, tx._aucBuffer[1]);
            if (command(I2C_MASTER_CMD_BURST_SEND_CONT))
                goto ERROR;
        }
        I2CMasterDataPut(I2C0_BASE, tx._aucBuffer[size - 1]);
        if (command(I2C_MASTER_CMD_BURST_SEND_FINISH))
            goto ERROR;
    }
    return 0;
// 0:success
// 1:data too long to fit in transmit buffer
// 2:received NACK on transmit of address
// 3:received NACK on transmit of data
// 4:other error
ERROR:
    command(I2C_MASTER_CMD_BURST_SEND_ERROR_STOP, true);
    return 4;
}

uint8_t TwoWire::endTransmission()
{
    return endTransmission(true);
}

size_t TwoWire::write(uint8_t ucData)
{
    if (!transmissionBegun || tx.isFull())
        return 0;
    tx.store_char(ucData);
    return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (!write(data[i]))
            return i;
    }
    return size;
}

TwoWire Wire;