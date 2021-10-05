#include <stdbool.h>
#include <string.h>
#include "../../OT_RADIO/ot_radio.h"
#include "phy.h"

typedef enum
{
    PHY_STATE_INITIAL,
    PHY_STATE_IDLE,
    PHY_STATE_SLEEP,
    PHY_STATE_TX_WAIT_END,
    PHY_STATE_TX_CONFIRM,
} PhyState_t;

static PhyState_t phyState = PHY_STATE_INITIAL;
static uint8_t tx_status = PHY_STATUS_ERROR;

static otRadioFrame phyRxFrame;
//////////////////////////////////////////////////////////////////////////////////////////////
// OT CALLBACKS
//////////////////////////////////////////////////////////////////////////////////////////////

void otPlatRadioEnergyScanDone(int8_t aEnergyScanMaxRssi) {}

void otPlatRadioTxStarted(otRadioFrame *aFrame) {}

void otPlatRadioTxDone(otRadioFrame *aFrame, otRadioFrame *aAckFrame, otError aError)
{
    PHY_PRINTF("[RADIO] %s( %d )\n", __func__, (int)aError);
    switch (aError)
    {
    case OT_ERROR_NONE:
        tx_status = PHY_STATUS_SUCCESS;
        break;
    case OT_ERROR_NO_ACK:
        tx_status = PHY_STATUS_NO_ACK;
        break;
    default:
        tx_status = PHY_STATUS_ERROR;
        break;
    }
    phyState = PHY_STATE_TX_CONFIRM;
}

void otPlatRadioReceiveDone(otRadioFrame *aFrame, otError aError)
{
    if (OT_ERROR_NONE == aError)
    {
        PHY_PRINTF("[RADIO] %s( %d ) RSSI = %d LQI  = %d\n",
                   __func__, (int)aError,
                   (int)aFrame->mInfo.mRxInfo.mRssi,
                   (int)aFrame->mInfo.mRxInfo.mLqi);
        memcpy(&phyRxFrame, aFrame, sizeof(otRadioFrame));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

void PHY_Init(void)
{
    memset(&phyRxFrame, 0, sizeof(otRadioFrame));
    phyState = PHY_STATE_INITIAL;
}

void PHY_SetTxPower(uint8_t txPower) { otPlatRadioSetTransmitPower(txPower); }

void PHY_SetChannel(uint8_t channel) { otPlatRadioReceive(channel); }

void PHY_SetPanId(uint16_t panId) { otPlatRadioSetPanId(panId); }

void PHY_SetShortAddr(uint16_t addr) { otPlatRadioSetShortAddress(addr); }

void PHY_SleepReq(void)
{
    if (0 == otPlatRadioDisable())
        phyState = PHY_STATE_SLEEP;
}

void PHY_WakeupReq(void)
{
    if (0 == otPlatRadioEnable())
        phyState = PHY_STATE_IDLE;
}

void PHY_DataReq(uint8_t *data, uint8_t size)
{
    otRadioFrame frame;
    frame.mPsdu = data;
    frame.mLength = size + 2;
    otPlatRadioTransmit(&frame); // ERROR?
    phyState = PHY_STATE_TX_WAIT_END;
}

void PHY_TaskHandler(void)
{
    if (PHY_STATE_SLEEP == phyState)
        return;

    if (PHY_STATE_TX_CONFIRM == phyState)
    {
        phyState = PHY_STATE_IDLE;
        PHY_DataConf(tx_status);
    }

    if (phyRxFrame.mLength)
    {
        PHY_DataInd_t ind;
        ind.data = phyRxFrame.mPsdu;
        ind.size = phyRxFrame.mLength - 2;
        ind.lqi = phyRxFrame.mInfo.mRxInfo.mLqi;
        ind.rssi = (int8_t)phyRxFrame.mInfo.mRxInfo.mRssi + PHY_RSSI_BASE_VAL;
        PHY_DataInd(&ind);
        phyRxFrame.mLength = 0;
    }
}