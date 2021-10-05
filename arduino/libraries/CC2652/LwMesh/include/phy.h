#ifndef _PHY_H_
#define _PHY_H_
#ifdef __cplusplus
extern "C" {
#endif


/*- Includes ---------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "sysConfig.h"

/*- Definitions ------------------------------------------------------------*/
#define PHY_RSSI_BASE_VAL                     (-90)

#define PHY_HAS_RANDOM_NUMBER_GENERATOR
#define PHY_HAS_AES_MODULE

/*- Types ------------------------------------------------------------------*/
typedef struct PHY_DataInd_t
{
  uint8_t    *data;
  uint8_t    size;
  uint8_t    lqi;
  int8_t     rssi;
} PHY_DataInd_t;

enum
{
  PHY_STATUS_SUCCESS                = 0,
  PHY_STATUS_CHANNEL_ACCESS_FAILURE = 1,
  PHY_STATUS_NO_ACK                 = 2,
  PHY_STATUS_ERROR                  = 3,
};

/*- Prototypes -------------------------------------------------------------*/
void PHY_Init(void);
void PHY_SetRxState(bool rx);
void PHY_SetChannel(uint8_t channel);
void PHY_SetBand(uint8_t band);
void PHY_SetPanId(uint16_t panId);
void PHY_SetShortAddr(uint16_t addr);
void PHY_SetTxPower(uint8_t txPower);
void PHY_Sleep(void);
void PHY_Wakeup(void);
void PHY_DataReq(uint8_t *data, uint8_t size);
void PHY_DataConf(uint8_t status);
void PHY_DataInd(PHY_DataInd_t *ind);
void PHY_TaskHandler(void);

#ifdef PHY_ENABLE_RANDOM_NUMBER_GENERATOR
uint16_t PHY_RandomReq(void);
#endif

#ifdef PHY_ENABLE_AES_MODULE
void PHY_EncryptReq(uint8_t *text, uint8_t *key);
#endif

#ifdef PHY_ENABLE_ENERGY_DETECTION
int8_t PHY_EdReq(void);
#endif

#define PHY_DEBUG
#ifdef PHY_DEBUG
  #include <stdio.h>
  #define PHY_PRINTF printf
#else
  #define PHY_PRINTF 
#endif

#ifdef __cplusplus
}
#endif
#endif // _PHY_H_
