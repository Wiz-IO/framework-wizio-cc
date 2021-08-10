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
private:
    bool on;

public:
    Radio()
    {
        on = false;
        cc2652RadioInit();
    }

    inline void SetPanId(uint16_t aPanid) { otPlatRadioSetPanId(aPanid); }

    inline void SetShortAddress(uint16_t aAddress) { otPlatRadioSetShortAddress(aAddress); }

    inline int SetTransmitPower(int8_t aPower) { return otPlatRadioSetTransmitPower(aPower); }

    inline int enable() { return otPlatRadioEnable(); }

    inline int disable() { return otPlatRadioDisable(); }

    int receive(uint8_t aChannel = 11) { return otPlatRadioReceive(aChannel); }

    inline void loop() { cc2652RadioProcess(); }

    /*auto add length & crc*/
    int transmit(uint8_t *buffer, uint8_t size)
    {
        if (otPlatRadioIsEnabled() && buffer && size < 128 /* max ? */)
        {
            otRadioFrame frame;
            frame.mPsdu = buffer;
            frame.mLength = size + 2; /* 2 bytes of CRC placeholder, removing, because we generate that in hardware */
            return otPlatRadioTransmit(&frame);
        }
        return -1;
    }

    bool begin(uint16_t aPanid, uint16_t aAddress, int8_t aPower, uint8_t aChannel)
    {
        if (false == on)
        {
            otPlatRadioSetPanId(aPanid);
            otPlatRadioSetShortAddress(aAddress);
            if (OT_ERROR_NONE == otPlatRadioSetTransmitPower(aPower))
            {
                if (OT_ERROR_NONE == otPlatRadioEnable())               // power on
                    on = OT_ERROR_NONE == otPlatRadioReceive(aChannel); // goto rx mode
            }
        }
        return on;
    }

    bool begin(uint8_t aChannel = 11)
    {
        if (false == on)
        {
            if (OT_ERROR_NONE == otPlatRadioEnable())               // power on
                on = OT_ERROR_NONE == otPlatRadioReceive(aChannel); // goto rx mode
        }
        return on;
    }
};