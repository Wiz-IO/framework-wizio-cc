////////////////////////////////////////////////////////////////////////////////////////
//
//      2021 Georgi Angelov
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////////////

#include <ieee_ot_radio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 127

//#define FRAME802154_TYPE_BEACONFRAME (0x00)
//#define FRAME802154_TYPE_DATAFRAME (0x01)
//#define FRAME802154_TYPE_ACKFRAME (0x02)
//#define FRAME802154_TYPE_CMDFRAME (0x03)

typedef struct __attribute__((packed))
{
    uint8_t frame_type : 3;                  /**< 3 bit. Frame type field, see 802.15.4 */
    uint8_t security_enabled : 1;            /**< 1 bit. True if security is used in this frame */
    uint8_t frame_pending : 1;               /**< 1 bit. True if sender has more data to send */
    uint8_t ack_required : 1;                /**< 1 bit. Is an ack frame required? */
    uint8_t panid_compression : 1;           /**< 1 bit. Is this a compressed header? */
    uint8_t reserved : 1;                    /**< 1 bit. Unused bit */
                                             //
    uint8_t sequence_number_suppression : 1; /**< 1 bit. Does the header omit sequence number?, see 802.15.4e */
    uint8_t ie_list_present : 1;             /**< 1 bit. Does the header contain Information Elements?, see 802.15.4e */
    uint8_t dest_addr_mode : 2;              /**< 2 bit. Destination address mode, see 802.15.4 */
    uint8_t frame_version : 2;               /**< 2 bit. 802.15.4 frame version */
    uint8_t src_addr_mode : 2;               /**< 2 bit. Source address mode, see 802.15.4 */
} fcf_t;

typedef struct __attribute__((packed)) LHeader_t
{
    union
    {
        fcf_t bFCF;
        uint16_t macFcf;
    };
    uint8_t macSeq;
    uint16_t macDstPanId;
    uint16_t macDstAddr;
    uint16_t macSrcAddr;
} LHeader_t;

typedef struct __attribute__((packed)) LFrame_t
{
    LHeader_t header;
    uint8_t payload[MAX_PAYLOAD_SIZE - sizeof(LHeader_t)];

    int error;

    uint16_t rxSize;
    int8_t rxRssi;
    uint8_t rxLqi;
} LFrame_t;

typedef void (*frame_callback)(LFrame_t *frame);

class EasyLink
{
private:
    Radio radio;
    uint8_t _macSeqNum;
    uint16_t _Panid;
    uint16_t _Address;
    uint8_t _Channel;
    int8_t _Power;
    int8_t *_Key;

    int waitTx(LFrame_t *frame)
    {
        uint32_t timeout = 50000;
        while (--timeout)
        {
            radio.process();
            if (-1 != frame->error)
                return frame->error;
        }
        return -3; // timeout
    }

public:
    EasyLink(uint16_t aPanid, uint16_t aAddress, uint8_t aChannel = 11, int8_t aPower = 0)
    {
        _macSeqNum = 0;
        _Panid = aPanid;
        _Address = aAddress;
        _Channel = aChannel;
        _Power = aPower;
        _Key = NULL;
    }
    ~EasyLink() { radio.disable(); };

    inline uint16_t getAddress() { return _Address; }

    int transmit(const void *data, uint8_t size, uint16_t dstAddr = 0x0000 /* default to coordinator */)
    {
        if (dstAddr == _Address)
            return -1;

        LFrame_t frame;
        memset(&frame, 0, sizeof(LFrame_t));
        frame.header.macFcf = (0xFFFF == dstAddr) ? 0x8841 : 0x8861;
        frame.header.macDstAddr = dstAddr;
        frame.header.macDstPanId = _Panid;
        frame.header.macSrcAddr = _Address;
        frame.header.macSeq = ++_macSeqNum;
        frame.error = -1;

        if (_Key)
        {
            // TODO
            frame.header.bFCF.security_enabled = 1;
        }
        else
        {
            if (data && size)
                memcpy(&frame.payload, (uint8_t *)data, size);
        }

        // send frame
        otRadioFrame *tx_radio_frame = otPlatRadioGetTransmitBuffer();
        tx_radio_frame->mUser = &frame;
        tx_radio_frame->mPsdu = (uint8_t *)&frame.header;
        tx_radio_frame->mLength = sizeof(LHeader_t) + size;
        if (radio.transmit())
            return -2;
        if (0xFFFF != dstAddr)
            return waitTx(&frame);
        return 0; // done
    }

    inline bool begin() { return radio.begin(_Panid, _Address, _Channel, _Power); }

    inline void process() { radio.process(); }
};

void otPlatRadioEnergyScanDone(int8_t aEnergyScanMaxRssi)
{ /* nothing */
}

void otPlatRadioTxStarted(otRadioFrame *aFrame)
{ /* nothing */
}

void otPlatRadioTxDone(otRadioFrame *aFrame, otRadioFrame *aAckFrame, otError aError)
{
    if (aFrame->mUser)
        ((LFrame_t *)(aFrame->mUser))->error = aError; // return aError
}

void otPlatRadioReceiveDone(otRadioFrame *aFrame, otError aError)
{
    if (0 == aError)
    {
        //DUMP("PSDU", aFrame->mPsdu, aFrame->mLength);
        LFrame_t f;
        memcpy(&f, aFrame->mPsdu, sizeof(LFrame_t));
        f.rxSize = aFrame->mLength - sizeof(LHeader_t) - 2;
        f.rxLqi = aFrame->mInfo.mRxInfo.mLqi;
        f.rxRssi = aFrame->mInfo.mRxInfo.mRssi;
        f.error = 0;
        extern void onReceive(LFrame_t * frame);
        onReceive(&f);
    }
}