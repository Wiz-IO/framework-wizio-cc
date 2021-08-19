#include "LRADIO_DEF.h"

const rfc_CMD_IEEE_ED_SCAN_t cEdScanCmd =
    {
        .commandNo = CMD_IEEE_ED_SCAN,
        .startTrigger =
            {
                .triggerType = TRIG_NOW,
            },
        .condition = {
            .rule = COND_NEVER,
        },
        .ccaOpt = {
            .ccaEnEnergy = 1,
            .ccaEnCorr = 1,
            .ccaEnSync = 1,
            .ccaCorrOp = 1,
            .ccaSyncOp = 0,
            .ccaCorrThr = 3,
        },
        .ccaRssiThr = -90,
        .endTrigger = {
            .triggerType = TRIG_REL_START,
            .pastTrig = 1,
        },
};

const rfc_CMD_IEEE_CSMA_t cCsmacaBackoffCmd =
    {
        .commandNo = CMD_IEEE_CSMA,
        .status = IDLE,
        .startTrigger =
            {
                .triggerType = TRIG_NOW,
            },
        .condition = {
            .rule = COND_ALWAYS,
        },
        .macMaxBE = IEEE802154_MAC_MAX_BE,
        .macMaxCSMABackoffs = IEEE802154_MAC_MAX_CSMA_BACKOFFS,
        .csmaConfig = {
            .initCW = 1,
            .bSlotted = 0,
            .rxOffMode = 0,
        },
        .NB = 0,
        .BE = IEEE802154_MAC_MIN_BE,
        .remainingPeriods = 0,
        .endTrigger = {
            .triggerType = TRIG_NEVER,
        },
        .endTime = 0x00000000,
};

const rfc_CMD_IEEE_TX_t cTransmitCmd =
    {
        .commandNo = CMD_IEEE_TX,
        .status = IDLE,
        .startTrigger =
            {
                .triggerType = TRIG_NOW,
            },
        .condition = {
            .rule = COND_NEVER,
        },
        .pNextOp = NULL,
};

const rfc_CMD_IEEE_RX_ACK_t cTransmitRxAckCmd =
    {
        .commandNo = CMD_IEEE_RX_ACK,
        .status = IDLE,
        .startTrigger =
            {
                .triggerType = TRIG_NOW,
            },
        .endTrigger =
            {
                .triggerType = TRIG_REL_START,
                .pastTrig = 1,
            },
        .condition = {
            .rule = COND_NEVER,
        },
        .pNextOp = NULL,
        /* number of RAT ticks to wait before claiming we haven't received an ack */
        .endTime = ((IEEE802154_MAC_ACK_WAIT_DURATION * CC2652_RAT_TICKS_PER_SEC) / IEEE802154_SYMBOLS_PER_SEC),
};

const rfc_CMD_IEEE_RX_t cReceiveCmd =
    {
        .commandNo = CMD_IEEE_RX,
        .status = IDLE,
        .pNextOp = NULL,
        .startTime = 0u,
        .startTrigger =
            {
                .triggerType = TRIG_NOW,
            },
        .condition = {
            .rule = COND_NEVER,
        },
        .channel = CC2652_CHANNEL_MIN,
        .rxConfig = {
            .bAutoFlushCrc = 1,
            .bAutoFlushIgn = 0,
            .bIncludePhyHdr = 0,
            .bIncludeCrc = 0,
            .bAppendRssi = 1,
            .bAppendCorrCrc = 1,
            .bAppendSrcInd = 0,
            .bAppendTimestamp = 0,
        },
        .frameFiltOpt = {
            .frameFiltEn = 1,
            .frameFiltStop = 1,
            .autoAckEn = 1,
            .slottedAckEn = 0,
            .autoPendEn = 0,
            .defaultPend = 0,
            .bPendDataReqOnly = 0,
            .bPanCoord = 0,
            .maxFrameVersion = 3,
            .bStrictLenFilter = 1,
        },
        .frameTypes = {
            .bAcceptFt0Beacon = 1,
            .bAcceptFt1Data = 1,
            .bAcceptFt2Ack = 1,
            .bAcceptFt3MacCmd = 1,
            .bAcceptFt4Reserved = 1,
            .bAcceptFt5Reserved = 1,
            .bAcceptFt6Reserved = 1,
            .bAcceptFt7Reserved = 1,
        },
        .ccaOpt = {
            .ccaEnEnergy = 1,
            .ccaEnCorr = 1,
            .ccaEnSync = 1,
            .ccaCorrOp = 1,
            .ccaSyncOp = 0,
            .ccaCorrThr = 3,
        },
        .ccaRssiThr = -90,
        .endTrigger = {
            .triggerType = TRIG_NEVER,
        },
        .endTime = 0u,
};

const rfc_CMD_SYNC_START_RAT_t cStartRatCmd =
    {
        .commandNo = CMD_SYNC_START_RAT,
        .startTrigger =
            {
                .triggerType = TRIG_NOW,
            },
        .condition = {
            .rule = COND_STOP_ON_FALSE,
        },
};

const rfc_CMD_RADIO_SETUP_t cRadioSetupCmd =
    {
        .commandNo = CMD_RADIO_SETUP,
        .startTrigger =
            {
                .triggerType = TRIG_NOW,
            },
        .condition = {
            .rule = COND_NEVER,
        },
        .mode = 1, // IEEE 802.15.4 mode
};

const rfc_CMD_FS_POWERDOWN_t cFsPowerdownCmd =
    {
        .commandNo = CMD_FS_POWERDOWN,
        .startTrigger =
            {
                .triggerType = TRIG_NOW,
            },
        .condition = {
            .rule = COND_ALWAYS,
        },
};

const rfc_CMD_SYNC_STOP_RAT_t cStopRatCmd =
    {
        .commandNo = CMD_SYNC_STOP_RAT,
        .startTrigger =
            {
                .triggerType = TRIG_NOW,
            },
        .condition = {
            .rule = COND_NEVER,
        },
};

uint32_t sIEEEOverrides[] = {
    // override_ieee_802_15_4.xml
    // DC/DC regulator: In Tx, use DCDCCTL5[3:0]=0x3 (DITHER_EN=0 and IPEAK=3).
    (uint32_t)0x00F388D3,
    // Rx: Set LNA bias current offset to +15 to saturate trim to max (default: 0)
    (uint32_t)0x000F8883,
    (uint32_t)0xFFFFFFFF,
};

const output_config_t rgOutputPower[15] = {
    {5, 0x941e},   //
    {4, 0x6c16},   //
    {3, 0x5411},   //
    {2, 0x440d},   //
    {1, 0x385c},   //
    {0, 0x3459},   //
    {-3, 0x2851},  //
    {-5, 0x224e},  //
    {-6, 0x204d},  //
    {-9, 0x0a8d},  //
    {-10, 0x168c}, //
    {-12, 0x10a8}, //
    {-15, 0xc88c}, //
    {-18, 0x06c9}, //
    {-21, 0x06c7}, //
};