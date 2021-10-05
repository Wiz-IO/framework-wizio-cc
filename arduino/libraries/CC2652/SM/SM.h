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
    int8_t _Power;

public:
    SMClass(uint16_t aPanid, uint16_t aAddress, int8_t aPower, uint8_t aChannel)
    {
        _Panid = aPanid;
        _Address = aAddress;
        _Channel = aChannel;
        _Power = aPower;
    }

    void send(NWK_DataReq_t *req)
    {
        if (req)
        {
            NWK_DataReq(req); // add to que
        }
        else
        {
            //::printf("[ERROR] send()\n");
        }
    }

    // run application task
    void run(uint8_t port, void (*handler)(void), bool (*ind)(NWK_DataInd_t *))
    {
        if (port && handler)
        {
            NWK_PortOpen(port, handler, ind);
        }
        else
        {
            //::printf("[ERROR] run()\n");
        }
    }

    void begin(uint8_t port, void (*handler)(void), bool (*ind)(NWK_DataInd_t *))
    {
        if (r.begin(_Panid, _Address, _Power, _Channel))
        {
            NWK_Init();
            NWK_SetAddr(_Address);
            NWK_SetPanId(_Panid);
            run(port, handler, ind);
        }
        else
        {
            //::printf("[ERROR] begin()\n");
        }
    }

    void loop()
    {
        r.loop();
        SYS_TaskRun();
    }
};