#include <driverlib/prcm.h>
#include <driverlib/rfc.h>

#define DBG_RF Serial.printf

class RF
{
public:
    bool isOn;
    RF()
    {
        isOn = false;
    };
    virtual ~RF(){};
    virtual void begin();

    void powerOn(uint32_t mode = PRCM_RFCMODESEL_CURR_MODE5) // PRCM_RFCMODESEL_CURR_MODE1 /* BLE */
    {
        PRCMPowerDomainOff(PRCM_DOMAIN_RFCORE);
        PRCMLoadSet();
        while (!PRCMLoadGet())
        {
        }

        HWREG(PRCM_BASE + PRCM_O_RFCMODESEL) = mode;

        // Power on RF core
        PRCMPowerDomainOn(PRCM_DOMAIN_RFCORE);
        while (PRCMPowerDomainsAllOn(PRCM_DOMAIN_RFCORE) != PRCM_DOMAIN_POWER_ON)
            ;

        PRCMLoadSet();
        while (!PRCMLoadGet())
        {
        }

        // Enable RF core clock
        PRCMDomainEnable(PRCM_DOMAIN_RFCORE);
        PRCMLoadSet();
        while (!PRCMLoadGet())
        {
        }

        // Wait for it...
        PRCMLoadSet();
        while (!PRCMLoadGet())
        {
        }

        /* Let CPE boot */
        RFCClockEnable();

        isOn = true;
        isOn = ping();
        DBG_RF("[RF] POWER %s\n", isOn ? "ON" : "OFF");
    }

    // true if CMDSTA_Done
    bool executeCommand(uint32_t pCmd)
    {
        if (isOn)
        {
            uint32_t res = RFCDoorbellSendTo(pCmd);
            if (res != CMDSTA_Done)
            {
                volatile rfc_radioOp_t *command = (rfc_radioOp_t *)pCmd;
                DBG_RF("[RF] CMD = %X, DOORBELL = %X\n", (int)command->status, (int)res);
            }
            return res == CMDSTA_Done;
        }
        return false;
    }

    // return command status
    uint32_t waitDone(uint32_t pCmd)
    {
        volatile rfc_radioOp_t *command = (rfc_radioOp_t *)pCmd;
        uint32_t timeout = 0;
        /* 0xn4nn = DONE, 0x0400 = DONE_OK while all other "DONE" values means done but with some kind of error (ref. "Common radio operation status codes") */
        do
        {
            if (++timeout > 500000)
            {
                DBG_RF("[ERROR] TIMEOUT CMD: %X STAT: %X\n", (int)command->commandNo, (int)command->status);
                return -1; // timeout
            }
        } while (!(command->status & 0x400));

        if (command->status != DONE_OK)
        {
            DBG_RF("[ERROR] STAT = 0x%X\n", (int)command->status);
        }
        return command->status;
    }

    bool execute(uint32_t cmd, bool wait = true)
    {
        bool res = executeCommand(cmd);
        if (res && wait)
            return DONE_OK == waitDone((uint32_t)cmd);
        return res;
    }

    bool ping(void)
    {
        return execute(CMDR_DIR_CMD(CMD_PING), false);
    }

    bool abort(void)
    {
        return execute(CMDR_DIR_CMD(CMD_ABORT), false);
    }
};