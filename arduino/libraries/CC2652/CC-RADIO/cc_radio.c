/*
 *  Copyright (c) 2017, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file implements the OpenThread platform abstraction for radio communication.
 *
 */

#include <interface.h>

#include "cc_radio.h"
#include "cc2652_radio.h"
#include <driverlib/chipinfo.h>
#include <driverlib/osc.h>
#include <driverlib/prcm.h>
#include <driverlib/rf_common_cmd.h>
#include <driverlib/rf_data_entry.h>
#include <driverlib/rf_ieee_cmd.h>
#include <driverlib/rf_ieee_mailbox.h>
#include <driverlib/rf_mailbox.h>
#include <driverlib/rfc.h>
#include <inc/hw_ccfg.h>
#include <inc/hw_fcfg1.h>
#include <inc/hw_memmap.h>
#include <inc/hw_prcm.h>
#include <inc/hw_rfc_pwr.h>
#include <rf_patches/rf_patch_cpe_ieee_802_15_4.h>

#define RADIO_PRINTF printf

#define UNUSED_VARIABLE(V) (void)V

#define EXPECT(aCondition) \
    do                     \
    {                      \
        if (!(aCondition)) \
        {                  \
            goto exit;     \
        }                  \
    } while (0)

#define EXPECT_ACTION(aCondition, aAction) \
    do                                     \
    {                                      \
        if (!(aCondition))                 \
        {                                  \
            aAction;                       \
            goto exit;                     \
        }                                  \
    } while (0)

#define ARRAY_LENGTH(aArray) (sizeof(aArray) / sizeof(aArray[0]))

enum
{
    CC2652_RECEIVE_SENSITIVITY = -100, // dBm
    CC2652_RF_CMD0 = 0x0607,
};

enum
{
    RADIO_FRAME_MAX_SIZE = 127,  ///< aMaxPHYPacketSize (IEEE 802.15.4-2006)
    RADIO_FRAME_MIN_SIZE = 3,    ///< Minimal size of frame FCS + CONTROL
    RADIO_SYMBOLS_PER_OCTET = 2, ///< 2.4 GHz IEEE 802.15.4-2006
    RADIO_BIT_RATE = 250000,     ///< 2.4 GHz IEEE 802.15.4 (bits per second)
    RADIO_BITS_PER_OCTET = 8,    ///< Number of bits per octet

    RADIO_SYMBOL_TIME = ((RADIO_BITS_PER_OCTET / RADIO_SYMBOLS_PER_OCTET) * 1000000) / RADIO_BIT_RATE,
    RADIO_LQI_NONE = 0,        ///< LQI measurement not supported
    RADIO_RSSI_INVALID = 127,  ///< Invalid or unknown RSSI value
    RADIO_POWER_INVALID = 127, ///< Invalid or unknown power value
};

enum
{
    RADIO_CHANNEL_PAGE_0 = 0,                                 ///< 2.4 GHz IEEE 802.15.4-2006
    RADIO_CHANNEL_PAGE_0_MASK = (1U << RADIO_CHANNEL_PAGE_0), ///< 2.4 GHz IEEE 802.15.4-2006
    RADIO_CHANNEL_PAGE_2 = 2,                                 ///< 915 MHz IEEE 802.15.4-2006
    RADIO_CHANNEL_PAGE_2_MASK = (1U << RADIO_CHANNEL_PAGE_2), ///< 915 MHz IEEE 802.15.4-2006
};

enum
{
    RADIO_915MHZ_OQPSK_CHANNEL_MIN = 1,                                         ///< 915 MHz IEEE 802.15.4-2006
    RADIO_915MHZ_OQPSK_CHANNEL_MAX = 10,                                        ///< 915 MHz IEEE 802.15.4-2006
    RADIO_915MHZ_OQPSK_CHANNEL_MASK = 0x3ff << RADIO_915MHZ_OQPSK_CHANNEL_MIN,  ///< 915 MHz IEEE 802.15.4-2006
    RADIO_2P4GHZ_OQPSK_CHANNEL_MIN = 11,                                        ///< 2.4 GHz IEEE 802.15.4-2006
    RADIO_2P4GHZ_OQPSK_CHANNEL_MAX = 26,                                        ///< 2.4 GHz IEEE 802.15.4-2006
    RADIO_2P4GHZ_OQPSK_CHANNEL_MASK = 0xffff << RADIO_2P4GHZ_OQPSK_CHANNEL_MIN, ///< 2.4 GHz IEEE 802.15.4-2006
};

enum
{
    CC2652_CHANNEL_MIN = RADIO_2P4GHZ_OQPSK_CHANNEL_MIN,
    CC2652_CHANNEL_MAX = RADIO_2P4GHZ_OQPSK_CHANNEL_MAX,
};

/* phy state as defined by openthread */
static volatile cc2652_PhyState_t sState;

/* set to max transmit power by default */
static output_config_t const *sCurrentOutputPower = &(rgOutputPower[0]);

/* Overrides from SmartRF Studio 7 2.10.0#94 */
static uint32_t sIEEEOverrides[] = {
    // override_ieee_802_15_4.xml
    // DC/DC regulator: In Tx, use DCDCCTL5[3:0]=0x3 (DITHER_EN=0 and IPEAK=3).
    (uint32_t)0x00F388D3,
    // Rx: Set LNA bias current offset to +15 to saturate trim to max (default: 0)
    (uint32_t)0x000F8883, (uint32_t)0xFFFFFFFF};

/*
 * Number of retry counts left to the currently transmitting frame.
 *
 * Initialized when a frame is passed to be sent over the air, and decremented
 * by the radio ISR every time the transmit command string fails to receive a
 * corresponding ack.
 */
static volatile unsigned int sTransmitRetryCount = 0;

/*
 * Offset of the radio timer from the rtc.
 *
 * Used when we start and stop the RAT on enabling and disabling of the rf
 * core.
 */
static uint32_t sRatOffset = 0;

/*
 * Radio command structures that run on the CM0.
 */
// clang-format off
static volatile __attribute__((aligned(4))) rfc_CMD_SYNC_START_RAT_t     sStartRatCmd;
static volatile __attribute__((aligned(4))) rfc_CMD_RADIO_SETUP_t        sRadioSetupCmd;

static volatile __attribute__((aligned(4))) rfc_CMD_FS_POWERDOWN_t       sFsPowerdownCmd;
static volatile __attribute__((aligned(4))) rfc_CMD_SYNC_STOP_RAT_t      sStopRatCmd;

static volatile __attribute__((aligned(4))) rfc_CMD_CLEAR_RX_t           sClearReceiveQueueCmd;
static volatile __attribute__((aligned(4))) rfc_CMD_IEEE_MOD_FILT_t      sModifyReceiveFilterCmd;
static volatile __attribute__((aligned(4))) rfc_CMD_IEEE_MOD_SRC_MATCH_t sModifyReceiveSrcMatchCmd;

static volatile __attribute__((aligned(4))) rfc_CMD_IEEE_ED_SCAN_t       sEdScanCmd;

static volatile __attribute__((aligned(4))) rfc_CMD_IEEE_RX_t            sReceiveCmd;

static volatile __attribute__((aligned(4))) rfc_CMD_IEEE_CSMA_t          sCsmacaBackoffCmd;
static volatile __attribute__((aligned(4))) rfc_CMD_IEEE_TX_t            sTransmitCmd;
static volatile __attribute__((aligned(4))) rfc_CMD_IEEE_RX_ACK_t        sTransmitRxAckCmd;

static volatile __attribute__((aligned(4))) ext_src_match_data_t         sSrcMatchExtData;
static volatile __attribute__((aligned(4))) short_src_match_data_t       sSrcMatchShortData;
// clang-format on

/*
 * Structure containing radio statistics.
 */
static __attribute__((aligned(4))) rfc_ieeeRxOutput_t sRfStats;

/*
 * Two receive buffers entries with room for 1 max IEEE802.15.4 frame in each
 *
 * These will be setup in a circular buffer configuration by /ref sRxDataQueue.
 */
#define RX_BUF_SIZE 144
static __attribute__((aligned(4))) uint8_t sRxBuf0[RX_BUF_SIZE];
static __attribute__((aligned(4))) uint8_t sRxBuf1[RX_BUF_SIZE];
static __attribute__((aligned(4))) uint8_t sRxBuf2[RX_BUF_SIZE];
static __attribute__((aligned(4))) uint8_t sRxBuf3[RX_BUF_SIZE];

/*
 * The RX Data Queue used by @ref sReceiveCmd.
 */
static __attribute__((aligned(4))) dataQueue_t sRxDataQueue = {0};

/*
 * OpenThread data primitives
 */
static RadioFrame sTransmitFrame;
static RadioError sTransmitError;

static __attribute__((aligned(4))) uint8_t sTransmitPsdu[RADIO_FRAME_MAX_SIZE];

static volatile bool sTxCmdChainDone = false;

/*
 * Interrupt handlers forward declared for register functions.
 */
static void RFCCPE0IntHandler(void);
static void RFCCPE1IntHandler(void);

/**
 * Initialize the RX/TX buffers.
 *
 * Zeros out the receive and transmit buffers and sets up the data structures
 * of the receive queue.
 */
static void rfCoreInitBufs(void)
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

    sTransmitFrame.mPsdu = sTransmitPsdu;
    sTransmitFrame.mLength = 0;
}

/**
 * Initialize the RX command structure.
 *
 * Sets the default values for the receive command structure.
 */
static void rfCoreInitReceiveParams(void)
{
    // clang-format off
    static const rfc_CMD_IEEE_RX_t cReceiveCmd =
    {
        .commandNo                  = CMD_IEEE_RX,
        .status                     = IDLE,
        .pNextOp                    = NULL,
        .startTime                  = 0u,
        .startTrigger               =
        {
            .triggerType            = TRIG_NOW,
        },
        .condition                  = {
            .rule                   = COND_NEVER,
        },
        .channel                    = CC2652_CHANNEL_MIN,
        .rxConfig                   =
        {
            .bAutoFlushCrc          = 1,
            .bAutoFlushIgn          = 0,
            .bIncludePhyHdr         = 0,
            .bIncludeCrc            = 0,//
            .bAppendRssi            = 1,
            .bAppendCorrCrc         = 1,
            .bAppendSrcInd          = 0,
            .bAppendTimestamp       = 0,
        },
        .frameFiltOpt               =
        {
            .frameFiltEn            = 1,
            .frameFiltStop          = 1,
            .autoAckEn              = 1,
            .slottedAckEn           = 0,
            .autoPendEn             = 0,//
            .defaultPend            = 0,
            .bPendDataReqOnly       = 0,
            .bPanCoord              = 0,
            .maxFrameVersion        = 3,
            .bStrictLenFilter       = 1,
        },
        .frameTypes                 =
        {
            .bAcceptFt0Beacon       = 1,
            .bAcceptFt1Data         = 1,
            .bAcceptFt2Ack          = 1,
            .bAcceptFt3MacCmd       = 1,
            .bAcceptFt4Reserved     = 1,
            .bAcceptFt5Reserved     = 1,
            .bAcceptFt6Reserved     = 1,
            .bAcceptFt7Reserved     = 1,
        },
        .ccaOpt                     =
        {
            .ccaEnEnergy            = 1,
            .ccaEnCorr              = 1,
            .ccaEnSync              = 1,
            .ccaCorrOp              = 1,
            .ccaSyncOp              = 0,
            .ccaCorrThr             = 3,
        },
        .ccaRssiThr                 = -90,
        .endTrigger                 =
        {
            .triggerType            = TRIG_NEVER,
        },
        .endTime                    = 0u,
    };
    // clang-format on
    sReceiveCmd = cReceiveCmd;

    sReceiveCmd.pRxQ = &sRxDataQueue;
    sReceiveCmd.pOutput = &sRfStats;

    sReceiveCmd.numShortEntries = CC2652_SHORTADD_SRC_MATCH_NUM;
    sReceiveCmd.pShortEntryList = (void *)&sSrcMatchShortData;

    sReceiveCmd.numExtEntries = CC2652_EXTADD_SRC_MATCH_NUM;
    sReceiveCmd.pExtEntryList = (uint32_t *)&sSrcMatchExtData;
}

/**
 * Sends the direct abort command to the radio core.
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command completed correctly.
 */
static uint_fast8_t rfCoreExecuteAbortCmd(void)
{
    return (RFCDoorbellSendTo(CMDR_DIR_CMD(CMD_ABORT)) & 0xFF);
}

/**
 * Sends the direct ping command to the radio core.
 *
 * Check that the Radio core is alive and able to respond to commands.
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command completed correctly.
 */
static uint_fast8_t rfCoreExecutePingCmd(void)
{
    return (RFCDoorbellSendTo(CMDR_DIR_CMD(CMD_PING)) & 0xFF);
}

/**
 * Sends the immediate clear rx queue command to the radio core.
 *
 * Uses the radio core to mark all of the entries in the receive queue as
 * pending. This is used instead of clearing the entries manually to avoid race
 * conditions between the main processor and the radio core.
 *
 * @param [in] aQueue A pointer to the receive queue to be cleared.
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command completed correctly.
 */
static uint_fast8_t rfCoreClearReceiveQueue(dataQueue_t *aQueue)
{
    /* memset skipped because sClearReceiveQueueCmd has only 2 members and padding */
    sClearReceiveQueueCmd.commandNo = CMD_CLEAR_RX;
    sClearReceiveQueueCmd.pQueue = aQueue;

    return (RFCDoorbellSendTo((uint32_t)&sClearReceiveQueueCmd) & 0xFF);
}

/**
 * Enable/disable frame filtering.
 *
 * Uses the radio core to alter the current running RX command filtering
 * options. This ensures there is no access fault between the CM3 and CM0 for
 * the RX command.
 *
 * This function leaves the type of frames to be filtered the same as the
 * receive command.
 *
 * @note An IEEE RX command *must* be running while this command executes.
 *
 * @param [in] aEnable TRUE: enable frame filtering,
 *                     FALSE: disable frame filtering.
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command completed correctly.
 */
static uint_fast8_t rfCoreModifyRxFrameFilter(bool aEnable)
{
    /* memset skipped because sModifyReceiveFilterCmd has only 3 members */
    sModifyReceiveFilterCmd.commandNo = CMD_IEEE_MOD_FILT;
    /* copy current frame filtering and frame types from running RX command */
    memcpy((void *)&sModifyReceiveFilterCmd.newFrameFiltOpt, (void *)&sReceiveCmd.frameFiltOpt,
           sizeof(sModifyReceiveFilterCmd.newFrameFiltOpt));
    memcpy((void *)&sModifyReceiveFilterCmd.newFrameTypes, (void *)&sReceiveCmd.frameTypes,
           sizeof(sModifyReceiveFilterCmd.newFrameTypes));

    sModifyReceiveFilterCmd.newFrameFiltOpt.frameFiltEn = aEnable ? 1 : 0;

    return (RFCDoorbellSendTo((uint32_t)&sModifyReceiveFilterCmd) & 0xFF);
}

/**
 * Enable/disable autoPend feature.
 *
 * Uses the radio core to alter the current running RX command filtering
 * options. This ensures there is no access fault between the CM3 and CM0 for
 * the RX command.
 *
 * This function leaves the type of frames to be filtered the same as the
 * receive command.
 *
 * @note An IEEE RX command *must* be running while this command executes.
 *
 * @param [in] aEnable TRUE: enable autoPend,
 *                     FALSE: disable autoPend.
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command completed correctly.
 */
static uint_fast8_t rfCoreModifyRxAutoPend(bool aEnable)
{
    /* memset skipped because sModifyReceiveFilterCmd has only 3 members */
    sModifyReceiveFilterCmd.commandNo = CMD_IEEE_MOD_FILT;
    /* copy current frame filtering and frame types from running RX command */
    memcpy((void *)&sModifyReceiveFilterCmd.newFrameFiltOpt, (void *)&sReceiveCmd.frameFiltOpt,
           sizeof(sModifyReceiveFilterCmd.newFrameFiltOpt));
    memcpy((void *)&sModifyReceiveFilterCmd.newFrameTypes, (void *)&sReceiveCmd.frameTypes,
           sizeof(sModifyReceiveFilterCmd.newFrameTypes));

    sModifyReceiveFilterCmd.newFrameFiltOpt.autoPendEn = aEnable ? 1 : 0;

    return (RFCDoorbellSendTo((uint32_t)&sModifyReceiveFilterCmd) & 0xFF);
}

/**
 * Sends the immediate modify source matching command to the radio core.
 *
 * Uses the radio core to alter the current source matching parameters used by
 * the running RX command. This ensures there is no access fault between the
 * CM3 and CM0, and ensures that the RX command has cohesive view of the data.
 * The CM3 may make alterations to the source matching entries if the entry is
 * marked as disabled.
 *
 * @note An IEEE RX command *must* be running while this command executes.
 *
 * @param [in] aEntryNo The index of the entry to alter.
 * @param [in] aType    TRUE: the entry is a short address,
 *                      FALSE: the entry is an extended address.
 * @param [in] aEnable  Whether the given entry is to be enabled or disabled.
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command completed correctly.
 */
static uint_fast8_t rfCoreModifySourceMatchEntry(uint8_t aEntryNo, cc2652_address_t aType, bool aEnable)
{
    /* memset kept to save 60 bytes of text space, gcc can't optimize the
     * following bitfield operation if it doesn't know the fields are zero
     * already.
     */
    memset((void *)&sModifyReceiveSrcMatchCmd, 0, sizeof(sModifyReceiveSrcMatchCmd));

    sModifyReceiveSrcMatchCmd.commandNo = CMD_IEEE_MOD_SRC_MATCH;

    /* we only use source matching for pending data bit, so enabling and
     * pending are the same to us.
     */
    if (aEnable)
    {
        sModifyReceiveSrcMatchCmd.options.bEnable = 1;
        sModifyReceiveSrcMatchCmd.options.srcPend = 1;
    }
    else
    {
        sModifyReceiveSrcMatchCmd.options.bEnable = 0;
        sModifyReceiveSrcMatchCmd.options.srcPend = 0;
    }

    sModifyReceiveSrcMatchCmd.options.entryType = aType;
    sModifyReceiveSrcMatchCmd.entryNo = aEntryNo;

    return (RFCDoorbellSendTo((uint32_t)&sModifyReceiveSrcMatchCmd) & 0xFF);
}

/**
 * Walks the short address source match list to find an address.
 *
 * @param [in] aAddress The short address to search for.
 *
 * @return The index where the address was found.
 * @retval CC2652_SRC_MATCH_NONE The address was not found.
 */
static uint8_t rfCoreFindShortSrcMatchIdx(uint16_t aAddress)
{
    uint8_t i;
    uint8_t ret = CC2652_SRC_MATCH_NONE;

    for (i = 0; i < CC2652_SHORTADD_SRC_MATCH_NUM; i++)
    {
        if (sSrcMatchShortData.extAddrEnt[i].shortAddr == aAddress)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

/**
 * Walks the short address source match list to find an empty slot.
 *
 * @return The index of an unused address slot.
 * @retval CC2652_SRC_MATCH_NONE No unused slots available.
 */
static uint8_t rfCoreFindEmptyShortSrcMatchIdx(void)
{
    uint8_t i;
    uint8_t ret = CC2652_SRC_MATCH_NONE;

    for (i = 0; i < CC2652_SHORTADD_SRC_MATCH_NUM; i++)
    {
        if ((sSrcMatchShortData.srcMatchEn[i / 32] & (1 << (i % 32))) == 0u)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

/**
 * Walks the extended address source match list to find an address.
 *
 * @param [in] aAddress The extended address to search for.
 *
 * @return The index where the address was found.
 * @retval CC2652_SRC_MATCH_NONE The address was not found.
 */
static uint8_t rfCoreFindExtSrcMatchIdx(const uint64_t *aAddress)
{
    uint8_t i;
    uint8_t ret = CC2652_SRC_MATCH_NONE;

    for (i = 0; i < CC2652_EXTADD_SRC_MATCH_NUM; i++)
    {
        if (sSrcMatchExtData.extAddrEnt[i] == *aAddress)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

/**
 * Walks the extended address source match list to find an empty slot.
 *
 * @return The index of an unused address slot.
 * @retval CC2652_SRC_MATCH_NONE No unused slots available.
 */
static uint8_t rfCoreFindEmptyExtSrcMatchIdx(void)
{
    uint8_t i;
    uint8_t ret = CC2652_SRC_MATCH_NONE;

    for (i = 0; i < CC2652_EXTADD_SRC_MATCH_NUM; i++)
    {
        if ((sSrcMatchExtData.srcMatchEn[i / 32] & (1 << (i % 32))) != 0u)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

/**
 * Sends the tx command to the radio core.
 *
 * Sends the packet to the radio core to be sent asynchronously.
 *
 * @note @ref aPsdu *must* be 4 byte aligned and not include the FCS.
 *
 * @param [in] aPsdu A pointer to the data to be sent.
 * @param [in] aLen  The length in bytes of data pointed to by PSDU.
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command completed correctly.
 */
static uint_fast8_t rfCoreSendTransmitCmd(uint8_t *aPsdu, uint8_t aLen)
{
    // clang-format off
    static const rfc_CMD_IEEE_CSMA_t cCsmacaBackoffCmd =
    {
        .commandNo                  = CMD_IEEE_CSMA,
        .status                     = IDLE,
        .startTrigger               =
        {
            .triggerType            = TRIG_NOW,
        },
        .condition                  = {
            .rule                   = COND_ALWAYS,
        },
        .macMaxBE                   = IEEE802154_MAC_MAX_BE,
        .macMaxCSMABackoffs         = IEEE802154_MAC_MAX_CSMA_BACKOFFS,
        .csmaConfig                 =
        {
            .initCW                 = 1,
            .bSlotted               = 0,
            .rxOffMode              = 0,
        },
        .NB                         = 0,
        .BE                         = IEEE802154_MAC_MIN_BE,
        .remainingPeriods           = 0,
        .endTrigger                 =
        {
            .triggerType            = TRIG_NEVER,
        },
        .endTime                    = 0x00000000,
    };
    static const rfc_CMD_IEEE_TX_t cTransmitCmd =
    {
        .commandNo                  = CMD_IEEE_TX,
        .status                     = IDLE,
        .startTrigger               =
        {
            .triggerType            = TRIG_NOW,
        },
        .condition                  = {
            .rule                   = COND_NEVER,
        },
        .pNextOp                    = NULL,
    };
    static const rfc_CMD_IEEE_RX_ACK_t cTransmitRxAckCmd =
    {
        .commandNo                  = CMD_IEEE_RX_ACK,
        .status                     = IDLE,
        .startTrigger               =
        {
            .triggerType            = TRIG_NOW,
        },
        .endTrigger                 =
        {
            .triggerType            = TRIG_REL_START,
            .pastTrig               = 1,
        },
        .condition                  = {
            .rule                   = COND_NEVER,
        },
        .pNextOp                    = NULL,
        /* number of RAT ticks to wait before claiming we haven't received an ack */
        .endTime                    = ((IEEE802154_MAC_ACK_WAIT_DURATION * CC2652_RAT_TICKS_PER_SEC) / IEEE802154_SYMBOLS_PER_SEC),
    };
    // clang-format on

    /* reset retry count */
    sTransmitRetryCount = 0;

    sCsmacaBackoffCmd = cCsmacaBackoffCmd;
    /* initialize the random state with a true random seed for the radio core's psudo rng */
    sCsmacaBackoffCmd.randomState = (uint16_t)rand();
    sCsmacaBackoffCmd.pNextOp = (rfc_radioOp_t *)&sTransmitCmd;

    sTransmitCmd = cTransmitCmd;
    /* no need to look for an ack if the tx operation was stopped */
    sTransmitCmd.payloadLen = aLen;
    sTransmitCmd.pPayload = aPsdu;

    //sTransmitRxAckCmd.seqNo = 0;
    if (aPsdu[0] & IEEE802154_ACK_REQUEST)
    {
        //RADIO_PRINTF("      TRANSMIT WITH ACK\n");
        //DUMP_LINE(aPsdu, aLen);
        /* setup the receive ack command to follow the tx command */
        sTransmitCmd.condition.rule = COND_STOP_ON_FALSE;
        sTransmitCmd.pNextOp = (rfc_radioOp_t *)&sTransmitRxAckCmd;

        sTransmitRxAckCmd = cTransmitRxAckCmd;
        sTransmitRxAckCmd.seqNo = aPsdu[IEEE802154_DSN_OFFSET];
    }

    return (RFCDoorbellSendTo((uint32_t)&sCsmacaBackoffCmd) & 0xFF);
}

/**
 * Sends the rx command to the radio core.
 *
 * Sends the pre-built receive command to the radio core. This sets up the
 * radio to receive packets according to the settings in the global rx command.
 *
 * @note This function does not alter any of the parameters of the rx command.
 * It is only concerned with sending the command to the radio core. See @ref
 * RadioSetPanId for an example of how the rx settings are set changed.
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command completed correctly.
 */
static uint_fast8_t rfCoreSendReceiveCmd(void)
{
    sReceiveCmd.status = IDLE;
    return (RFCDoorbellSendTo((uint32_t)&sReceiveCmd) & 0xFF);
}

static uint_fast8_t rfCoreSendEdScanCmd(uint8_t aChannel, uint16_t aDurration)
{
    // clang-format off
    static const rfc_CMD_IEEE_ED_SCAN_t cEdScanCmd =
    {
        .commandNo                  = CMD_IEEE_ED_SCAN,
        .startTrigger               =
        {
            .triggerType            = TRIG_NOW,
        },
        .condition                  = {
            .rule                   = COND_NEVER,
        },
        .ccaOpt                     =
        {
            .ccaEnEnergy            = 1,
            .ccaEnCorr              = 1,
            .ccaEnSync              = 1,
            .ccaCorrOp              = 1,
            .ccaSyncOp              = 0,
            .ccaCorrThr             = 3,
        },
        .ccaRssiThr                 = -90,
        .endTrigger                 =
        {
            .triggerType            = TRIG_REL_START,
            .pastTrig               = 1,
        },
    };
    // clang-format on
    sEdScanCmd = cEdScanCmd;

    sEdScanCmd.channel = aChannel;

    /* durration is in ms */
    sEdScanCmd.endTime = aDurration * (CC2652_RAT_TICKS_PER_SEC / 1000);

    return (RFCDoorbellSendTo((uint32_t)&sEdScanCmd) & 0xFF);
}

/**
 * Enables the cpe0 and cpe1 radio interrupts.
 *
 * Enables the @ref IRQ_LAST_COMMAND_DONE and @ref IRQ_LAST_FG_COMMAND_DONE to
 * be handled by the @ref RFCCPE0IntHandler interrupt handler.
 */
static void rfCoreSetupInt(void)
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

/**
 * Disables and clears the cpe0 and cpe1 radio interrupts.
 */
static void rfCoreStopInt(void)
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

/**
 * Turns on the radio core.
 *
 * Sets up the power and resources for the radio core.
 * - switches the high frequency clock to the xosc crystal
 * - sets the mode for the radio core to IEEE 802.15.4
 * - initializes the rx buffers and command
 * - powers on the radio core power domain
 * - enables the radio core power domain
 * - sets up the interrupts
 * - sends the ping command to the radio core to make sure it is running
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command was received.
 */
static uint_fast8_t rfCorePowerOn(void)
{
    bool interruptsWereDisabled;
    bool oscSourceSwitch = false;

    /* Request the HF XOSC as the source for the HF clock. Needed before we can
     * use the FS. This will only request, it will _not_ perform the switch.
     */
    if (OSCClockSourceGet(OSC_SRC_CLK_HF) != OSC_XOSC_HF)
    {
        /* Request to switch to the crystal to enable radio operation. It takes a
         * while for the XTAL to be ready so instead of performing the actual
         * switch, we do other stuff while the XOSC is getting ready.
         */
        OSCClockSourceSet(OSC_SRC_CLK_HF, OSC_XOSC_HF);
        oscSourceSwitch = true;
    }

    /* Set of RF Core data queue. Circular buffer, no last entry */
    sRxDataQueue.pCurrEntry = sRxBuf0;
    sRxDataQueue.pLastEntry = NULL;

    rfCoreInitBufs();

    /*
     * Trigger a switch to the XOSC, so that we can subsequently use the RF FS
     * This will block until the XOSC is actually ready, but give how we
     * requested it early on, this won't be too long a wait.
     * This should be done before starting the RAT.
     */
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
    PRCMPowerDomainOn(PRCM_DOMAIN_RFCORE);

    while (PRCMPowerDomainsAllOn(PRCM_DOMAIN_RFCORE) != PRCM_DOMAIN_POWER_ON)
        ;

    PRCMDomainEnable(PRCM_DOMAIN_RFCORE);
    PRCMLoadSet();

    while (!PRCMLoadGet())
        ;

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

/**
 * Turns off the radio core.
 *
 * Switches off the power and resources for the radio core.
 * - disables the interrupts
 * - disables the radio core power domain
 * - powers off the radio core power domain
 * - switches the high frequency clock to the rcosc to save power
 */
static void rfCorePowerOff(void)
{
    rfCoreStopInt();

    PRCMDomainDisable(PRCM_DOMAIN_RFCORE);
    PRCMLoadSet();

    while (!PRCMLoadGet())
        ;

    PRCMPowerDomainOff(PRCM_DOMAIN_RFCORE);

    while (PRCMPowerDomainsAllOn(PRCM_DOMAIN_RFCORE) != PRCM_DOMAIN_POWER_OFF)
        ;

    if (OSCClockSourceGet(OSC_SRC_CLK_HF) != OSC_RCOSC_HF)
    {
        /* Request to switch to the RC osc for low power mode. */
        OSCClockSourceSet(OSC_SRC_CLK_HF, OSC_RCOSC_HF);
        /* Switch the HF clock source (cc26xxware executes this from ROM) */
        OSCHfSourceSwitch();
    }
}

/**
 * Applies CPE patche to the radio.
 */
static void rfCoreApplyPatch(void)
{
    rf_patch_cpe_ieee_802_15_4();

    /* disable ram bus clocks */
    RFCDoorbellSendTo(CMDR_DIR_CMD_2BYTE(CC2652_RF_CMD0, 0));
}

/**
 * Sends the setup command string to the radio core.
 *
 * Enables the clock line from the RTC to the RF core RAT. Enables the RAT
 * timer and sets up the radio in IEEE mode.
 *
 * @return The value from the command status register.
 * @retval CMDSTA_Done The command was received.
 */
static uint_fast16_t rfCoreSendEnableCmd(void)
{
    uint8_t doorbellRet;
    bool interruptsWereDisabled;
    uint_fast16_t ret;

    // clang-format off
    static const rfc_CMD_SYNC_START_RAT_t cStartRatCmd =
    {
        .commandNo                  = CMD_SYNC_START_RAT,
        .startTrigger               =
        {
            .triggerType            = TRIG_NOW,
        },
        .condition                  = {
            .rule                   = COND_STOP_ON_FALSE,
        },
    };
    static const rfc_CMD_RADIO_SETUP_t cRadioSetupCmd =
    {
        .commandNo                  = CMD_RADIO_SETUP,
        .startTrigger               =
        {
            .triggerType            = TRIG_NOW,
        },
        .condition                  = {
            .rule                   = COND_NEVER,
        },
        .mode                       = 1, // IEEE 802.15.4 mode
    };
    // clang-format on
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

    rfCoreApplyPatch();

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

/**
 * Sends the shutdown command string to the radio core.
 *
 * Powers down the frequency synthesizer and stops the RAT.
 *
 * @note synchronously waits until the command string completes.
 *
 * @return The status of the RAT stop command.
 * @retval DONE_OK The command string executed properly.
 */
static uint_fast16_t rfCoreSendDisableCmd(void)
{
    uint8_t doorbellRet;
    bool interruptsWereDisabled;
    uint_fast16_t ret;

    // clang-format off
    static const rfc_CMD_FS_POWERDOWN_t cFsPowerdownCmd =
    {
        .commandNo                  = CMD_FS_POWERDOWN,
        .startTrigger               =
        {
            .triggerType            = TRIG_NOW,
        },
        .condition                  = {
            .rule                   = COND_ALWAYS,
        },
    };
    static const rfc_CMD_SYNC_STOP_RAT_t cStopRatCmd =
    {
        .commandNo                  = CMD_SYNC_STOP_RAT,
        .startTrigger               =
        {
            .triggerType            = TRIG_NOW,
        },
        .condition                  = {
            .rule                   = COND_NEVER,
        },
    };
    // clang-format on

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

/**
 * Error interrupt handler.
 */
static void RFCCPE1IntHandler(void)
{
    /* Clear INTERNAL_ERROR interrupt flag */
    HWREG(RFC_DBELL_NONBUF_BASE + RFC_DBELL_O_RFCPEIFG) = 0x7FFFFFFF;
}

/**
 * Command done handler.
 */
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
                /* The TX command was either stopped or we are not looking for
                 * an ack */
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

/**
 * Function documented in platform-cc2652.h
 */
void RadioInit(void)
{
    /* Populate the RX parameters data structure with default values */
    rfCoreInitReceiveParams();
    sState = cc2652_stateDisabled;
}

/**
 * Function documented in platform/radio.h
 */
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

/**
 * Function documented in platform/radio.h
 */
bool RadioIsEnabled(void) { return (sState != cc2652_stateDisabled); }
bool RadioIsActive(void)  { return (sState > cc2652_stateSleep);     }
bool RadioIsRecive(void)  { return (sState == cc2652_stateReceive);  }
int  RadioGetState(void)  { return sState; }

/**
 * Function documented in platform/radio.h
 */
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
        /* we don't want to fail if this command string doesn't work, just turn
         * off the whole core
         */
        rfCorePowerOff();
        sState = cc2652_stateDisabled;
        error = ERROR_RADIO_NONE;
    }

    return error;
}

/**
 * Function documented in platform/radio.h
 */
RadioError RadioEnergyScan(uint8_t aScanChannel, uint16_t aScanDuration)
{
    RadioError error = ERROR_RADIO_BUSY;

    if (sState == cc2652_stateSleep)
    {
        sState = cc2652_stateEdScan;
        EXPECT_ACTION(rfCoreSendEdScanCmd(aScanChannel, aScanDuration) == CMDSTA_Done, error = ERROR_RADIO_FAILED);
        error = ERROR_RADIO_NONE;
    }

exit:
    return error;
}

/**
 * Function documented in platform/radio.h
 */
RadioError RadioGetTransmitPower(int8_t *aPower)
{
    RadioError error = ERROR_RADIO_NONE;

    EXPECT_ACTION(aPower != NULL, error = ERROR_RADIO_INVALID_ARGS);
    *aPower = sCurrentOutputPower->dbm;

exit:
    return error;
}

/**
 * Function documented in platform/radio.h
 */
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

/**
 * Function documented in platform/radio.h
 */
RadioError RadioReceive(uint8_t aChannel)
{
    RADIO_PRINTF("[RADIO] %s( CHANNEL = %d )\n", __func__, (int)aChannel);
    
    if (aChannel < CC2652_CHANNEL_MIN || aChannel > CC2652_CHANNEL_MAX)
        return ERROR_RADIO_INVALID_ARGS;

    RadioError error = ERROR_RADIO_BUSY;
    if (sState == cc2652_stateSleep)
    {
        sState = cc2652_stateReceive;

        /*
         * initialize the receive command
         * XXX: no memset here because we assume init has been called and we
         *      may have changed some values in the rx command
         */
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
            /*
             * we have either not fallen back into our receive command or
             * we are running on the wrong channel. Either way assume the
             * caller correctly called us and abort all running commands.
             */
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

/**
 * Function documented in platform/radio.h
 */
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

/**
 * Function documented in platform/radio.h
 */
RadioFrame *RadioGetTransmitBuffer(void)
{
    return &sTransmitFrame;
}

/**
 * Function documented in platform/radio.h
 */
RadioError RadioTransmit(RadioFrame *aFrame)
{
    RadioError error = ERROR_RADIO_BUSY;
    aFrame->mTxError = ERROR_RADIO_TIMEOUT; // WizIO

    if (sState == cc2652_stateReceive)
    {
        sState = cc2652_stateTransmit;

        /* removing 2 bytes of CRC placeholder because we generate that in hardware */
        EXPECT_ACTION(rfCoreSendTransmitCmd(aFrame->mPsdu, aFrame->mLength - 2) == CMDSTA_Done, error = ERROR_RADIO_FAILED);
        error = ERROR_RADIO_NONE;
        sTransmitError = ERROR_RADIO_NONE;
        sTxCmdChainDone = false;
        RadioTxStarted(aFrame);
    }

exit:
    return error;
}

/**
 * Function documented in platform/radio.h
 */
int8_t RadioGetRssi(void)
{
    return sRfStats.maxRssi;
}

/**
 * Function documented in platform/radio.h
 */
RadioCaps RadioGetCaps(void)
{

    return (RadioCaps)(RADIO_CAPS_ACK_TIMEOUT | RADIO_CAPS_ENERGY_SCAN | RADIO_CAPS_TRANSMIT_RETRIES | RADIO_CAPS_CSMA_BACKOFF);
}

/**
 * Function documented in platform/radio.h
 */
void RadioEnableSrcMatch(bool aEnable)
{

    if (sReceiveCmd.status == ACTIVE || sReceiveCmd.status == IEEE_SUSPENDED)
    {
        /* we have a running or backgrounded rx command */
        rfCoreModifyRxAutoPend(aEnable);
    }
    else
    {
        /* if we are promiscuous, then frame filtering should be disabled */
        sReceiveCmd.frameFiltOpt.autoPendEn = aEnable ? 1 : 0;
    }
}

/**
 * Function documented in platform/radio.h
 */
RadioError RadioAddSrcMatchShortEntry(uint16_t aShortAddress)
{

    RadioError error = ERROR_RADIO_NONE;
    uint8_t idx = rfCoreFindShortSrcMatchIdx(aShortAddress);

    if (idx == CC2652_SRC_MATCH_NONE)
    {
        /* the entry does not exist already, add it */
        EXPECT_ACTION((idx = rfCoreFindEmptyShortSrcMatchIdx()) != CC2652_SRC_MATCH_NONE, error = ERROR_RADIO_NO_BUFS);
        sSrcMatchShortData.extAddrEnt[idx].shortAddr = aShortAddress;
        sSrcMatchShortData.extAddrEnt[idx].panId = sReceiveCmd.localPanID;
    }

    if (sReceiveCmd.status == ACTIVE || sReceiveCmd.status == IEEE_SUSPENDED)
    {
        /* we have a running or backgrounded rx command */
        EXPECT_ACTION(rfCoreModifySourceMatchEntry(idx, SHORT_ADDRESS, true) == CMDSTA_Done, error = ERROR_RADIO_FAILED);
    }
    else
    {
        /* we are not running, so we must update the values ourselves */
        sSrcMatchShortData.srcPendEn[idx / 32] |= (1 << (idx % 32));
        sSrcMatchShortData.srcMatchEn[idx / 32] |= (1 << (idx % 32));
    }

exit:
    return error;
}

/**
 * Function documented in platform/radio.h
 */
RadioError RadioClearSrcMatchShortEntry(uint16_t aShortAddress)
{

    RadioError error = ERROR_RADIO_NONE;
    uint8_t idx;

    EXPECT_ACTION((idx = rfCoreFindShortSrcMatchIdx(aShortAddress)) != CC2652_SRC_MATCH_NONE,
                  error = ERROR_RADIO_NO_ADDRESS);

    if (sReceiveCmd.status == ACTIVE || sReceiveCmd.status == IEEE_SUSPENDED)
    {
        /* we have a running or backgrounded rx command */
        EXPECT_ACTION(rfCoreModifySourceMatchEntry(idx, SHORT_ADDRESS, false) == CMDSTA_Done,
                      error = ERROR_RADIO_FAILED);
    }
    else
    {
        /* we are not running, so we must update the values ourselves */
        sSrcMatchShortData.srcPendEn[idx / 32] &= ~(1 << (idx % 32));
        sSrcMatchShortData.srcMatchEn[idx / 32] &= ~(1 << (idx % 32));
    }

exit:
    return error;
}

/**
 * Function documented in platform/radio.h
 */
RadioError RadioAddSrcMatchExtEntry(const ExtAddress *aExtAddress)
{

    RadioError error = ERROR_RADIO_NONE;
    uint64_t extAddress = RadioReadUint64Le(aExtAddress->m8);
    uint8_t idx = rfCoreFindExtSrcMatchIdx(&extAddress);

    if (idx == CC2652_SRC_MATCH_NONE)
    {
        /* the entry does not exist already, add it */
        EXPECT_ACTION((idx = rfCoreFindEmptyExtSrcMatchIdx()) != CC2652_SRC_MATCH_NONE, error = ERROR_RADIO_NO_BUFS);
        sSrcMatchExtData.extAddrEnt[idx] = extAddress;
    }

    if (sReceiveCmd.status == ACTIVE || sReceiveCmd.status == IEEE_SUSPENDED)
    {
        /* we have a running or backgrounded rx command */
        EXPECT_ACTION(rfCoreModifySourceMatchEntry(idx, EXT_ADDRESS, true) == CMDSTA_Done, error = ERROR_RADIO_FAILED);
    }
    else
    {
        /* we are not running, so we must update the values ourselves */
        sSrcMatchExtData.srcPendEn[idx / 32] |= (1 << (idx % 32));
        sSrcMatchExtData.srcMatchEn[idx / 32] |= (1 << (idx % 32));
    }

exit:
    return error;
}

/**
 * Function documented in platform/radio.h
 */
RadioError RadioClearSrcMatchExtEntry(const ExtAddress *aExtAddress)
{

    RadioError error = ERROR_RADIO_NONE;
    uint64_t extAddress = RadioReadUint64Le(aExtAddress->m8);
    uint8_t idx;

    EXPECT_ACTION((idx = rfCoreFindExtSrcMatchIdx(&extAddress)) != CC2652_SRC_MATCH_NONE,
                  error = ERROR_RADIO_NO_ADDRESS);

    if (sReceiveCmd.status == ACTIVE || sReceiveCmd.status == IEEE_SUSPENDED)
    {
        /* we have a running or backgrounded rx command */
        EXPECT_ACTION(rfCoreModifySourceMatchEntry(idx, EXT_ADDRESS, false) == CMDSTA_Done, error = ERROR_RADIO_FAILED);
    }
    else
    {
        /* we are not running, so we must update the values ourselves */
        sSrcMatchExtData.srcPendEn[idx / 32] &= ~(1 << (idx % 32));
        sSrcMatchExtData.srcMatchEn[idx / 32] &= ~(1 << (idx % 32));
    }

exit:
    return error;
}

/**
 * Function documented in platform/radio.h
 */
void RadioClearSrcMatchShortEntries(void)
{

    if (sReceiveCmd.status == ACTIVE || sReceiveCmd.status == IEEE_SUSPENDED)
    {
        unsigned int i;

        for (i = 0; i < CC2652_SHORTADD_SRC_MATCH_NUM; i++)
        {
            /* we have a running or backgrounded rx command */
            EXPECT(rfCoreModifySourceMatchEntry(i, SHORT_ADDRESS, false) == CMDSTA_Done);
        }
    }
    else
    {
        /* we are not running, so we can erase them ourselves */
        memset((void *)&sSrcMatchShortData, 0, sizeof(sSrcMatchShortData));
    }

exit:
    return;
}

/**
 * Function documented in platform/radio.h
 */
void RadioClearSrcMatchExtEntries(void)
{

    if (sReceiveCmd.status == ACTIVE || sReceiveCmd.status == IEEE_SUSPENDED)
    {
        unsigned int i;

        for (i = 0; i < CC2652_EXTADD_SRC_MATCH_NUM; i++)
        {
            /* we have a running or backgrounded rx command */
            EXPECT(rfCoreModifySourceMatchEntry(i, EXT_ADDRESS, false) == CMDSTA_Done);
        }
    }
    else
    {
        /* we are not running, so we can erase them ourselves */
        memset((void *)&sSrcMatchExtData, 0, sizeof(sSrcMatchExtData));
    }

exit:
    return;
}

/**
 * Function documented in platform/radio.h
 */
bool RadioGetPromiscuous(void)
{

    /* we are promiscuous if we are not filtering */
    return sReceiveCmd.frameFiltOpt.frameFiltEn == 0;
}

/**
 * Function documented in platform/radio.h
 */
void RadioSetPromiscuous(bool aEnable)
{

    if (sReceiveCmd.status == ACTIVE || sReceiveCmd.status == IEEE_SUSPENDED)
    {
        /* we have a running or backgrounded rx command */
        /* if we are promiscuous, then frame filtering should be disabled */
        rfCoreModifyRxFrameFilter(!aEnable);
        /* XXX should we dump any queued messages ? */
    }
    else
    {
        /* if we are promiscuous, then frame filtering should be disabled */
        sReceiveCmd.frameFiltOpt.frameFiltEn = aEnable ? 0 : 1;
    }
}

uint64_t RadioReadUint64Le(const uint8_t *aSource)
{
    uint64_t value = (uint64_t)aSource[0];
    value |= ((uint64_t)aSource[1]) << 8;
    value |= ((uint64_t)aSource[2]) << 16;
    value |= ((uint64_t)aSource[3]) << 24;
    value |= ((uint64_t)aSource[4]) << 32;
    value |= ((uint64_t)aSource[5]) << 40;
    value |= ((uint64_t)aSource[6]) << 48;
    value |= ((uint64_t)aSource[7]) << 56;
    return value;
}

/**
 * Function documented in platform/radio.h
 */
void RadioInitExtAddress(uint8_t *aIeeeEui64)
{
    uint8_t *eui64;
    unsigned int i;
    /*
     * The IEEE MAC address can be stored two places. We check the Customer
     * Configuration was not set before defaulting to the Factory
     * Configuration.
     */
    eui64 = (uint8_t *)(CCFG_BASE + CCFG_O_IEEE_MAC_0);

    for (i = 0; i < EXT_ADDRESS_SIZE; i++)
    {
        if (eui64[i] != CC2652_UNKNOWN_EUI64)
        {
            break;
        }
    }

    if (i >= EXT_ADDRESS_SIZE)
    {
        /* The ccfg address was all 0xFF, switch to the fcfg */
        eui64 = (uint8_t *)(FCFG1_BASE + FCFG1_O_MAC_15_4_0);
    }

    /*
     * The IEEE MAC address is stored in network byte order.  The caller seems
     * to want the address stored in little endian format, which is backwards
     * of the conventions setup by @ref RadioSetExtendedAddress.
     * RadioSetExtendedAddress assumes that the address being passed to
     * it is in network byte order, so the caller of
     * RadioSetExtendedAddress must swap the endianness before calling.
     *
     * It may be easier to have the caller of this function store the IEEE
     * address in network byte order.
     */
    ////for (i = 0; i < EXT_ADDRESS_SIZE; i++) aIeeeEui64[i] = eui64[(EXT_ADDRESS_SIZE - 1) - i];
    for (i = 0; i < EXT_ADDRESS_SIZE; i++) aIeeeEui64[i] = eui64[i]; // revers
}

/**
 * Function documented in platform/radio.h
 *
 * @note it is entirely possible for this function to fail, but there is no
 * valid way to return that error since the function prototype was changed.
 */
void RadioSetPanId(uint16_t aPanid)
{
    RADIO_PRINTF("[RADIO] %s( %04X )\n", __func__, (int)aPanid);
    /* XXX: if the pan id is the broadcast pan id (0xFFFF) the auto ack will
     * not work. This is due to the design of the CM0 and follows IEEE 802.15.4
     */
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

/**
 * Function documented in platform/radio.h
 *
 * @note it is entirely possible for this function to fail, but there is no
 * valid way to return that error since the function prototype was changed.
 */
void RadioSetExtendedAddress(const ExtAddress *aAddress)
{
    RADIO_PRINTF("[RADIO] %s()\n", __func__);
    /* XXX: assuming little endian format */
    if (sState == cc2652_stateReceive)
    {
        EXPECT(rfCoreExecuteAbortCmd() == CMDSTA_Done);
        sReceiveCmd.localExtAddr = RadioReadUint64Le(aAddress->m8);
        EXPECT(rfCoreClearReceiveQueue(&sRxDataQueue) == CMDSTA_Done);
        EXPECT(rfCoreSendReceiveCmd() == CMDSTA_Done);
        /* the interrupt from abort changed our state to sleep */
        sState = cc2652_stateReceive;
    }
    else if (sState != cc2652_stateTransmit)
    {
        sReceiveCmd.localExtAddr = RadioReadUint64Le(aAddress->m8);
    }

exit:
    return;
}

/**
 * Function documented in platform/radio.h
 *
 * @note it is entirely possible for this function to fail, but there is no
 * valid way to return that error since the function prototype was changed.
 */
void RadioSetShortAddress(uint16_t aAddress)
{
    RADIO_PRINTF("[RADIO] %s( %X )\n", __func__, (int)aAddress);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void RadioProcessTransmitDone(RadioFrame *aTransmitFrame, RadioFrame *aAckFrame, RadioError aTransmitError)
{
#if OPENTHREAD_CONFIG_DIAG_ENABLE
    if (DiagModeGet())
    {
        DiagRadioTransmitDone(aTransmitFrame, aTransmitError);
    }
    else
#endif /* OPENTHREAD_CONFIG_DIAG_ENABLE */
    {
        aTransmitFrame->mTxError = aTransmitError; // WizIO
        RadioTxDone(aTransmitFrame, aAckFrame, aTransmitError);
        //RADIO_PRINTF("[RADIO] %s()\n", __func__);
    }
}

static void RadioProcessReceiveDone(RadioFrame *aReceiveFrame, RadioError aReceiveError)
{
    // TODO Set this flag only when the packet is really acknowledged with frame pending set.
    // See https://github.com/openthread/openthread/pull/3785
    aReceiveFrame->mInfo.mRxInfo.mAckedWithFramePending = true;
#if OPENTHREAD_CONFIG_DIAG_ENABLE

    if (DiagModeGet())
    {
        DiagRadioReceiveDone(aReceiveFrame, aReceiveError);
    }
    else
#endif /* OPENTHREAD_CONFIG_DIAG_ENABLE */
    {
        RadioReceiveDone(aReceiveFrame, aReceiveError);
        //RADIO_PRINTF("[RADIO] %s()\n", __func__);
    }
}

void RadioProcessReceiveQueue(void)
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

            /* get the information appended to the end of the frame.
             * This array access looks like it is a fencepost error, but the
             * first byte is the number of bytes that follow.
             */
            len = payload[0];
            crcCorr = (rfc_ieeeRxCorrCrc_t *)&payload[len];
            rssi = payload[len - 1];

            if (crcCorr->status.bCrcErr == 0 && (len - 2) < RADIO_FRAME_MAX_SIZE)
            {
#if OPENTHREAD_CONFIG_TIME_SYNC_ENABLE
#error Time sync requires the timestamp of SFD rather than that of rx done!
#else
                if (RadioGetPromiscuous())
#endif
                {
                    // TODO: Propagate CM0 timestamp
                    // The current driver only supports milliseconds resolution.
                    receiveFrame.mInfo.mRxInfo.mTimestamp = millis() * 1000;
                }

                receiveFrame.mRxPayload = payload;

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
                    RadioProcessTransmitDone(&sTransmitFrame, &receiveFrame, receiveError);

                    sTransmitError = ERROR_RADIO_NONE;
                    sTxCmdChainDone = false;
                }
            }
            else
            {
                RadioProcessReceiveDone(&receiveFrame, receiveError);
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

/**
 * Function documented in platform-cc2652.h
 */
void RadioProcess(void)
{
    if (sState == cc2652_stateEdScan)
    {
        if (sEdScanCmd.status == IEEE_DONE_OK)
        {
            RadioEnergyScanDone(sEdScanCmd.maxRssi);
        }
        else if (sEdScanCmd.status == ACTIVE)
        {
            RadioEnergyScanDone(CC2652_INVALID_RSSI);
        }
    }

    if (sState == cc2652_stateReceive || sState == cc2652_stateTransmit)
    {
        RadioProcessReceiveQueue();
    }

    if (sTxCmdChainDone)
    {
        if (sState == cc2652_stateTransmit)
        {
            /* we are not looking for an ACK packet, or failed */
            sState = cc2652_stateReceive;
            RadioProcessTransmitDone(&sTransmitFrame, NULL, sTransmitError);
        }

        sTransmitError = ERROR_RADIO_NONE;
        sTxCmdChainDone = false;
    }
}

int8_t RadioGetReceiveSensitivity(void)
{
    return CC2652_RECEIVE_SENSITIVITY;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

ExtAddress ExtendedAddress;

uint64_t RadioGetExtendedAddress(void)
{
    RADIO_PRINTF("[RADIO] %s()\n", __func__);
    RadioInitExtAddress(ExtendedAddress.m8);
    //DUMP_LINE(ExtendedAddress.m8, 8);
    return RadioReadUint64Le(ExtendedAddress.m8);
}

bool RadioBegin(uint8_t Channel, int8_t Power)
{
    RadioError res = ERROR_RADIO_NONE;
    if (false == RadioIsEnabled())
    {
        if (ERROR_RADIO_NONE == (res = RadioSetTransmitPower(Power)))
        {
            if (ERROR_RADIO_NONE == (res = RadioEnable()))
            {
                res = RadioReceive(Channel);
            }
            else
            {
                RADIO_PRINTF("[ERROR] %s( RadioEnable )\n", __func__);
            }
        }
        else
        {
            RADIO_PRINTF("[ERROR] %s( RadioSetTransmitPower )\n", __func__);
        }
    }
    RADIO_PRINTF("[RADIO] %s( %s )\n", __func__, res == ERROR_RADIO_NONE ? "DONE" : "ERROR");
    return res == ERROR_RADIO_NONE;
}

//