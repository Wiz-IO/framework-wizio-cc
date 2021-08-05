#include "RF.h"

#include <driverlib/rfc.h>
#include <driverlib/rf_mailbox.h>
#include <driverlib/rf_common_cmd.h>
#include <driverlib/rf_ble_mailbox.h>
#include <driverlib/rf_ble_cmd.h>

#define BLE_PRINT Serial.printf

#define BLE_ADV_TYPE_DEVINFO 0x01
#define BLE_ADV_TYPE_NAME 0x09
#define BLE_ADV_TYPE_TX_POWER_LVL 0x0A

static uint32_t ble_overrides[] = {
    0x00364038, /* Synth: Set RTRIM (POTAILRESTRIM) to 6 */
    0x000784A3, /* Synth: Set FREF = 3.43 MHz (24 MHz / 7) */
    0xA47E0583, /* Synth: Set loop bandwidth after lock to 80 kHz (K2) */
    0xEAE00603, /* Synth: Set loop bandwidth after lock to 80 kHz (K3, LSB) */
    0x00010623, /* Synth: Set loop bandwidth after lock to 80 kHz (K3, MSB) */
    0x00456088, /* Adjust AGC reference level */
    0xFFFFFFFF, /* End of override list */
};

class BLE : public RF
{
public:
    BLE() {}
    ~BLE() {}
    void begin()
    {
        powerOn();
        _setup();
    }

    void advertise(const char *name)
    {
        if (name)
        {

            // Advertisement output structure
            __attribute__((aligned(4))) rfc_bleAdvOutput_s out;
            memset(&out, 0, sizeof(rfc_bleAdvOutput_s));

            // Advertisement parameters structure
            __attribute__((aligned(4))) rfc_bleAdvPar_t params;
            memset(&params, 0, sizeof(rfc_bleAdvPar_t));

            // RF command structure
            __attribute__((aligned(4))) rfc_CMD_BLE_ADV_NC_t cmd;
            memset(&cmd, 0, sizeof(rfc_CMD_BLE_ADV_NC_t));

            // Payload structure: <length (1 byte)> <type (1 byte)> <data>
            uint8_t bleAdvPayload[32] = {
                // See core supplement v6, 1.3.2, flags: LE discoverable, BR/EDR not supported
                2,
                BLE_ADV_TYPE_DEVINFO,
                0x06,
                // TX power level: 5dBm (this not a setting, it is just for informing the scanner, so that it can calculate the losses)
                2,
                BLE_ADV_TYPE_TX_POWER_LVL,
                5,
            };
            int payload_len = 6;
            uint8_t *p = &bleAdvPayload[payload_len];
            *p++ = strlen(name) + 1;
            *p++ = BLE_ADV_TYPE_NAME;
            payload_len += 2;
            for (int i = 0; i < 32 - 6 - 2; payload_len++, i++)
            {
                if (0 == name[i])
                    break;
                *p++ = name[i];
            }
            //DMP("ADV", bleAdvPayload, payload_len);

            // Set advertising parameters
            params.advLen = payload_len;
            params.pAdvData = bleAdvPayload;
            params.endTrigger.triggerType = TRIG_NEVER;
            params.endTime = TRIG_NEVER;

            //params.pDeviceAddress = (uint16_t *)&;
            cmd.commandNo = CMD_BLE_ADV_NC;
            cmd.channel = 37; // adv channel
            cmd.condition.rule = COND_NEVER;
            cmd.pOutput = (rfc_bleAdvOutput_t *)&out;
            cmd.pParams = (rfc_bleAdvPar_t *)&params;

            // Send command and wait for results
            if (0 == executeCommand((uint32_t)&cmd))
                waitCommandDone((uint32_t)&cmd);
        }
    }

private:
    bool _setup()
    {
        int res;
        __attribute__((aligned(4))) rfc_CMD_RADIO_SETUP_t cmd;
        memset(&cmd, 0, sizeof(rfc_CMD_RADIO_SETUP_t));

        cmd.mode = 0; // BLE
        cmd.commandNo = CMD_RADIO_SETUP;
        cmd.condition.rule = COND_NEVER;
        cmd.txPower = 0x9330;    // ????
        cmd.pRegOverride = NULL; // ble_overrides; 

        if (executeCommand((uint32_t)&cmd))
        {
            return false;
        }

        res = waitCommandDone((uint32_t)&cmd);
        if (res != DONE_OK)
        {
            return false;
        }

        res = RFCDoorbellSendTo(CMDR_DIR_CMD(CMD_START_RAT));
        BLE_PRINT("[BLE] CMD_START_RAT = 0x%X\n", res);
        return res == 0x1;
    }
};