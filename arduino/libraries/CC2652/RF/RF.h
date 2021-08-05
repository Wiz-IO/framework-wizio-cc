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

    void powerOn(uint32_t mode = PRCM_RFCMODESEL_CURR_MODE1 /*BLE*/)
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

        // Enablde RF clocks
        // NOTE: This line was copypasted from SysCtrlPowerEverything
        HWREG(RFC_PWR_NONBUF_BASE + RFC_PWR_O_PWMCLKEN) = 0x7FF;

        // Wait for it...
        PRCMLoadSet();
        while (!PRCMLoadGet())
        {
        }

        isOn = true;
        DBG_RF("[RF] POWER ON\n");
    }

    int executeCommand(uint32_t pCmd)
    {
        /* If the RF core is ON, we can send the command */
        if (isOn)
        {
            /* Submit the command to the doorbell */
            uint32_t doorbell_status = RFCDoorbellSendTo(pCmd);
            DBG_RF("[RF] DOORBELL STATUS = %lu\n", doorbell_status);

            /* Check the return value of the RF core through the CMDSTA register within the doorbell */
            if ((doorbell_status & 0xFF) == CMDSTA_Done)
            {
                /* The command was accepted */
                return 0;
            }
            else
            {
                /* The command was rejected */
                return -2;
            }
        }
        else
        {
            /* The RF core is not capable of receiving the command */
            return -1;
        }
    }

    uint32_t waitCommandDone(uint32_t pCmd)
    {
        volatile rfc_radioOp_t *command = (rfc_radioOp_t *)pCmd;
        uint32_t timeout_cnt = 0;
        /* 0xn4nn=DONE, 0x0400 = DONE_OK while all other "DONE" values means done but with some kind of error (ref. "Common radio operation status codes") */
        do
        {
            if (++timeout_cnt > 500000)
            {
                DBG_RF("[ERROR] RF TIMEOUT\n");
                return -1;
            }
        } while (!(command->status & 0x400));
        DBG_RF("[RF] COMMAND STATUS = 0x%X\n", (int)command->status);
        return command->status;
    }
};