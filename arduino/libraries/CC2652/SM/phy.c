#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ot_radio.h>
#include "phy.h"
#include "sysTaskManager.h"

volatile PHY_State_t phyState = PHY_STATE_INITIAL;
volatile uint8_t phyTxStatus;

//////////////////////////////////////////////////////////////////////////////////////////////
// OT CALLBACKS
//////////////////////////////////////////////////////////////////////////////////////////////

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
    phyState = PHY_STATE_TX_CONFIRM;
    phyTxStatus = aError;
    SYS_TaskSet(PHY_TASK);
}

//////////////////////////////////////////////////////////////////////////////////////////////

void PHY_Init(void)
{ /* NONE */
}

void PHY_SetRxState(bool rx)
{
    SYS_TaskSet(PHY_TASK);
}

void PHY_SetTxPower(uint8_t txPower)
{
    otPlatRadioSetTransmitPower(txPower);
}

void PHY_SetChannel(uint8_t channel)
{
    otPlatRadioReceive(channel);
}

void PHY_SetPanId(uint16_t panId)
{
    otPlatRadioSetPanId(panId);
}

void PHY_SetAddr(uint16_t addr)
{
    otPlatRadioSetShortAddress(addr);
}

bool PHY_Busy(void) { return false; }

void PHY_SleepReq(void) {}

void PHY_WakeupReq(void) {}

void PHY_DataReq(uint8_t *data, uint8_t size)
{
    otRadioFrame frame;
    frame.mPsdu = data;
    frame.mLength = size + 2;
    otPlatRadioTransmit(&frame);
    phyState = PHY_STATE_TX_WAIT_END;
    SYS_TaskSet(PHY_TASK);
}

void phyTaskHandler(void)
{
    printf("[PHY] STATE: %d\n", (int)phyState);
    switch (phyState)
    {
    case PHY_STATE_INITIAL: //0
        break;

    case PHY_STATE_IDLE: //1
        break;

    case PHY_STATE_SLEEP: //2
        break;

    case PHY_STATE_TX_WAIT_END: //3
        break;

    case PHY_STATE_TX_CONFIRM: //4
        PHY_DataConf(phyTxStatus);
        phyState = PHY_STATE_IDLE;
        SYS_TaskSet(PHY_TASK);
        break;

    case PHY_STATE_RX_IND: //5
    {
        PHY_DataInd_t ind;
        uint8_t size;
        uint8_t lqi;

        //TODO

        phyState = PHY_STATE_IDLE;
        SYS_TaskSet(PHY_TASK);
    }
    break;

    default:
        break;
    }
}