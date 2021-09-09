#ifndef CC_RADIO_H_
#define CC_RADIO_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum RadioError
{
    ERROR_RADIO_NONE = 0,
    ERROR_RADIO_INVALID_ARGS,
    ERROR_RADIO_NOT_IMPLEMENTED,
    ERROR_RADIO_FAILED,
    ERROR_RADIO_NO_BUFS,
    ERROR_RADIO_NO_ADDRESS,
    ERROR_RADIO_NO_ACK,
    ERROR_RADIO_BUSY,
    ERROR_RADIO_CHANNEL_ACCESS_FAILURE,
    ERROR_RADIO_INVALID_STATE,
    ERROR_RADIO_FCS,
    ERROR_RADIO_TIMEOUT,
} RadioError;

#define EXT_ADDRESS_SIZE (8)
typedef struct ExtAddress_s
{
    uint8_t m8[EXT_ADDRESS_SIZE]; ///< IEEE 802.15.4 Extended Address bytes
} __attribute__((packed)) ExtAddress;

extern ExtAddress ExtendedAddress;

#define MAC_KEY_SIZE 16 ///< Size of the MAC Key in bytes.
typedef struct MacKey_s
{
    uint8_t m8[MAC_KEY_SIZE]; ///< MAC Key bytes.
} __attribute__((packed)) MacKey;

typedef struct RadioIeInfo_s
{
    int64_t mNetworkTimeOffset; ///< The time offset to the Thread network time.
    uint8_t mTimeIeOffset;      ///< The Time IE offset from the start of PSDU.
    uint8_t mTimeSyncSeq;       ///< The Time sync sequence.
} RadioIeInfo;

typedef struct RadioFrame_s
{
    uint8_t *mPsdu;   ///< The PSDU.
    uint16_t mLength; ///< Length of the PSDU.

    uint8_t mChannel;   ///< Channel used to transmit/receive the frame.
    uint8_t mRadioType; ///< Radio link type - should be ignored by radio driver.

    /**
     * The union of transmit and receive information for a radio frame.
     */
    union
    {
        /**
         * Structure representing radio frame transmit information.
         */
        struct
        {
            const MacKey *mAesKey;   ///< The key used for AES-CCM frame security.
            RadioIeInfo *mIeInfo;    ///< The pointer to the Header IE(s) related information.
            uint32_t mTxDelay;         ///< The delay time for this transmission (based on `mTxDelayBaseTime`).
            uint32_t mTxDelayBaseTime; ///< The base time for the transmission delay.
            uint8_t mMaxCsmaBackoffs;  ///< Maximum number of backoffs attempts before declaring CCA failure.
            uint8_t mMaxFrameRetries;  ///< Maximum number of retries allowed after a transmission failure.

            /**
             * Indicates whether frame counter and CSL IEs are properly updated in the header.
             *
             * If the platform layer does not provide `OT_RADIO_CAPS_TRANSMIT_SEC` capability, it can ignore this flag.
             *
             * If the platform provides `OT_RADIO_CAPS_TRANSMIT_SEC` capability, then platform is expected to handle tx
             * security processing and assignment of frame counter. In this case the following behavior is expected:
             *
             * When `mIsHeaderUpdated` is set, it indicates that OpenThread core has already set the frame counter and
             * CSL IEs (if security is enabled) in the prepared frame. The counter is ensured to match the counter value
             * from the previous attempts of the same frame. The platform should not assign or change the frame counter
             * (but may still need to perform security processing depending on `mIsSecurityProcessed` flag).
             *
             * If `mIsHeaderUpdated` is not set, then the frame counter and key CSL IE not set in the frame by
             * OpenThread core and it is the responsibility of the radio platform to assign them. The platform
             * must update the frame header (assign counter and CSL IE values) before sending the frame over the air,
             * however if the the transmission gets aborted and the frame is never sent over the air (e.g., channel
             * access error) the platform may choose to not update the header. If the platform updates the header,
             * it must also set this flag before passing the frame back from the `RadioTxDone()` callback.
             *
             */
            bool mIsHeaderUpdated : 1;
            bool mIsARetx : 1;             ///< Indicates whether the frame is a retransmission or not.
            bool mCsmaCaEnabled : 1;       ///< Set to true to enable CSMA-CA for this packet, false otherwise.
            bool mCslPresent : 1;          ///< Set to true if CSL header IE is present.
            bool mIsSecurityProcessed : 1; ///< True if SubMac should skip the AES processing of this frame.
        } mTxInfo;

        /**
         * Structure representing radio frame receive information.
         */
        struct
        {
            /**
             * The timestamp when the frame was received in microseconds.
             *
             * The value SHALL be the time when the SFD was received when TIME_SYNC or CSL is enabled.
             * Otherwise, the time when the MAC frame was fully received is also acceptable.
             *
             */
            uint64_t mTimestamp;

            uint32_t mAckFrameCounter; ///< ACK security frame counter (applicable when `mAckedWithSecEnhAck` is set).
            uint8_t mAckKeyId;         ///< ACK security key index (applicable when `mAckedWithSecEnhAck` is set).
            int8_t mRssi;              ///< Received signal strength indicator in dBm for received frames.
            uint8_t mLqi;              ///< Link Quality Indicator for received frames.

            // Flags
            bool mAckedWithFramePending : 1; ///< This indicates if this frame was acknowledged with frame pending set.
            bool mAckedWithSecEnhAck : 1;    ///< This indicates if this frame was acknowledged with secured enhance ACK.
        } mRxInfo;
    } mInfo;

    uint8_t *mRxPayload; /* [WizIO] RX */
    void *mTxUser;       /* [WizIO] for Transmit frame user callback variable */
    RadioError mTxError; /* [WizIO] for Transmit sync timeout */
} RadioFrame;

typedef enum RadioState
{
    RADIO_STATE_DISABLED = 0,
    RADIO_STATE_SLEEP = 1,
    RADIO_STATE_RECEIVE = 2,
    RADIO_STATE_TRANSMIT = 3,
    RADIO_STATE_INVALID = 255,
} otRadioState;

typedef uint8_t RadioCaps;
enum
{
    RADIO_CAPS_NONE = 0,                  ///< Radio supports no capability.
    RADIO_CAPS_ACK_TIMEOUT = 1 << 0,      ///< Radio supports AckTime event.
    RADIO_CAPS_ENERGY_SCAN = 1 << 1,      ///< Radio supports Energy Scans.
    RADIO_CAPS_TRANSMIT_RETRIES = 1 << 2, ///< Radio supports tx retry logic with collision avoidance (CSMA).
    RADIO_CAPS_CSMA_BACKOFF = 1 << 3,     ///< Radio supports CSMA backoff for frame transmission (but no retry).
    RADIO_CAPS_SLEEP_TO_TX = 1 << 4,      ///< Radio supports direct transition from sleep to TX with CSMA.
    RADIO_CAPS_TRANSMIT_SEC = 1 << 5,     ///< Radio supports tx security.
    RADIO_CAPS_TRANSMIT_TIMING = 1 << 6,  ///< Radio supports tx at specific time.
    RADIO_CAPS_RECEIVE_TIMING = 1 << 7,   ///< Radio supports rx at specific time.
};

void RadioInit(void);
void RadioProcess(void);

void RadioSetPanId(uint16_t aPanid);
void RadioSetShortAddress(uint16_t aAddress);
void RadioSetExtendedAddress(const ExtAddress *aAddress);
void RadioInitExtAddress(uint8_t *aIeeeEui64);
uint64_t RadioReadUint64Le(const uint8_t *aSource);
uint64_t RadioGetExtendedAddress(void);

bool RadioIsEnabled(void);
RadioError RadioEnable(void);
RadioError RadioDisable(void);
RadioError RadioSleep(void);
RadioError RadioReceive(uint8_t aChannel);
RadioError RadioSetTransmitPower(int8_t aPower);
RadioError RadioGetTransmitPower(int8_t *aPower);
RadioFrame *RadioGetTransmitBuffer(void);
RadioError RadioTransmit(RadioFrame *aFrame);
RadioError RadioEnergyScan(uint8_t aScanChannel, uint16_t aScanDuration);

int8_t RadioGetRssi(void);
RadioCaps RadioGetCaps(void);
void RadioSetPromiscuous(bool aEnable);
void RadioSetPromiscuous(bool aEnable);
void RadioClearSrcMatchExtEntries(void);
void RadioClearSrcMatchShortEntries(void);
RadioError RadioClearSrcMatchExtEntry(const ExtAddress *aExtAddress);
RadioError RadioAddSrcMatchExtEntry(const ExtAddress *aExtAddress);
RadioError RadioClearSrcMatchShortEntry(uint16_t aShortAddress);
RadioError RadioAddSrcMatchShortEntry(uint16_t aShortAddress);
void RadioEnableSrcMatch(bool aEnable);

// callbacks
void RadioReceiveDone(RadioFrame *, RadioError);
void RadioTxStarted(RadioFrame *);
void RadioTxDone(RadioFrame *, RadioFrame *, RadioError);
void RadioEnergyScanDone(int8_t);

bool RadioBegin(uint8_t Channel, int8_t Power);

#endif // CC_RADIO_H_