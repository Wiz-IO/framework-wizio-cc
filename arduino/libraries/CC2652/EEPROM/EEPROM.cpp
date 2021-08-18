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
#include "EEPROM.h"
#include <driverlib/flash.h>

#define EEPROM_PRINTF 
//::printf

extern "C" uint8_t _start_eeprom;
extern "C" uint8_t disableFlashCache(void);
extern "C" void restoreFlashCache(uint8_t mode);

#define EEPROM_BLOCK_SIZE 0x2000

EEPROMClass::EEPROMClass(void)
    : _sector(&_start_eeprom)
{
    while ((int)&_start_eeprom % EEPROM_BLOCK_SIZE) // align protect
    {
    }
}

void EEPROMClass::begin(size_t size)
{
    if ((size <= 0) || (size > EEPROM_BLOCK_SIZE))
    {
        size = EEPROM_BLOCK_SIZE;
    }

    _size = (size + 255) & (~255); // Flash writes limited to 256 byte boundaries

    // In case begin() is called a 2nd+ time, don't reallocate if size is the same
    if (_data && size != _size)
    {
        delete[] _data;
        _data = new uint8_t[size];
    }
    else if (!_data)
    {
        _data = new uint8_t[size];
    }

    memcpy(_data, _sector, _size);

    _dirty = false; // Make sure dirty is cleared in case begin() is called 2nd+ time
}

bool EEPROMClass::end()
{
    bool retval;

    if (!_size)
    {
        return false;
    }

    retval = commit();
    if (_data)
    {
        delete[] _data;
    }
    _data = 0;
    _size = 0;
    _dirty = false;

    return retval;
}

uint8_t EEPROMClass::read(int const address)
{
    if (address < 0 || (size_t)address >= _size)
        return 0;
    if (!_data)
        return 0;
    return _data[address];
}

void EEPROMClass::write(int const address, uint8_t const value)
{
    if (address < 0 || (size_t)address >= _size)
        return;
    if (!_data)
        return;

    // Optimise _dirty. Only flagged if data written is different.
    uint8_t *pData = &_data[address];
    if (*pData != value)
    {
        *pData = value;
        _dirty = true;
    }
}

bool EEPROMClass::commit()
{
    bool res = false;
    if (!_size)
        return res;
    if (!_dirty)
        return res;
    if (!_data)
        return res;

    noInterrupts();
    uint8_t mode = disableFlashCache();

    if (FAPI_STATUS_SUCCESS == FlashSectorErase((intptr_t)_sector))
    {
        EEPROM_PRINTF("[EEPROM] FlashSectorErase() %p\n", _sector);
        if (FAPI_STATUS_SUCCESS != FlashProgram(_data, (intptr_t)_sector, _size))
        {
            EEPROM_PRINTF("[ERROR] FlashProgram() %p, %p, %u\n", _data, _sector, (int)_size);
        }
        else
        {
            EEPROM_PRINTF("[EEPROM] FlashProgram() %p, %p, %u\n", _data, _sector, (int)_size);
            res = true;
        }
    }
    else
    {
        EEPROM_PRINTF("[ERROR] FlashSectorErase() %p\n", _sector);
    }

    restoreFlashCache(mode);
    interrupts();

    return res;
}

uint8_t *EEPROMClass::getDataPtr()
{
    _dirty = true;
    return &_data[0];
}

uint8_t const *EEPROMClass::getConstDataPtr() const
{
    return &_data[0];
}

EEPROMClass EEPROM;