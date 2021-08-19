// BASE: https://github.com/openthread/ot-cc13x2-cc26x2/blob/main/src/cc2652/radio.c

#include <interface.h>
#include "LRADIO_DEF.h"
#include <rf_patches/rf_patch_cpe_ieee_802_15_4.h>
#include <driverlib/osc.h>
#include <inc/hw_ccfg.h>

#define RADIO_PRINTF
//printf

enum
{
    OT_RADIO_FRAME_MAX_SIZE = 127,                                                                                 ///< aMaxPHYPacketSize (IEEE 802.15.4-2006)
    OT_RADIO_FRAME_MIN_SIZE = 3,                                                                                   ///< Minimal size of frame FCS + CONTROL
    OT_RADIO_SYMBOLS_PER_OCTET = 2,                                                                                ///< 2.4 GHz IEEE 802.15.4-2006
    OT_RADIO_BIT_RATE = 250000,                                                                                    ///< 2.4 GHz IEEE 802.15.4 (bits per second)
    OT_RADIO_BITS_PER_OCTET = 8,                                                                                   ///< Number of bits per octet
    OT_RADIO_SYMBOL_TIME = ((OT_RADIO_BITS_PER_OCTET / OT_RADIO_SYMBOLS_PER_OCTET) * 1000000) / OT_RADIO_BIT_RATE, ///<
    OT_RADIO_LQI_NONE = 0,                                                                                         ///< LQI measurement not supported
    OT_RADIO_RSSI_INVALID = 127,                                                                                   ///< Invalid or unknown RSSI value
    OT_RADIO_POWER_INVALID = 127,                                                                                  ///< Invalid or unknown power value
};

typedef enum cc2652_PhyState
{
    cc2652_stateDisabled = 0,
    cc2652_stateSleep,
    cc2652_stateReceive,
    cc2652_stateEdScan,
    cc2652_stateTransmit,
} cc2652_PhyState_t;

typedef enum RadioError
{
    /**  No error. */
    ERROR_RADIO_NONE = 0,

    ERROR_RADIO_INVALID_PARAM,

    ERROR_RADIO_TIMEOUT,

    /** Operational failed. */
    ERROR_RADIO_FAILED,

    /** Insufficient buffers. */
    ERROR_RADIO_NO_BUFS,

    /** Service is busy and could not service the operation. */
    ERROR_RADIO_BUSY,

    /** Cannot complete due to invalid state. */
    ERROR_RADIO_INVALID_STATE,

    /**  No acknowledgment was received after macMaxFrameRetries (IEEE 802.15.4-2006). */
    ERROR_RADIO_NO_ACK,

    /** A transmission could not take place due to activity on the channel, i.e., the CSMA-CA mechanism has failed (IEEE 802.15.4-2006). */
    ERROR_RADIO_CHANNEL_ACCESS_FAILURE,

    /** FCS check failure while receiving. */
    ERROR_RADIO_FCS,

} RadioError;

typedef struct RadioFrame
{
    uint8_t *mPsdu;   ///< The PSDU.
    uint16_t mLength; ///< Length of the PSDU.
    uint8_t mChannel; ///< Channel used to transmit/receive the frame.

    /* The union of transmit and receive information for a radio frame. */
    union
    {
        /* Structure representing radio frame receive information. */
        struct
        {
            int8_t mRssi; ///< Received signal strength indicator in dBm for received frames.
            uint8_t mLqi; ///< Link Quality Indicator for received frames.
            // Flags
            bool mAckedWithFramePending : 1; ///< This indicates if this frame was acknowledged with frame pending set.
            bool mAckedWithSecEnhAck : 1;    ///< This indicates if this frame was acknowledged with secured enhance ACK.
        } mRxInfo;
    } mInfo;

    void *mUser; /* [WizIO] for Transmit frame user callback variable */
} RadioFrame;

// PACKED !!
typedef struct ExtAddress_s
{
    uint8_t m8[OT_EXT_ADDRESS_SIZE]; ///< IEEE 802.15.4 Extended Address bytes
} ExtAddress_t;

static cc2652_PhyState_t sState = cc2652_stateDisabled;
static RadioError sTransmitError = ERROR_RADIO_FAILED;
static unsigned int sTransmitRetryCount = 0;
static bool sTxCmdChainDone = false;

static __attribute__((aligned(4))) rfc_CMD_IEEE_RX_t sReceiveCmd;
static __attribute__((aligned(4))) rfc_CMD_IEEE_CSMA_t sCsmacaBackoffCmd;
static __attribute__((aligned(4))) rfc_CMD_IEEE_TX_t sTransmitCmd;
static __attribute__((aligned(4))) rfc_CMD_IEEE_RX_ACK_t sTransmitRxAckCmd;

#define RX_BUF_SIZE 144
static __attribute__((aligned(4))) uint8_t sRxBuf0[RX_BUF_SIZE];
static __attribute__((aligned(4))) uint8_t sRxBuf1[RX_BUF_SIZE];
static __attribute__((aligned(4))) uint8_t sRxBuf2[RX_BUF_SIZE];
static __attribute__((aligned(4))) uint8_t sRxBuf3[RX_BUF_SIZE];
static __attribute__((aligned(4))) dataQueue_t sRxDataQueue = {0, 0};

/* User callbacks */
typedef void (*HandleTxStarted)(RadioFrame *aFrame);
typedef void (*HandleTxDone)(RadioFrame *aFrame, RadioFrame *aAckFrame, RadioError aError);
typedef void (*HandleReceiveDone)(RadioFrame *aFrame);

class LRadio
{
protected:
    __attribute__((aligned(4))) rfc_CMD_CLEAR_RX_t sClearReceiveQueueCmd;
    __attribute__((aligned(4))) rfc_CMD_RADIO_SETUP_t sRadioSetupCmd;
    __attribute__((aligned(4))) rfc_CMD_FS_POWERDOWN_t sFsPowerdownCmd;
    __attribute__((aligned(4))) rfc_CMD_SYNC_START_RAT_t sStartRatCmd;
    __attribute__((aligned(4))) rfc_CMD_SYNC_STOP_RAT_t sStopRatCmd;

    __attribute__((aligned(4))) ext_src_match_data_t sSrcMatchExtData;
    __attribute__((aligned(4))) short_src_match_data_t sSrcMatchShortData;
    __attribute__((aligned(4))) rfc_ieeeRxOutput_t sRfStats;

    __attribute__((aligned(4))) uint8_t sTransmitPsdu[OT_RADIO_FRAME_MAX_SIZE];

    output_config_t const *sCurrentOutputPower = &(rgOutputPower[0]);
    uint32_t sRatOffset;

    inline uint_fast8_t rfCoreExecuteAbortCmd(void) { return (RFCDoorbellSendTo(CMDR_DIR_CMD(CMD_ABORT)) & 0xFF); }

    inline uint_fast8_t rfCoreExecutePingCmd(void) { return (RFCDoorbellSendTo(CMDR_DIR_CMD(CMD_PING)) & 0xFF); }

    uint_fast8_t rfCoreSendTransmitCmd(uint8_t *aPsdu, uint8_t aLen)
    {
        /* reset retry count */
        sTransmitRetryCount = 0;
        sCsmacaBackoffCmd = cCsmacaBackoffCmd;

        /* initialize the random state with a true random seed for the radio core's psudo rng */
        sCsmacaBackoffCmd.randomState = rand(); // -------------> otRandomNonCryptoGetUint16();
        sCsmacaBackoffCmd.pNextOp = (rfc_radioOp_t *)&sTransmitCmd;

        sTransmitCmd = cTransmitCmd;
        /* no need to look for an ack if the tx operation was stopped */
        sTransmitCmd.payloadLen = aLen;
        sTransmitCmd.pPayload = aPsdu;
        if (aPsdu[0] & IEEE802154_ACK_REQUEST)
        {
            /* setup the receive ack command to follow the tx command */
            sTransmitCmd.condition.rule = COND_STOP_ON_FALSE;
            sTransmitCmd.pNextOp = (rfc_radioOp_t *)&sTransmitRxAckCmd;

            sTransmitRxAckCmd = cTransmitRxAckCmd;
            sTransmitRxAckCmd.seqNo = aPsdu[IEEE802154_DSN_OFFSET];
        }
        return (RFCDoorbellSendTo((uint32_t)&sCsmacaBackoffCmd) & 0xFF);
    }

    uint_fast8_t rfCoreSendReceiveCmd(void)
    {
        sReceiveCmd.status = IDLE;
        return (RFCDoorbellSendTo((uint32_t)&sReceiveCmd) & 0xFF);
    }

    uint_fast16_t rfCoreSendEnableCmd(void)
    {
        uint8_t doorbellRet;
        bool interruptsWereDisabled;
        uint_fast16_t ret;

        /* turn on the clock line to the radio core */
        HWREGBITW(AON_RTC_BASE + AON_RTC_O_CTL, AON_RTC_CTL_RTC_UPD_EN_BITN) = 1;

        /* initialize the rat start command */
        sStartRatCmd = cStartRatCmd;
        sStartRatCmd.pNextOp = (rfc_radioOp_t *)&sRadioSetupCmd;
        sStartRatCmd.rat0 = sRatOffset;

        /* initialize radio setup command */
        sRadioSetupCmd = cRadioSetupCmd;
        /* initally set the radio tx power to the max */
        sRadioSetupCmd.txPower = sCurrentOutputPower->value;
        sRadioSetupCmd.pRegOverride = sIEEEOverrides;

        interruptsWereDisabled = IntMasterDisable();

        ////rfCoreApplyPatch();
        rf_patch_cpe_ieee_802_15_4();
        /* disable ram bus clocks */
        RFCDoorbellSendTo(CMDR_DIR_CMD_2BYTE(CC2652_RF_CMD0, 0));

        doorbellRet = (RFCDoorbellSendTo((uint32_t)&sStartRatCmd) & 0xFF);
        EXPECT_ACTION(CMDSTA_Done == doorbellRet, ret = doorbellRet);

        /* synchronously wait for the CM0 to stop executing */
        while ((HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) & IRQ_LAST_COMMAND_DONE) == 0x00)
            ;

        ret = sRadioSetupCmd.status;

    exit:
        if (!interruptsWereDisabled)
        {
            IntMasterEnable();
        }
        return ret;
    }

    uint_fast16_t rfCoreSendDisableCmd(void)
    {
        uint8_t doorbellRet;
        bool interruptsWereDisabled;
        uint_fast16_t ret;

        HWREGBITW(AON_RTC_BASE + AON_RTC_O_CTL, AON_RTC_CTL_RTC_UPD_EN_BITN) = 1;

        /* initialize the command to power down the frequency synth */
        sFsPowerdownCmd = cFsPowerdownCmd;
        sFsPowerdownCmd.pNextOp = (rfc_radioOp_t *)&sStopRatCmd;

        sStopRatCmd = cStopRatCmd;

        interruptsWereDisabled = IntMasterDisable();

        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = ~IRQ_LAST_COMMAND_DONE;

        doorbellRet = (RFCDoorbellSendTo((uint32_t)&sFsPowerdownCmd) & 0xFF);
        EXPECT_ACTION(CMDSTA_Done == doorbellRet, ret = doorbellRet);

        /* synchronously wait for the CM0 to stop */
        while ((HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) & IRQ_LAST_COMMAND_DONE) == 0x00)
            ;

        ret = sStopRatCmd.status;

        if (sStopRatCmd.status == DONE_OK)
        {
            sRatOffset = sStopRatCmd.rat0;
        }

    exit:

        if (!interruptsWereDisabled)
        {
            IntMasterEnable();
        }

        return ret;
    }

    uint_fast8_t rfCoreClearReceiveQueue(dataQueue_t *aQueue)
    {
        /* memset skipped because sClearReceiveQueueCmd has only 2 members and padding */
        sClearReceiveQueueCmd.commandNo = CMD_CLEAR_RX;
        sClearReceiveQueueCmd.pQueue = aQueue;
        return (RFCDoorbellSendTo((uint32_t)&sClearReceiveQueueCmd) & 0xFF);
    }

    void rfProcessReceiveQueue(void)
    {
        rfc_ieeeRxCorrCrc_t *crcCorr;
        rfc_dataEntryGeneral_t *curEntry, *startEntry;
        uint8_t rssi;

        startEntry = (rfc_dataEntryGeneral_t *)sRxDataQueue.pCurrEntry;
        curEntry = startEntry;

        /* loop through receive queue */
        do
        {
            uint8_t *payload = &(curEntry->data);

            if (curEntry->status == DATA_ENTRY_FINISHED)
            {
                uint8_t len;
                RadioError receiveError;
                RadioFrame receiveFrame;

                /* get the information appended to the end of the frame. This array access looks like it is a fencepost error, but the first byte is the number of bytes that follow. */
                len = payload[0];
                crcCorr = (rfc_ieeeRxCorrCrc_t *)&payload[len];
                rssi = payload[len - 1];

                if (crcCorr->status.bCrcErr == 0 && (len - 2) < OT_RADIO_FRAME_MAX_SIZE)
                {
                    receiveFrame.mLength = len;
                    receiveFrame.mPsdu = &(payload[1]);
                    receiveFrame.mChannel = sReceiveCmd.channel;
                    receiveFrame.mInfo.mRxInfo.mRssi = rssi;
                    receiveFrame.mInfo.mRxInfo.mLqi = crcCorr->status.corr;
                    receiveError = ERROR_RADIO_NONE;
                }
                else
                {
                    receiveError = ERROR_RADIO_FCS;
                }

                if ((receiveFrame.mPsdu[0] & IEEE802154_FRAME_TYPE_MASK) == IEEE802154_FRAME_TYPE_ACK)
                {
                    if (sState == cc2652_stateTransmit && sTxCmdChainDone &&
                        receiveFrame.mPsdu[IEEE802154_DSN_OFFSET] == sTransmitFrame.mPsdu[IEEE802154_DSN_OFFSET])
                    {
                        /* we found the ACK packet */
                        sState = cc2652_stateReceive;
                        CB_RadioTxDone(&sTransmitFrame, &receiveFrame, receiveError); //

                        sTransmitError = ERROR_RADIO_NONE;
                        sTxCmdChainDone = false;
                    }
                }
                else
                {
                    //rfProcessReceiveDone(&receiveFrame, receiveError);
                    // TODO Set this flag only when the packet is really acknowledged with frame pending set.
                    // See https://github.com/openthread/openthread/pull/3785
                    receiveFrame.mInfo.mRxInfo.mAckedWithFramePending = true;
                    CB_RadioReceiveDone(&receiveFrame, receiveError);
                }

                curEntry->status = DATA_ENTRY_PENDING;
                break;
            }
            else if (curEntry->status == DATA_ENTRY_UNFINISHED)
            {
                curEntry->status = DATA_ENTRY_PENDING;
            }

            curEntry = (rfc_dataEntryGeneral_t *)(curEntry->pNextEntry);
        } while (curEntry != startEntry);
    }

    static void RFCCPE1IntHandler(void)
    {
        /* Clear INTERNAL_ERROR interrupt flag */
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = 0x7FFFFFFF;
    }

    static void RFCCPE0IntHandler(void)
    {
        if (HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) & IRQ_LAST_COMMAND_DONE)
        {
            HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = ~IRQ_LAST_COMMAND_DONE;
            if (sState == cc2652_stateReceive && sReceiveCmd.status != ACTIVE && sReceiveCmd.status != IEEE_SUSPENDED)
            {
                /* the rx command was probably aborted to change the channel */
                sState = cc2652_stateSleep;
            }
            else if (sState == cc2652_stateEdScan)
            {
                sState = cc2652_stateSleep;
            }
        }

        if (HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) & IRQ_LAST_FG_COMMAND_DONE)
        {
            HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = ~IRQ_LAST_FG_COMMAND_DONE;
            if (sState == cc2652_stateTransmit)
            {
                if (sTransmitCmd.pPayload[0] & IEEE802154_ACK_REQUEST)
                {
                    /* we are looking for an ack */
                    switch (sTransmitRxAckCmd.status)
                    {
                    case IEEE_DONE_TIMEOUT:
                        if (sTransmitRetryCount < IEEE802154_MAC_MAX_FRAMES_RETRIES)
                        {
                            /* re-submit the tx command chain */
                            sTransmitRetryCount++;
                            RFCDoorbellSendTo((uint32_t)&sCsmacaBackoffCmd);
                        }
                        else
                        {
                            sTransmitError = ERROR_RADIO_NO_ACK;
                            /* signal polling function we are done transmitting, we failed to send the packet */
                            sTxCmdChainDone = true;
                        }
                        break;

                    case IEEE_DONE_ACK:
                        sTransmitError = ERROR_RADIO_NONE;
                        /* signal polling function we are done transmitting */
                        sTxCmdChainDone = true;
                        break;

                    case IEEE_DONE_ACKPEND:
                        sTransmitError = ERROR_RADIO_NONE;
                        /* signal polling function we are done transmitting */
                        sTxCmdChainDone = true;
                        break;

                    default:
                        sTransmitError = ERROR_RADIO_FAILED;
                        /* signal polling function we are done transmitting */
                        sTxCmdChainDone = true;
                        break;
                    }
                }
                else
                {
                    /* The TX command was either stopped or we are not looking for an ack */
                    switch (sTransmitCmd.status)
                    {
                    case IEEE_DONE_OK:
                        sTransmitError = ERROR_RADIO_NONE;
                        break;

                    case IEEE_DONE_TIMEOUT:
                        sTransmitError = ERROR_RADIO_CHANNEL_ACCESS_FAILURE;
                        break;

                    case IEEE_ERROR_NO_SETUP:
                    case IEEE_ERROR_NO_FS:
                    case IEEE_ERROR_SYNTH_PROG:
                        sTransmitError = ERROR_RADIO_INVALID_STATE;
                        break;

                    case IEEE_ERROR_TXUNF:
                        sTransmitError = ERROR_RADIO_NO_BUFS;
                        break;

                    default:
                        sTransmitError = ERROR_RADIO_FAILED;
                        break;
                    }

                    /* signal polling function we are done transmitting */
                    sTxCmdChainDone = true;
                }
            }
        }
    }

    void rfCoreSetupInt(void)
    {
        bool interruptsWereDisabled;
        EXPECT(PRCMRfReady());
        interruptsWereDisabled = IntMasterDisable();
        /* Set all interrupt channels to CPE0 channel, error to CPE1 */
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEISL) = IRQ_INTERNAL_ERROR;
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIEN) = IRQ_LAST_COMMAND_DONE | IRQ_LAST_FG_COMMAND_DONE;
        IntRegister(INT_RFC_CPE_0, RFCCPE0IntHandler);
        IntRegister(INT_RFC_CPE_1, RFCCPE1IntHandler);
        IntPendClear(INT_RFC_CPE_0);
        IntPendClear(INT_RFC_CPE_1);
        IntEnable(INT_RFC_CPE_0);
        IntEnable(INT_RFC_CPE_1);
        if (!interruptsWereDisabled)
        {
            IntMasterEnable();
        }
    exit:
        return;
    }

    void rfCoreStopInt(void)
    {
        bool interruptsWereDisabled;
        interruptsWereDisabled = IntMasterDisable();
        /* clear and disable interrupts */
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = 0x0;
        HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIEN) = 0x0;
        IntUnregister(INT_RFC_CPE_0);
        IntUnregister(INT_RFC_CPE_1);
        IntPendClear(INT_RFC_CPE_0);
        IntPendClear(INT_RFC_CPE_1);
        IntDisable(INT_RFC_CPE_0);
        IntDisable(INT_RFC_CPE_1);
        if (!interruptsWereDisabled)
        {
            IntMasterEnable();
        }
    }

    void rfCorePowerOff(void)
    {
        rfCoreStopInt();

#if 1
        soc_power_off_domain(PRCM_DOMAIN_RFCORE);
#else
        PRCMDomainDisable(PRCM_DOMAIN_RFCORE);
        PRCMLoadSet();
        while (!PRCMLoadGet())
            ;
        PRCMPowerDomainOff(PRCM_DOMAIN_RFCORE);
        while (PRCMPowerDomainsAllOn(PRCM_DOMAIN_RFCORE) != PRCM_DOMAIN_POWER_OFF)
            ;
#endif

        if (OSCClockSourceGet(OSC_SRC_CLK_HF) != OSC_RCOSC_HF)
        {
            /* Request to switch to the RC osc for low power mode. */
            OSCClockSourceSet(OSC_SRC_CLK_HF, OSC_RCOSC_HF);
            /* Switch the HF clock source (cc26xxware executes this from ROM) */
            OSCHfSourceSwitch();
        }
    }

    uint_fast8_t rfCorePowerOn(void)
    {
        bool interruptsWereDisabled;
        bool oscSourceSwitch = false;

        /* Request the HF XOSC as the source for the HF clock. Needed before we can use the FS. This will only request, it will _not_ perform the switch. */
        if (OSCClockSourceGet(OSC_SRC_CLK_HF) != OSC_XOSC_HF)
        {
            /* Request to switch to the crystal to enable radio operation. It takes a while for the XTAL to be ready so instead of performing the actual 
            switch, we do other stuff while the XOSC is getting ready. */
            OSCClockSourceSet(OSC_SRC_CLK_HF, OSC_XOSC_HF);
            oscSourceSwitch = true;
        }

        /* Set of RF Core data queue. Circular buffer, no last entry */
        sRxDataQueue.pCurrEntry = sRxBuf0;
        sRxDataQueue.pLastEntry = NULL;

        //void rfCoreInitBufs(void)
        {
            rfc_dataEntry_t *entry;
            memset(sRxBuf0, 0x00, sizeof(sRxBuf0));
            memset(sRxBuf1, 0x00, sizeof(sRxBuf1));
            memset(sRxBuf2, 0x00, sizeof(sRxBuf2));
            memset(sRxBuf3, 0x00, sizeof(sRxBuf3));

            entry = (rfc_dataEntry_t *)sRxBuf0;
            entry->pNextEntry = sRxBuf1;
            entry->config.lenSz = DATA_ENTRY_LENSZ_BYTE;
            entry->length = sizeof(sRxBuf0) - sizeof(rfc_dataEntry_t);

            entry = (rfc_dataEntry_t *)sRxBuf1;
            entry->pNextEntry = sRxBuf2;
            entry->config.lenSz = DATA_ENTRY_LENSZ_BYTE;
            entry->length = sizeof(sRxBuf1) - sizeof(rfc_dataEntry_t);

            entry = (rfc_dataEntry_t *)sRxBuf2;
            entry->pNextEntry = sRxBuf3;
            entry->config.lenSz = DATA_ENTRY_LENSZ_BYTE;
            entry->length = sizeof(sRxBuf2) - sizeof(rfc_dataEntry_t);

            entry = (rfc_dataEntry_t *)sRxBuf3;
            entry->pNextEntry = sRxBuf0;
            entry->config.lenSz = DATA_ENTRY_LENSZ_BYTE;
            entry->length = sizeof(sRxBuf3) - sizeof(rfc_dataEntry_t);

            memset(&sTransmitFrame, 0x00, sizeof(RadioFrame));
            sTransmitFrame.mPsdu = sTransmitPsdu;
            //sTransmitFrame.mLength = 0;
        }

        /* Trigger a switch to the XOSC, so that we can subsequently use the RF FS This will block until the XOSC is actually ready, but give how we
           requested it early on, this won't be too long a wait. This should be done before starting the RAT. */
        if (oscSourceSwitch)
        {
            /* Block until the high frequency clock source is ready */
            while (!OSCHfSourceReady())
                ;
            /* Switch the HF clock source (cc26xxware executes this from ROM) */
            OSCHfSourceSwitch();
        }

        interruptsWereDisabled = IntMasterDisable();

/* Enable RF Core power domain */
#if 1
        soc_power_on_domain(PRCM_DOMAIN_RFCORE);
#else
        PRCMPowerDomainOn(PRCM_DOMAIN_RFCORE);
        while (PRCMPowerDomainsAllOn(PRCM_DOMAIN_RFCORE) != PRCM_DOMAIN_POWER_ON)
            ;
        PRCMDomainEnable(PRCM_DOMAIN_RFCORE);
        PRCMLoadSet();
        while (!PRCMLoadGet())
            ;
#endif

        rfCoreSetupInt();

        if (!interruptsWereDisabled)
        {
            IntMasterEnable();
        }

        /* Let CPE boot */
        RFCClockEnable();

        /* Enable ram clocks for patches */
        RFCDoorbellSendTo(CMDR_DIR_CMD_2BYTE(CC2652_RF_CMD0, RFC_PWR_PWMCLKEN_MDMRAM | RFC_PWR_PWMCLKEN_RFERAM));

        /* Send ping (to verify RFCore is ready and alive) */
        return rfCoreExecutePingCmd();
    }

private:
    RadioFrame sTransmitFrame; // active transmit frame = getTransmitBuffer()

    void CB_RadioTxStarted(RadioFrame *aFrame)
    {
        //RADIO_PRINTF("[RADIO] %s()\n", __func__);
        if (cbTxStarted)
            cbTxStarted(aFrame);
    }

    void CB_RadioTxDone(RadioFrame *aFrame, RadioFrame *aAckFrame, RadioError aError)
    {
        //RADIO_PRINTF("[RADIO] %s( %d )\n", __func__, (int)aError);
        if (cbTxDone)
            cbTxDone(aFrame, aAckFrame, aError);
    }

    void CB_RadioReceiveDone(RadioFrame *aFrame, RadioError aError)
    {
        //RADIO_PRINTF("[RADIO] %s()\n", __func__);
        //DUMP("PSDU", aFrame->mPsdu, aFrame->mLength);
        if (ERROR_RADIO_NONE == aError && cbRxDone)
            cbRxDone(aFrame);
    }

    RadioError RadioTransmit(RadioFrame *aFrame)
    {
        RadioError error = ERROR_RADIO_BUSY;
        if (sState == cc2652_stateReceive)
        {
            sState = cc2652_stateTransmit;
            /* removing 2 bytes of CRC placeholder because we generate that in hardware */
            EXPECT_ACTION(rfCoreSendTransmitCmd(aFrame->mPsdu, aFrame->mLength - 2) == CMDSTA_Done, error = ERROR_RADIO_FAILED);
            error = ERROR_RADIO_NONE;
            sTransmitError = ERROR_RADIO_NONE;
            sTxCmdChainDone = false;
            CB_RadioTxStarted(aFrame); // callback to user
        }

    exit:
        return error;
    }

    RadioError RadioReceive(uint8_t aChannel)
    {
        RadioError error = ERROR_RADIO_BUSY;
        if (sState == cc2652_stateSleep)
        {
            sState = cc2652_stateReceive;
            /* initialize the receive command XXX: no memset here because we assume init has been called and we may have changed some values in the rx command */
            sReceiveCmd.channel = aChannel;
            EXPECT_ACTION(rfCoreSendReceiveCmd() == CMDSTA_Done, error = ERROR_RADIO_FAILED);
            error = ERROR_RADIO_NONE;
        }
        else if (sState == cc2652_stateReceive)
        {
            if (sReceiveCmd.status == ACTIVE && sReceiveCmd.channel == aChannel)
            {
                /* we are already running on the right channel */
                sState = cc2652_stateReceive;
                error = ERROR_RADIO_NONE;
            }
            else
            {
                /* we have either not fallen back into our receive command or we are running on the wrong channel. Either way assume the caller correctly called us and abort all running commands. */
                EXPECT_ACTION(rfCoreExecuteAbortCmd() == CMDSTA_Done, error = ERROR_RADIO_FAILED);
                /* any frames in the queue will be for the old channel */
                EXPECT_ACTION(rfCoreClearReceiveQueue(&sRxDataQueue) == CMDSTA_Done, error = ERROR_RADIO_FAILED);
                sReceiveCmd.channel = aChannel;
                EXPECT_ACTION(rfCoreSendReceiveCmd() == CMDSTA_Done, error = ERROR_RADIO_FAILED);
                sState = cc2652_stateReceive;
                error = ERROR_RADIO_NONE;
            }
        }

    exit:
        return error;
    }

    RadioError RadioDisable(void)
    {
        RadioError error = ERROR_RADIO_BUSY;
        if (sState == cc2652_stateDisabled)
        {
            error = ERROR_RADIO_NONE;
        }
        else if (sState == cc2652_stateSleep)
        {
            rfCoreSendDisableCmd();
            /* we don't want to fail if this command string doesn't work, just turn off the whole core */
            rfCorePowerOff();
            sState = cc2652_stateDisabled;
            error = ERROR_RADIO_NONE;
        }
        return error;
    }

    RadioError RadioEnable(void)
    {
        RadioError error = ERROR_RADIO_BUSY;
        if (sState == cc2652_stateSleep)
        {
            error = ERROR_RADIO_NONE;
        }
        else if (sState == cc2652_stateDisabled)
        {
            EXPECT_ACTION(rfCorePowerOn() == CMDSTA_Done, error = ERROR_RADIO_FAILED);
            EXPECT_ACTION(rfCoreSendEnableCmd() == DONE_OK, error = ERROR_RADIO_FAILED);
            sState = cc2652_stateSleep;
            error = ERROR_RADIO_NONE;
        }
    exit:
        if (error == ERROR_RADIO_FAILED)
        {
            rfCorePowerOff();
            sState = cc2652_stateDisabled;
        }
        return error;
    }

    inline bool RadioIsEnabled(void) { return (sState != cc2652_stateDisabled); }

    RadioError RadioSleep(void)
    {
        RadioError error = ERROR_RADIO_BUSY;
        if (sState == cc2652_stateSleep)
        {
            error = ERROR_RADIO_NONE;
        }
        else if (sState == cc2652_stateReceive)
        {
            if (rfCoreExecuteAbortCmd() != CMDSTA_Done)
            {
                error = ERROR_RADIO_BUSY;
            }
            else
            {
                sState = cc2652_stateSleep;
                error = ERROR_RADIO_NONE;
            }
        }
        return error;
    }

    void RadioSetPanId(uint16_t aPanid)
    {

        /* XXX: if the pan id is the broadcast pan id (0xFFFF) the auto ack will not work. This is due to the design of the CM0 and follows IEEE 802.15.4 */
        if (sState == cc2652_stateReceive)
        {
            EXPECT(rfCoreExecuteAbortCmd() == CMDSTA_Done);
            sReceiveCmd.localPanID = aPanid;
            EXPECT(rfCoreClearReceiveQueue(&sRxDataQueue) == CMDSTA_Done);
            EXPECT(rfCoreSendReceiveCmd() == CMDSTA_Done);
            /* the interrupt from abort changed our state to sleep */
            sState = cc2652_stateReceive;
        }
        else if (sState != cc2652_stateTransmit)
        {
            sReceiveCmd.localPanID = aPanid;
        }
    exit:
        return;
    }

    void RadioSetShortAddress(uint16_t aAddress)
    {
        if (sState == cc2652_stateReceive)
        {
            EXPECT(rfCoreExecuteAbortCmd() == CMDSTA_Done);
            sReceiveCmd.localShortAddr = aAddress;
            EXPECT(rfCoreClearReceiveQueue(&sRxDataQueue) == CMDSTA_Done);
            EXPECT(rfCoreSendReceiveCmd() == CMDSTA_Done);
            /* the interrupt from abort changed our state to sleep */
            sState = cc2652_stateReceive;
        }
        else if (sState != cc2652_stateTransmit)
        {
            sReceiveCmd.localShortAddr = aAddress;
        }
    exit:
        return;
    }

    void RadioSetExtendedAddress(const ExtAddress_t *aAddress)
    {
        if (sState == cc2652_stateReceive)
        {
            EXPECT(rfCoreExecuteAbortCmd() == CMDSTA_Done);
            sReceiveCmd.localExtAddr = ReadUint64Le(aAddress->m8);
            EXPECT(rfCoreClearReceiveQueue(&sRxDataQueue) == CMDSTA_Done);
            EXPECT(rfCoreSendReceiveCmd() == CMDSTA_Done);
            sState = cc2652_stateReceive;
        }
        else if (sState != cc2652_stateTransmit)
        {
            sReceiveCmd.localExtAddr = ReadUint64Le(aAddress->m8);
        }
    exit:
        return;
    }

    RadioError RadioSetTransmitPower(int8_t aPower)
    {
        unsigned int i;
        output_config_t const *powerCfg = &(rgOutputPower[0]);
        for (i = 1; i < OUTPUT_CONFIG_COUNT; i++)
        {
            if (rgOutputPower[i].dbm >= aPower)
            {
                powerCfg = &(rgOutputPower[i]);
            }
            else
            {
                break;
            }
        }
        sCurrentOutputPower = powerCfg;
        return ERROR_RADIO_NONE;
    }

    uint64_t ReadUint64Le(const uint8_t *aSource)
    {
        uint64_t value = 0;
        value |= (uint64_t)aSource[0];
        value |= ((uint64_t)aSource[1]) << 8;
        value |= ((uint64_t)aSource[2]) << 16;
        value |= ((uint64_t)aSource[3]) << 24;
        value |= ((uint64_t)aSource[4]) << 32;
        value |= ((uint64_t)aSource[5]) << 40;
        value |= ((uint64_t)aSource[6]) << 48;
        value |= ((uint64_t)aSource[7]) << 56;
        return value;
    }

    void GetIeeeEui64(uint8_t *aIeeeEui64)
    {

        uint8_t *eui64;
        unsigned int i;

        /* The IEEE MAC address can be stored two places. We check the Customer Configuration was not set before defaulting to the Factory Configuration. */
        eui64 = (uint8_t *)(CCFG_BASE + CCFG_O_IEEE_MAC_0);

        for (i = 0; i < OT_EXT_ADDRESS_SIZE; i++)
        {
            if (eui64[i] != CC2652_UNKNOWN_EUI64)
            {
                break;
            }
        }
        if (i >= OT_EXT_ADDRESS_SIZE)
        {
            /* The ccfg address was all 0xFF, switch to the fcfg */
            eui64 = (uint8_t *)(FCFG1_BASE + FCFG1_O_MAC_15_4_0);
        }
        /*
     * The IEEE MAC address is stored in network byte order.  The caller seems
     * to want the address stored in little endian format, which is backwards
     * of the conventions setup by @ref otPlatRadioSetExtendedAddress.
     * otPlatRadioSetExtendedAddress assumes that the address being passed to
     * it is in network byte order, so the caller of
     * otPlatRadioSetExtendedAddress must swap the endianness before calling.
     *
     * It may be easier to have the caller of this function store the IEEE
     * address in network byte order.
     */
        for (i = 0; i < OT_EXT_ADDRESS_SIZE; i++)
        {
            aIeeeEui64[i] = eui64[(OT_EXT_ADDRESS_SIZE - 1) - i];
        }
    }

    /* User settings */
    uint16_t _PanID;
    uint16_t _Address;
    uint8_t _Channel;
    int8_t _Power;
    HandleTxStarted cbTxStarted;
    HandleTxDone cbTxDone;
    HandleReceiveDone cbRxDone;

    uint8_t ExtendedAddress[OT_EXT_ADDRESS_SIZE];

public:
    LRadio(uint16_t aPanid, uint16_t aAddress, uint8_t aChannel = CC2652_CHANNEL_MIN, int8_t aPower = 0 /* dbm see rgOutputPower[] table */)
    {
        //void cc2652RadioInit(void)
        ////void rfCoreInitReceiveParams(void)
        memcpy(&sReceiveCmd, &cReceiveCmd, sizeof(rfc_CMD_IEEE_RX_t));
        sReceiveCmd.pRxQ = &sRxDataQueue;
        sReceiveCmd.pOutput = &sRfStats;
        sReceiveCmd.numShortEntries = CC2652_SHORTADD_SRC_MATCH_NUM;
        sReceiveCmd.pShortEntryList = (uint32_t *)&sSrcMatchShortData;
        sReceiveCmd.numExtEntries = CC2652_EXTADD_SRC_MATCH_NUM;
        sReceiveCmd.pExtEntryList = (uint32_t *)&sSrcMatchExtData;
        sRatOffset = 0;

        cbTxStarted = NULL;
        cbTxDone = NULL;
        cbRxDone = NULL;
        _PanID = aPanid;
        _Address = aAddress;
        _Power = aPower;
        setChannel(aChannel);
        GetIeeeEui64(ExtendedAddress);
    }

    ~LRadio() { RadioDisable(); }

    void setup(HandleReceiveDone callbackRxDone, HandleTxDone callbackTxDone, HandleTxStarted callbackTxStarted = NULL)
    {
        cbTxStarted = callbackTxStarted;
        cbTxDone = callbackTxDone;
        cbRxDone = callbackRxDone;
    }

    inline void end() { RadioDisable(); }

    bool begin()
    {
        RadioError res = ERROR_RADIO_NONE;
        if (false == RadioIsEnabled())
        {
            RadioSetPanId(_PanID);
            RadioSetShortAddress(_Address);
            if (ERROR_RADIO_NONE == (res = RadioSetTransmitPower(_Power)))
                if (ERROR_RADIO_NONE == (res = RadioEnable())) // power on
                    res = RadioReceive(_Channel);              // goto rx mode
        }
        RADIO_PRINTF("[RADIO] %s( %s )\n", __func__, res == ERROR_RADIO_NONE ? "DONE" : "ERROR");
        return res == ERROR_RADIO_NONE;
    }

    void process(void)
    {
        if (sState == cc2652_stateReceive || sState == cc2652_stateTransmit)
        {
            rfProcessReceiveQueue();
        }

        if (sTxCmdChainDone)
        {
            if (sState == cc2652_stateTransmit)
            {
                /* we are not looking for an ACK packet, or failed */
                sState = cc2652_stateReceive;
                CB_RadioTxDone(&sTransmitFrame, NULL, sTransmitError); //
            }
            sTransmitError = ERROR_RADIO_NONE;
            sTxCmdChainDone = false;
        }
    }

    inline RadioError enable() { return RadioEnable(); }

    inline RadioError disable() { return RadioDisable(); }

    inline RadioError sleep() { return RadioSleep(); }

    inline bool wakeup() // TODO ?
    {
        switch (sState)
        {
        case cc2652_stateDisabled:
            return begin();
            break;
        case cc2652_stateSleep:
            return ERROR_RADIO_NONE == RadioReceive(_Channel);
        default:
            return true;
        }
    }

    inline uint16_t getPanID() { return _PanID; }

    inline void setPanID(uint16_t aPanid)
    {
        _PanID = aPanid;
        RadioSetPanId(aPanid);
    }

    inline uint16_t getShortAddress() { return _Address; }

    inline void setShortAddress(uint16_t aAddress)
    {
        _Address = aAddress;
        RadioSetShortAddress(aAddress);
    }

    inline int8_t getTransmitPower() { return _Power; }

    RadioError setTransmitPower(int8_t aPower)
    {

        RadioError res;
        if (ERROR_RADIO_NONE == (res = RadioSetTransmitPower(aPower)))
            _Power = aPower;
        return res;
    }

    void setExtendedAddress(uint8_t addr[OT_EXT_ADDRESS_SIZE])
    {
        if (addr)
            memcpy(ExtendedAddress, addr, OT_EXT_ADDRESS_SIZE);
        RadioSetExtendedAddress((ExtAddress_t *)ExtendedAddress);
    }

    inline uint8_t *getExtendedAddress() { return ExtendedAddress; }

    inline uint64_t getEUI64() { return ReadUint64Le(ExtendedAddress); }

    inline int8_t getRssi() { return sRfStats.maxRssi; }

    inline uint8_t getChannel() { return _Channel; }

    void setChannel(uint8_t aChannel)
    {
        _Channel = aChannel;
        if (_Channel < CC2652_CHANNEL_MIN)
            _Channel = CC2652_CHANNEL_MIN;
        if (_Channel > CC2652_CHANNEL_MAX)
            _Channel = CC2652_CHANNEL_MAX;
    }

    /* go to rx mode */
    inline RadioError receive() { return RadioReceive(_Channel); }

    inline RadioFrame *getTransmitBuffer() { return &sTransmitFrame; }

    inline RadioError transmit(RadioFrame *aFrame) { return (aFrame) ? RadioTransmit(aFrame) : ERROR_RADIO_INVALID_PARAM; }

    RadioError transmitWait(RadioFrame *aFrame, uint32_t timeout_ms = 1000)
    {
        RadioError res = ERROR_RADIO_INVALID_PARAM;
        HandleTxDone backupTxDone = cbTxDone;
        if (aFrame)
        {
            cbTxDone = NULL; // disable user callback
            if (ERROR_RADIO_NONE == (res = transmit(aFrame)))
            {
                res = ERROR_RADIO_TIMEOUT;
                aFrame->mUser = &res;
                uint32_t start = millis();
                do
                {
                    process();
                    if (ERROR_RADIO_TIMEOUT != (res = *(RadioError *)aFrame->mUser))
                        break;
                } while (millis() - start < timeout_ms);
            }
            cbTxDone = backupTxDone; // enable user callback
        }
        return res;
    }

    RadioError write(uint8_t *buffer, uint32_t size, uint32_t timeout_ms = 1000)
    {
        RadioError res = ERROR_RADIO_INVALID_PARAM;
        if (buffer && size)
        {
            RadioFrame frame;
            memset(&frame, 0, sizeof(RadioFrame));
            frame.mPsdu = buffer;
            frame.mLength = size + 2;
            if (timeout_ms)
                res = transmitWait(&frame, timeout_ms);
            else
                res = transmit(&frame);
        }
        return res;
    }
};