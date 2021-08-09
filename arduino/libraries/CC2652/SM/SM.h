#include <radio.h>
#include "nwk.h"
#include "sysTaskManager.h"

class SMClass
{
private:
    Radio r;
    uint16_t _Panid;
    uint16_t _Address;
    uint8_t _Channel;

public:
    SMClass(uint16_t aPanid, uint16_t aAddress, uint8_t aChannel = 11)
    {
        _Panid = aPanid;
        _Address = aAddress;
        _Channel = aChannel;
    }

    void send(NWK_DataReq_t *req)
    {
        if (req)
            NWK_DataReq(req); // add to que
    }

    // run task
    void run(uint8_t port, void (*handler)(void), bool (*ind)(NWK_DataInd_t *))
    {
        if (port && handler)
            NWK_PortOpen(port, handler, ind);
    }

    void begin(uint8_t port, void (*handler)(void), bool (*ind)(NWK_DataInd_t *), int8_t power = 0)
    {
        if (r.begin(_Panid, _Address, _Channel))
        {
            r.SetTransmitPower(power);
            NWK_Init();
            NWK_SetAddr(_Address);
            NWK_SetPanId(_Panid);
            run(port, handler, ind);
        }
        else
        {
            ::printf("[ERROR] SM begin()\n");
        }
    }

    void loop()
    {
        r.loop();
        SYS_TaskRun();
    }
};