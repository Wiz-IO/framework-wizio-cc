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

    /* for receive */
    inline void SetPanId(uint16_t aPanid) { otPlatRadioSetPanId(aPanid); }

    /* for receive */
    inline void SetShortAddress(uint16_t aAddress) { otPlatRadioSetShortAddress(aAddress); }

    inline int SetTransmitPower(int8_t aPower) { return otPlatRadioSetTransmitPower(aPower); }

    int enable() { return otPlatRadioEnable(); }

    int disable() { return otPlatRadioDisable(); }

    int receive(uint8_t aChannel = 11) { return otPlatRadioReceive(aChannel); }

    /*auto add length & crc*/
    int send_raw(uint8_t *buffer, uint8_t size)
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

    void loop()
    {
        cc2652RadioProcess();
    }

    bool begin(uint16_t aPanid, uint16_t aAddress, uint8_t aChannel = 11)
    {
        otPlatRadioSetPanId(aPanid);          /* for receive */
        otPlatRadioSetShortAddress(aAddress); /* for receive */
        otPlatRadioSetTransmitPower(0);       /* error ?! */
        if (OT_ERROR_NONE == otPlatRadioEnable())
            if (OT_ERROR_NONE == otPlatRadioReceive(aChannel))
                return true;
        return false;
    }
};