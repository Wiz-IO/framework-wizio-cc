// https://github.com/openthread/ot-cc13x2-cc26x2/blob/main/src/cc2652/radio.c

#include <Arduino.h>
#include "RF.h"
#include <driverlib/rf_ieee_cmd.h>
#include <driverlib/rf_ieee_mailbox.h>
#include <driverlib/rf_data_entry.h>

#define IEEE_PRINT Serial.printf

void RFCCPE1IntHandler(void);
void RFCCPE0IntHandler(void);

/* Overrides for IEEE 802.15.4, differential mode */
static uint32_t ieee_overrides[] = {
    0x00354038, /* Synth: Set RTRIM (POTAILRESTRIM) to 5 */
    0x4001402D, /* Synth: Correct CKVD latency setting (address) */
    0x00608402, /* Synth: Correct CKVD latency setting (value) */
    0x4001405D, /* Synth: Set ANADIV DIV_BIAS_MODE to PG1 (address) */
    0x1801F800, /* Synth: Set ANADIV DIV_BIAS_MODE to PG1 (value) */
    0x000784A3, /* Synth: Set FREF = 3.43 MHz (24 MHz / 7) */
    0xA47E0583, /* Synth: Set loop bandwidth after lock to 80 kHz (K2) */
    0xEAE00603, /* Synth: Set loop bandwidth after lock to 80 kHz (K3, LSB) */
    0x00010623, /* Synth: Set loop bandwidth after lock to 80 kHz (K3, MSB) */
    0x002B50DC, /* Adjust AGC DC filter */
    0x05000243, /* Increase synth programming timeout */
    0x002082C3, /* Increase synth programming timeout */
    0xFFFFFFFF, /* End of override list */
};

static __attribute__((aligned(4))) rfc_ieeeRxOutput_t sRfStats;
static __attribute__((aligned(4))) dataQueue_t sRxDataQueue = {0, 0};
#define RX_BUF_SIZE 144
static __attribute__((aligned(4))) uint8_t sRxBuf0[RX_BUF_SIZE];
static __attribute__((aligned(4))) uint8_t sRxBuf1[RX_BUF_SIZE];
static __attribute__((aligned(4))) uint8_t sRxBuf2[RX_BUF_SIZE];
static __attribute__((aligned(4))) uint8_t sRxBuf3[RX_BUF_SIZE];

class IEEE : public RF
{
public:
    IEEE()
    {
        memset(&cmdRx, 0, sizeof(rfc_CMD_IEEE_RX_t));

        cmdRx.commandNo = CMD_IEEE_RX;
        cmdRx.status = IDLE;
        cmdRx.pNextOp = 0;
        cmdRx.startTime = 0;
        cmdRx.startTrigger.triggerType = 0;
        cmdRx.startTrigger.bEnaCmd = 0;
        cmdRx.startTrigger.triggerNo = 0;
        cmdRx.startTrigger.pastTrig = 0;
        {
            cmdRx.condition.rule = COND_NEVER;
            cmdRx.condition.nSkip = 0;
        }
        cmdRx.channel = 11; // 11--26: Use as IEEE 802.15.4 channel, i.e. frequency is (2405 + 5 &times; (channel - 11)) MHz<br>
        {
            cmdRx.rxConfig.bAutoFlushCrc = 1;
            cmdRx.rxConfig.bAutoFlushIgn = 0;
            cmdRx.rxConfig.bIncludePhyHdr = 0;
            cmdRx.rxConfig.bIncludeCrc = 0;
            cmdRx.rxConfig.bAppendRssi = 1;
            cmdRx.rxConfig.bAppendCorrCrc = 1;
            cmdRx.rxConfig.bAppendSrcInd = 0;
            cmdRx.rxConfig.bAppendTimestamp = 0;
        };
        cmdRx.pRxQ = &sRxDataQueue;
        cmdRx.pOutput = &sRfStats;
        {
            cmdRx.frameFiltOpt.frameFiltEn = 1;
            cmdRx.frameFiltOpt.frameFiltStop = 1;
            cmdRx.frameFiltOpt.autoAckEn = 1;
            cmdRx.frameFiltOpt.slottedAckEn = 0;
            cmdRx.frameFiltOpt.autoPendEn = 0;
            cmdRx.frameFiltOpt.defaultPend = 0;
            cmdRx.frameFiltOpt.bPendDataReqOnly = 0;
            cmdRx.frameFiltOpt.bPanCoord = 0;
            cmdRx.frameFiltOpt.maxFrameVersion = 3;
            cmdRx.frameFiltOpt.fcfReservedMask = 0;
            cmdRx.frameFiltOpt.modifyFtFilter = 0;
            cmdRx.frameFiltOpt.bStrictLenFilter = 1;
        }
        {
            cmdRx.frameTypes.bAcceptFt0Beacon = 1;
            cmdRx.frameTypes.bAcceptFt1Data = 1;
            cmdRx.frameTypes.bAcceptFt2Ack = 1;
            cmdRx.frameTypes.bAcceptFt3MacCmd = 1;
            cmdRx.frameTypes.bAcceptFt4Reserved = 1;
            cmdRx.frameTypes.bAcceptFt5Reserved = 1;
            cmdRx.frameTypes.bAcceptFt6Reserved = 1;
            cmdRx.frameTypes.bAcceptFt7Reserved = 1;
        }
        {
            cmdRx.ccaOpt.ccaEnEnergy = 1;
            cmdRx.ccaOpt.ccaEnCorr = 1;
            cmdRx.ccaOpt.ccaEnSync = 1;
            cmdRx.ccaOpt.ccaCorrOp = 1;
            cmdRx.ccaOpt.ccaSyncOp = 0;
            cmdRx.ccaOpt.ccaCorrThr = 1;
        }
        cmdRx.ccaRssiThr = 0xA6;   // -90dBm
        cmdRx.numExtEntries = 0;   //
        cmdRx.numShortEntries = 0; //
        cmdRx.pExtEntryList = 0;   //
        cmdRx.pShortEntryList = 0; //
        cmdRx.localExtAddr = 0;    //
        cmdRx.localShortAddr = 0;  //
        cmdRx.localPanID = 0;      //
        {
            cmdRx.endTrigger.triggerType = TRIG_NEVER;
            cmdRx.endTrigger.bEnaCmd = 0;
            cmdRx.endTrigger.triggerNo = 0;
            cmdRx.endTrigger.pastTrig = 0;
        }
        cmdRx.endTime = 0;
        //cmdRx.__dummy0 = 0;
        //cmdRx.__dummy1 = 0;
        //cmdRx.__dummy2 = 0;

        init_buffers();
    }

    ~IEEE() {}
    void begin()
    {
        if (false == isOn)
        {
            powerOn();
            int_enable();
            setup();
        }
    }

    bool tx(uint8_t *buf, size_t size)
    {
        IEEE_PRINT("[IEEE] %s()\n", __func__);
        __attribute__((aligned(4))) rfc_CMD_IEEE_TX_t cmd;
        memset(&cmd, 0, sizeof(rfc_CMD_IEEE_TX_t));
        cmd.commandNo = CMD_IEEE_TX;
        cmd.condition.rule = COND_NEVER;
        cmd.payloadLen = size;
        cmd.pPayload = buf;
        return execute((uint32_t)&cmd);
    }

    bool rx()
    {
        IEEE_PRINT("[IEEE] %s()\n", __func__);
        if (isOn)
            return execute((uint32_t)&cmdRx, false);
        return false;
    }

private:
    rfc_CMD_IEEE_RX_t cmdRx;

    void setup(uint16_t power = 0x9330)
    {
        if (isOn)
        {
            IEEE_PRINT("[IEEE] %s()\n", __func__);
            int res;
            __attribute__((aligned(4))) rfc_CMD_RADIO_SETUP_t cmd;
            memset(&cmd, 0, sizeof(rfc_CMD_RADIO_SETUP_t));
            cmd.mode = 1; // IEEE
            cmd.commandNo = CMD_RADIO_SETUP;
            cmd.condition.rule = COND_NEVER;
            cmd.txPower = power; // ????
            cmd.pRegOverride = ieee_overrides;
            execute((uint32_t)&cmd);
        }
    }

    void init_buffers()
    {
        rfc_dataEntry_t *entry;
        memset(sRxBuf0, 0, sizeof(sRxBuf0));
        memset(sRxBuf1, 0, sizeof(sRxBuf1));
        memset(sRxBuf2, 0, sizeof(sRxBuf2));
        memset(sRxBuf3, 0, sizeof(sRxBuf3));

        entry = (rfc_dataEntry_t *)sRxBuf0;
        entry->pNextEntry = sRxBuf1;
        entry->config.lenSz = 1;
        entry->length = sizeof(sRxBuf0) - sizeof(rfc_dataEntry_t);

        entry = (rfc_dataEntry_t *)sRxBuf1;
        entry->pNextEntry = sRxBuf2;
        entry->config.lenSz = 1;
        entry->length = sizeof(sRxBuf1) - sizeof(rfc_dataEntry_t);

        entry = (rfc_dataEntry_t *)sRxBuf2;
        entry->pNextEntry = sRxBuf3;
        entry->config.lenSz = 1;
        entry->length = sizeof(sRxBuf2) - sizeof(rfc_dataEntry_t);

        entry = (rfc_dataEntry_t *)sRxBuf3;
        entry->pNextEntry = sRxBuf0;
        entry->config.lenSz = 1;
        entry->length = sizeof(sRxBuf3) - sizeof(rfc_dataEntry_t);
    }

    void int_enable()
    {
        uint32_t p;
        ENTER_CRITICAL(p);

        /* Set all interrupt channels to CPE0 channel, error to CPE1 */
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEISL) = IRQ_INTERNAL_ERROR;
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIEN) = IRQ_LAST_COMMAND_DONE | IRQ_LAST_FG_COMMAND_DONE;

        IntRegister(INT_RFC_CPE_0, RFCCPE0IntHandler);
        IntRegister(INT_RFC_CPE_1, RFCCPE1IntHandler);
        IntPendClear(INT_RFC_CPE_0);
        IntPendClear(INT_RFC_CPE_1);
        IntEnable(INT_RFC_CPE_0);
        IntEnable(INT_RFC_CPE_1);

        EXIT_CRITICAL(p);
        //IntMasterEnable
    }

    void int_disable()
    {
        uint32_t p;
        ENTER_CRITICAL(p);
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = 0x0;
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIEN) = 0x0;
        IntUnregister(INT_RFC_CPE_0);
        IntUnregister(INT_RFC_CPE_1);
        IntPendClear(INT_RFC_CPE_0);
        IntPendClear(INT_RFC_CPE_1);
        IntDisable(INT_RFC_CPE_0);
        IntDisable(INT_RFC_CPE_1);
        EXIT_CRITICAL(p);
    }
};

#if 0
    bool setFrequency(uint32_t ui32Frequency /* MHz */)
    {
        IEEE_PRINT("[IEEE] %s()\n", __func__);
        int res;
        __attribute__((aligned(4))) rfc_CMD_FS_t cmd;
        memset(&cmd, 0, sizeof(rfc_CMD_FS_t));
        if (on)
        {
            centerFreq = (uint16_t)(ui32Frequency / 1000000);
            fractFreq = (uint16_t)(((uint64_t)ui32Frequency - ((uint64_t)centerFreq * 1000000)) * 65536 / 1000000);
            IEEE_PRINT("[IEEE] C = %d, F = %d\n", (int)centerFreq, (int)fractFreq);

            cmd.commandNo = CMD_FS;
            cmd.condition.rule = COND_NEVER;
            cmd.frequency = centerFreq; // MHz
            cmd.fractFreq = fractFreq;

            if (executeCommand((uint32_t)&cmd))
            {
                IEEE_PRINT("[ERROR] %s execute\n", __func__);
                return false;
            }

            res = waitCommandDone((uint32_t)&cmd);
            if (res != DONE_OK)
            {
                //0x0809   Synthesizer calibration failed
                return false;
            }
            IEEE_PRINT("[IEEE] %s() done\n", __func__);
        }
        return false;
    }

#endif