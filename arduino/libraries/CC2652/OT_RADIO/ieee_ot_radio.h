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

#include <stdint.h>
#include "ot_radio.h"

/* CALLBACKS

void otPlatRadioEnergyScanDone(int8_t aEnergyScanMaxRssi)
{
    printf("[RADIO] %s()\n", __func__);
}

void otPlatRadioReceiveDone(otRadioFrame *aFrame, otError aError)
{
    printf("[RADIO] %s()\n", __func__);
}

void otPlatRadioTxStarted(otRadioFrame *aFrame)
{
    printf("[RADIO] %s()\n", __func__);
}

void otPlatRadioTxDone(otRadioFrame *aFrame, otRadioFrame *aAckFrame, otError aError)
{
    printf("[RADIO] %s( %d )\n", __func__, (int)aError);
}

*/

class Radio
{

public:
    Radio() { cc2652RadioInit(); }
    ~Radio() { otPlatRadioDisable(); }

    inline void SetPanId(uint16_t aPanid) { otPlatRadioSetPanId(aPanid); }

    inline void SetShortAddress(uint16_t aAddress) { otPlatRadioSetShortAddress(aAddress); }

    inline int SetTransmitPower(int8_t aPower) { return otPlatRadioSetTransmitPower(aPower); }

    inline int enable() { return otPlatRadioEnable(); }

    inline int disable() { return otPlatRadioDisable(); }

    inline int receive(uint8_t aChannel = 11) { return otPlatRadioReceive(aChannel); }

    inline void process() { cc2652RadioProcess(); }

    int transmit(uint8_t *buffer, uint8_t size, void *user = NULL)
    {
        if (buffer && size < 128 /* max ? */)
        {
            otRadioFrame *otFrame = otPlatRadioGetTransmitBuffer();
            otFrame->mPsdu = buffer;
            otFrame->mLength = size + 2; /* otPlatRadioTransmit() will remove 2 bytes*/
            otFrame->mUser = user;
            return otPlatRadioTransmit(otFrame);
        }
        return -1;
    }

    int transmit()
    {
        otRadioFrame *otFrame = otPlatRadioGetTransmitBuffer();
        otFrame->mLength += 2; /* otPlatRadioTransmit() will remove 2 bytes*/
        return otPlatRadioTransmit(otFrame);
    }

    bool begin(uint16_t aPanid, uint16_t aAddress, int8_t aPower, uint8_t aChannel = 11)
    {
        if (false == otPlatRadioIsEnabled())
        {
            otPlatRadioSetPanId(aPanid);
            otPlatRadioSetShortAddress(aAddress);
            if (OT_ERROR_NONE == otPlatRadioSetTransmitPower(aPower))
            {
                if (OT_ERROR_NONE == otPlatRadioEnable())                 // power on
                    return OT_ERROR_NONE == otPlatRadioReceive(aChannel); // goto rx mode
            }
        }
        return false;
    }

    bool begin(uint8_t aChannel = 11)
    {
        if (false == otPlatRadioIsEnabled())
        {
            if (OT_ERROR_NONE == otPlatRadioEnable())                 // power on
                return OT_ERROR_NONE == otPlatRadioReceive(aChannel); // goto rx mode
        }
        return false;
    }
};