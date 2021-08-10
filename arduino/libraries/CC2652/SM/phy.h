#ifndef _PHY_H_
#define _PHY_H_

#include <stdint.h>
#include <stdbool.h>

enum
{
  TRAC_STATUS_SUCCESS                = 0,
  TRAC_STATUS_SUCCESS_DATA_PENDING   = 1,
  TRAC_STATUS_SUCCESS_WAIT_FOR_ACK   = 2,
  TRAC_STATUS_CHANNEL_ACCESS_FAILURE = 3,
  TRAC_STATUS_NO_ACK                 = 5,
  TRAC_STATUS_INVALID                = 7,
};

typedef enum PHY_State_t
{
  PHY_STATE_INITIAL,
  PHY_STATE_IDLE,
  PHY_STATE_SLEEP,
  PHY_STATE_TX_WAIT_END,
  PHY_STATE_TX_CONFIRM,
  PHY_STATE_RX_IND,
} PHY_State_t;

typedef struct PHY_DataInd_t
{
  uint8_t    *data;
  uint8_t    size;
  uint8_t    lqi;
  int8_t     rssi;
} PHY_DataInd_t;

void PHY_Init(void);
void PHY_SetRxState(bool rx);
void PHY_SetTxPower(uint8_t txPower);
void PHY_SetChannel(uint8_t channel);
void PHY_SetPanId(uint16_t panId);
void PHY_SetAddr(uint16_t addr);
bool PHY_Busy(void);
void PHY_DataReq(uint8_t *data, uint8_t size);
void PHY_DataConf(uint8_t status);
void PHY_DataInd(PHY_DataInd_t *ind);
void PHY_SleepReq(void);
void PHY_WakeupReq(void);
void PHY_SleepConf(void);
void PHY_WakeupConf(void);

#ifdef PHY_DEBUG
  #include <stdio.h>
  #define PHY_PRINTF printf
#else
  #define PHY_PRINTF 
#endif

#endif // _PHY_H_