#ifndef __CAN_DECODE_H__
#define __CAN_DECODE_H__

#include "canmanager.h"
#include "dataFormat.h"
#include "digital.h"

#define BOARD_ID_MASK 0x700


class CANDecoder : public CANManager {
    private:
        int getValueFrom2Bytes(unsigned char bigByte, unsigned char smallByte);

        // Helper functions for compacted messages
        void decode100(unsigned char *data);
        void decode101(unsigned char *data);
        void decode102(unsigned char *data);
        void decode200(unsigned char *data);

        // Helper functions to process data from each board
        void decodeBMS(int messageID, SharedPtr<unsigned char> data, int length);
        void decodeMCC(int messageID, SharedPtr<unsigned char> data, int length);
        void decodeHV(int messageID, SharedPtr<unsigned char> data, int length);
        void decodeMPPT(int messageID, SharedPtr<unsigned char> data, int length);

    public:
        CANDecoder(PinName rd, PinName td, int frequency = DEFAULT_CAN_FREQ) : CANManager(rd, td, frequency) {};
        
        void readHandler(int messageID, SharedPtr<unsigned char> data, int length);
        void send_mainio_data();
};

#endif