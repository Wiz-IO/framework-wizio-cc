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

#ifndef EEPROM_h
#define EEPROM_h

#include <stddef.h>
#include <stdint.h>
#include <string.h>

class EEPROMClass
{
public:
    EEPROMClass(void);

    void begin(size_t size);
    uint8_t read(int const address);
    void write(int const address, uint8_t const val);
    bool commit();
    bool end();

    uint8_t *getDataPtr();
    uint8_t const *getConstDataPtr() const;

    template <typename T>
    T &get(int const address, T &t)
    {
        if (address < 0 || address + sizeof(T) > _size)
        {
            return t;
        }

        memcpy((uint8_t *)&t, _data + address, sizeof(T));
        return t;
    }

    template <typename T>
    const T &put(int const address, const T &t)
    {
        if (address < 0 || address + sizeof(T) > _size)
        {
            return t;
        }
        if (memcmp(_data + address, (const uint8_t *)&t, sizeof(T)) != 0)
        {
            _dirty = true;
            memcpy(_data + address, (const uint8_t *)&t, sizeof(T));
        }

        return t;
    }

    inline size_t length() { return _size; }

    uint8_t &operator[](int const address) { return getDataPtr()[address]; }

    uint8_t const &operator[](int const address) const { return getConstDataPtr()[address]; }

protected:
    uint8_t *_sector;
    uint8_t *_data = nullptr;
    size_t _size = 0;
    bool _dirty = false;
};

extern EEPROMClass EEPROM;

#endif
