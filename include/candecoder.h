#ifndef __CAN_DECODE_H__
#define __CAN_DECODE_H__

#include "canmanager.h"
#include "dataFormat.h"
#include "digital.h"

class CANDecoder : public CANManager {
    private:
        // position for how far from the start of the screen the on/off string should be when printFlags is called
        const int flagTextPosition = 50;

        int getValueFrom2Bytes(unsigned char bigByte, unsigned char smallByte);

        void printFlags(const char *const flagsType, unsigned char flags, const char *const flagMessages[]);

        void printDecodedx100(unsigned char *data);
        void printDecodedx101(unsigned char *data);
        void printDecodedx102(unsigned char *data);
        void printDecodedx103(unsigned char *data);
        void printDecodedx104(unsigned char *data);

    public:
        CANDecoder(PinName rd, PinName td, int frequency): CANManager(rd, td, frequency) {};
        
        void readHandler(int messageID, SharedPtr<unsigned char> data, int length);
        void send_mainio_data();
};

#endif