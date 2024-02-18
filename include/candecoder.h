#ifndef __CAN_DECODE_H__
#define __CAN_DECODE_H__

#include "canmanager.h"
#include "dataFormat.h"

#define BOARD_ID_MASK 0x700

class CANDecoder : public CANManager {
    private:
        int getValueFrom2Bytes(unsigned char bigByte, unsigned char smallByte);
        void setCellVoltage(int index, float value);

        // Helper functions for compacted messages
        void decode100(unsigned char *data);
        void decode101(unsigned char *data);
        void decode102(unsigned char *data);
        void decode103(unsigned char *data);
        void decode200(unsigned char *data);
        void decode300(unsigned char *data);
        

        // Helper functions to process data from each board
        void decodeBMS(int messageID, SharedPtr<unsigned char> data, int length);
        void decodeMCC(int messageID, SharedPtr<unsigned char> data, int length);
        void decodeHV(int messageID, SharedPtr<unsigned char> data, int length);
        void decodeMPPT(int messageID, SharedPtr<unsigned char> data, int length);


        // MCC DATA STRUCT
        struct Digital_Data {
            bool cruiseEnabled : 1;
            bool motorPower : 1;
            bool forwardAndReverse : 1;
            bool ecoMode : 1;
            bool brakeStatus : 1;
        };

        // HV DATA STRUCT
        struct HV_Digital_Data {
            bool driver_EStop : 1;
            bool external_EStop : 1;
            bool start_shutdown_status : 1;
            bool isolation_status : 1;
            bool battery_discharge_enabled : 1;
            bool battery_discharge_enable : 1;
            bool battery_charge_enabled : 1;
            bool battery_charge_enable : 1;
            bool BMS_MPO1 : 1;
            bool lv_contactor : 1;
            bool mc_contactor : 1;
            bool mppt_contactor : 1;
            bool crash_sensor : 1;
            bool use_supp : 1;
            bool use_dcdc : 1;
            bool mcu_hv_en : 1;
        };

    public:
        CANDecoder(PinName rd, PinName td, int frequency = DEFAULT_CAN_FREQ) : CANManager(rd, td, frequency) {};
        
        void readHandler(int messageID, SharedPtr<unsigned char> data, int length);
        void send_mainio_data();
};

#endif