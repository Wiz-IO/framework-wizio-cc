#include <stdbool.h>
#include <string.h>
#include <ot_radio.h>
#include "phy.h"
#include "sysTaskManager.h"
#include "sysQueue.h"

volatile PHY_State_t phyState = PHY_STATE_INITIAL;
volatile uint8_t phyTxStatus = -1;

static SYS_Queue_t *rxQueue;

//////////////////////////////////////////////////////////////////////////////////////////////
// OT CALLBACKS
//////////////////////////////////////////////////////////////////////////////////////////////

void otPlatRadioEnergyScanDone(int8_t aEnergyScanMaxRssi) {}

void otPlatRadioReceiveDone(otRadioFrame *aFrame, otError aError)
{
    PHY_PRINTF("[RADIO] %s( %d )\n", __func__, (int)aError);
    if (OT_ERROR_NONE == aError)
    {
        otRadioFrame *rx = (otRadioFrame *)malloc(sizeof(otRadioFrame));
        if (rx)
        {
            memcpy(rx, aFrame, sizeof(otRadioFrame));
            SYS_QueueAppend(&rxQueue, rx);
            phyState = PHY_STATE_RX_IND;
            SYS_TaskSetInline(PHY_TASK);
        }
        else
        {
            PHY_PRINTF("[ERROR] %s()\n", __func__);
        }
    }
}

void otPlatRadioTxStarted(otRadioFrame *aFrame) {}

void otPlatRadioTxDone(otRadioFrame *aFrame, otRadioFrame *aAckFrame, otError aError)
{
    PHY_PRINTF("[RADIO] %s( %d )\n", __func__, (int)aError);
    if (OT_ERROR_NONE == aError)
    {
        if (aAckFrame)
            phyTxStatus = TRAC_STATUS_SUCCESS;
        else
            phyTxStatus = TRAC_STATUS_NO_ACK;
        phyState = PHY_STATE_TX_CONFIRM;
        SYS_TaskSet(PHY_TASK);
    }
    else
    {
        phyTxStatus = -1;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

void PHY_Init(void) { SYS_QueueInit(&rxQueue); }

void PHY_SetRxState(bool rx)
{
    phyState = PHY_STATE_IDLE;
    SYS_TaskSet(PHY_TASK);
}

void PHY_SetTxPower(uint8_t txPower) { otPlatRadioSetTransmitPower(txPower); }

void PHY_SetChannel(uint8_t channel) { otPlatRadioReceive(channel); }

void PHY_SetPanId(uint16_t panId) { otPlatRadioSetPanId(panId); }

void PHY_SetAddr(uint16_t addr) { otPlatRadioSetShortAddress(addr); }

bool PHY_Busy(void) { return PHY_STATE_IDLE != phyState; }

void PHY_SleepReq(void) { otPlatRadioDisable(); }

void PHY_WakeupReq(void) { otPlatRadioEnable(); }

void PHY_DataReq(uint8_t *data, uint8_t size)
{
    otRadioFrame frame;
    frame.mPsdu = data;
    frame.mLength = size + 2;
    otPlatRadioTransmit(&frame);
    phyState = PHY_STATE_TX_WAIT_END;
    SYS_TaskSet(PHY_TASK);
}

static void rx_ind(void)
{
    otRadioFrame *frame = SYS_QueueHead(&rxQueue);
    if (frame)
    {
        PHY_DataInd_t ind;
        ind.data = frame->mPsdu;
        ind.size = frame->mLength - 2;         // ??? crc
        ind.lqi = frame->mInfo.mRxInfo.mLqi;   // ???
        ind.rssi = frame->mInfo.mRxInfo.mRssi; // ???
        PHY_DataInd(&ind);

        SYS_QueueRemove(&rxQueue, frame);
        free(frame);
        if (SYS_QueueHead(&rxQueue))
        {
            phyState = PHY_STATE_RX_IND;
            SYS_TaskSet(PHY_TASK);
        }
        else
        {
            phyState = PHY_STATE_IDLE;
            SYS_TaskSet(PHY_TASK);
        }
    }
}

void phyTaskHandler(void)
{
    PHY_PRINTF("[PHY] STATE: %d\n", (int)phyState);
    switch (phyState)
    {
    case PHY_STATE_INITIAL:
        break;

    case PHY_STATE_IDLE:
        break;

    case PHY_STATE_SLEEP:
        break;

    case PHY_STATE_TX_WAIT_END:
        break;

    case PHY_STATE_TX_CONFIRM: //4
        PHY_DataConf(phyTxStatus);
        phyState = PHY_STATE_IDLE;
        SYS_TaskSet(PHY_TASK);
        break;

    case PHY_STATE_RX_IND: // 5
        rx_ind();
        break;

    default:
        break;
    }
}