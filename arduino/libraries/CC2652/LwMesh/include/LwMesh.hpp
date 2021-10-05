#include <ieee_ot_radio.h>
#include "sysConfig.h"
#include "phy.h"
#include "nwk.h"
#include "hal.h"

extern "C" void PHY_TaskHandler(void);
extern "C" void NWK_TaskHandler(void);
extern "C" void SYS_TimerInit(void);
extern "C" void SYS_TimerTaskHandler(void);

class LwMesh
{
    typedef void (*TaskHandler)(void);

private:
    Radio radio;
    uint16_t _Panid;
    uint16_t _Address;
    uint8_t _Channel;
    int8_t _Power;

#define MAX_HANDLERS NWK_ENDPOINTS_AMOUNT
    TaskHandler aHandlers[MAX_HANDLERS];

public:
    LwMesh(uint16_t aPanid, uint16_t aAddress, int8_t aPower, uint8_t aChannel)
    {
        _Panid = aPanid;
        _Address = aAddress;
        _Channel = aChannel;
        _Power = aPower;
        memset(aHandlers, 0, sizeof(aHandlers));
    }

    inline uint16_t getNexHop(uint16_t dst, uint8_t multicast)
    {
#ifdef NWK_ENABLE_ROUTING
        return NWK_RouteNextHop(dst, multicast);
#else
        return 0;
#endif
    }

    inline void setSecurityKey(uint8_t *key)
    {
#ifdef NWK_ENABLE_SECURITY
        NWK_SetSecurityKey(key);
#endif
    }

    void send(NWK_DataReq_t *req)
    {
        if (req)
            NWK_DataReq(req); // add to que
    }

    // Endpoint index (1-15)
    bool runTask(uint8_t appEndPoint, void (*appTaskHandler)(void), bool (*appDataInd)(NWK_DataInd_t *))
    {
        if (appEndPoint && appEndPoint < MAX_HANDLERS && appTaskHandler && appDataInd)
        {
            NWK_OpenEndpoint(appEndPoint, appDataInd);
            aHandlers[appEndPoint] = appTaskHandler;
            return true;
        }
        return false;
    }

    // Endpoint index (1-15)
    bool begin(uint8_t appEndPoint, void (*appTaskHandler)(void), bool (*appDataInd)(NWK_DataInd_t *))
    {
        SYS_TimerInit();
        NWK_Init();
        PHY_Init();
        if (appEndPoint && appTaskHandler && appDataInd)
        {
            NWK_SetAddr(_Address);
            NWK_SetPanId(_Panid);
            PHY_SetTxPower(_Power);
            if (runTask(appEndPoint, appTaskHandler, appDataInd))
                return radio.begin(_Channel);
        }
        return false;
    }

    void loop()
    {
        radio.loop();
        PHY_TaskHandler();
        NWK_TaskHandler();
        SYS_TimerTaskHandler();
        for (int i = 0; i < MAX_HANDLERS; i++)
            if (aHandlers[i])
                aHandlers[i]();
    }
};