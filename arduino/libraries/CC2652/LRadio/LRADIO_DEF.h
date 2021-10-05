#ifndef LRADIO_DEF_H_
#define LRADIO_DEF_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <driverlib/rfc.h>
#include <driverlib/rf_ieee_cmd.h>
#include <driverlib/rf_ieee_mailbox.h>
#include <driverlib/rf_data_entry.h>
#define DATA_ENTRY_LENSZ_BYTE 1

    enum
    {
        IEEE802154_FRAME_TYPE_MASK = 0x7,      ///< (IEEE 802.15.4-2006) PSDU.FCF.frameType
        IEEE802154_FRAME_TYPE_ACK = 0x2,       ///< (IEEE 802.15.4-2006) frame type: ACK
        IEEE802154_ACK_REQUEST = (1 << 5),     ///< (IEEE 802.15.4-2006) PSDU.FCF.bAR
        IEEE802154_DSN_OFFSET = 2,             ///< (IEEE 802.15.4-2006) PSDU.sequenceNumber
        IEEE802154_MAC_MIN_BE = 1,             ///< (IEEE 802.15.4-2006) macMinBE
        IEEE802154_MAC_MAX_BE = 5,             ///< (IEEE 802.15.4-2006) macMaxBE
        IEEE802154_MAC_MAX_CSMA_BACKOFFS = 4,  ///< (IEEE 802.15.4-2006) macMaxCSMABackoffs
        IEEE802154_MAC_MAX_FRAMES_RETRIES = 3, ///< (IEEE 802.15.4-2006) macMaxFrameRetries
        IEEE802154_A_UINT_BACKOFF_PERIOD = 20, ///< (IEEE 802.15.4-2006 7.4.1) MAC constants
        IEEE802154_A_TURNAROUND_TIME = 12,     ///< (IEEE 802.15.4-2006 6.4.1) PHY constants
        IEEE802154_PHY_SHR_DURATION = 10,      //

        ///< (IEEE 802.15.4-2006 6.4.2) PHY PIB attribute, specifically the O-QPSK PHY
        IEEE802154_PHY_SYMBOLS_PER_OCTET = 2, //

        ///< (IEEE 802.15.4-2006 6.4.2) PHY PIB attribute, specifically the O-QPSK PHY
        IEEE802154_MAC_ACK_WAIT_DURATION = (IEEE802154_A_UINT_BACKOFF_PERIOD + IEEE802154_A_TURNAROUND_TIME + IEEE802154_PHY_SHR_DURATION + (6 * IEEE802154_PHY_SYMBOLS_PER_OCTET)),

        ///< (IEEE 802.15.4-2006 7.4.2) macAckWaitDuration PIB attribute
        IEEE802154_SYMBOLS_PER_SEC = 62500 ///< (IEEE 802.15.4-2006 6.5.3.2) O-QPSK symbol rate
    };

    enum
    {
        CC2652_RAT_TICKS_PER_SEC = 4000000, ///< 4MHz clock
        CC2652_INVALID_RSSI = 127,
        CC2652_UNKNOWN_EUI64 = 0xFF,
        ///< If the EUI64 read from the ccfg is all ones then the customer did not set the address

        CC2652_CHANNEL_MIN = 11,
        CC2652_CHANNEL_MAX = 26,
    };

#define OT_EXT_ADDRESS_SIZE 8 ///< Size of an IEEE 802.15.4 Extended Address (bytes)

#define CC2652_RF_CMD0 0x0607            /* ram clocks for patches */
#define CC2652_SHORTADD_SRC_MATCH_NUM 10 /**/
#define CC2652_EXTADD_SRC_MATCH_NUM 10   /**/

    typedef struct __attribute__((aligned(4))) ext_src_match_data
    {
        uint32_t srcMatchEn[((CC2652_EXTADD_SRC_MATCH_NUM + 31) / 32)];
        uint32_t srcPendEn[((CC2652_EXTADD_SRC_MATCH_NUM + 31) / 32)];
        uint64_t extAddrEnt[CC2652_EXTADD_SRC_MATCH_NUM];
    } ext_src_match_data_t;

    typedef struct __attribute__((aligned(4))) short_src_match_data
    {
        uint32_t srcMatchEn[((CC2652_SHORTADD_SRC_MATCH_NUM + 31) / 32)];
        uint32_t srcPendEn[((CC2652_SHORTADD_SRC_MATCH_NUM + 31) / 32)];
        rfc_shortAddrEntry_t extAddrEnt[CC2652_SHORTADD_SRC_MATCH_NUM];
    } short_src_match_data_t;

    /* TX Power dBm lookup table - values from SmartRF Studio */
    typedef struct output_config
    {
        int dbm;
        uint16_t value;
    } output_config_t;

    //////////////////////////////////////////////////////////////////////////////////

    /* COMMANDS */
    extern const rfc_CMD_IEEE_ED_SCAN_t c_EdScanCmd;
    extern const rfc_CMD_IEEE_RX_t c_ReceiveCmd;
    extern const rfc_CMD_IEEE_CSMA_t c_CsmacaBackoffCmd;
    extern const rfc_CMD_IEEE_TX_t c_TransmitCmd;
    extern const rfc_CMD_IEEE_RX_ACK_t c_TransmitRxAckCmd;
    extern const rfc_CMD_SYNC_START_RAT_t c_StartRatCmd;
    extern const rfc_CMD_RADIO_SETUP_t c_RadioSetupCmd;
    extern const rfc_CMD_FS_POWERDOWN_t c_FsPowerdownCmd;
    extern const rfc_CMD_SYNC_STOP_RAT_t c_StopRatCmd;

    extern const output_config_t rgOutputPower[15];
#define OUTPUT_CONFIG_COUNT (sizeof(rgOutputPower) / sizeof(rgOutputPower[0]))

    extern uint32_t sIEEEOverrides[];

    //////////////////////////////////////////////////////////////////////////////////

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

    //////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif
#endif // LRADIO_DEF_H_