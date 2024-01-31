#include "candecoder.h"

/*
    gets value from 2 bytes.
    - 
    bigByte:       the byte that is at the front/shifted
    smallByte:     the data that is at the end
    
*/
int CANDecoder::getValueFrom2Bytes(unsigned char bigByte, unsigned char smallByte) {
    return ((bigByte << 8) + smallByte);
}

/*
    decodes the data from ID = x100. 
    8B failsafe status, DTC1, DTC2, Adaptive total capacity
    - 
    data: the pointer to the data byte
    
*/
void CANDecoder::decode100(unsigned char *data) {
    // Failsafe statuses
    set_voltage_failsafe(data[0] & (1 << 0));
    set_current_failsafe(data[0] & (1 << 1));
    set_relay_failsafe(data[0] & (1 << 2));
    set_cell_balancing_active(data[0] & (1 << 3));
    set_charge_interlock_failsafe(data[0] & (1 << 4));
    set_thermistor_b_value_table_invalid(data[0] & (1 << 5));
    set_input_power_supply_failsafe(data[0] & (1 << 6));

    // DTC status 1
    set_discharge_limit_enforcement_fault(data[2] & (1 << 0));
    set_charger_safety_relay_fault(data[2] & (1 << 1));
    set_internal_hardware_fault(data[2] & (1 << 2));
    set_internal_heatsink_fault(data[2] & (1 << 3));
    set_internal_software_fault(data[2] & (1 << 4));
    set_highest_cell_voltage_too_high_fault(data[2] & (1 << 5));
    set_lowest_cell_voltage_too_low_fault(data[2] & (1 << 6));
    set_pack_too_hot_fault(data[2] & (1 << 7));

    //2nd half of DTC status 1 is reserved by BMS

    // DTC status 2
    set_internal_communication_fault(data[4] & (1 << 0));
    set_cell_balancing_stuck_off_fault(data[4] & (1 << 1));
    set_weak_cell_fault(data[4] & (1 << 2));
    set_low_cell_voltage_fault(data[4] & (1 << 3));
    set_open_wiring_fault(data[4] & (1 << 4));
    set_current_sensor_fault(data[4] & (1 << 5));
    set_highest_cell_voltage_over_5V_fault(data[4] & (1 << 6));
    set_cell_asic_fault(data[4] & (1 << 7));

    set_weak_pack_fault(data[5] & (1 << 0));
    set_fan_monitor_fault(data[5] & (1 << 1));
    set_thermistor_fault(data[5] & (1 << 2));
    set_external_communication_fault(data[5] & (1 << 3));
    set_redundant_power_supply_fault(data[5] & (1 << 4));
    set_high_voltage_isolation_fault(data[5] & (1 << 5));
    set_input_power_supply_fault(data[5] & (1 << 6));
    set_charge_limit_enforcement_fault(data[5] & (1 << 7));

    float adaptiveTotalCapacity = getValueFrom2Bytes(data[6], data[7]) * 0.1;
    set_adaptive_total_capacity(adaptiveTotalCapacity);
}

/*
    decodes the data from ID = x101. 
    8B Pack current, Pack open voltage, pack soc, pack health, pack resistance
    - 
    data: the pointer to the data byte
    
*/
void CANDecoder::decode101(unsigned char *data) {
    float packCurrent = getValueFrom2Bytes(data[0], data[1]) * 0.1;
    set_pack_current(packCurrent);

    float packOpenVoltage = getValueFrom2Bytes(data[2], data[3]) * 0.1;
    set_pack_voltage(packOpenVoltage);

    set_pack_power(packCurrent * packOpenVoltage);
    
    int packSOC = data[4] * 0.5;
    set_soc(packSOC);

    int packSOH = data[5];
    set_soh(packSOH);

    int packResistance = getValueFrom2Bytes(data[6], data[7]);
    set_pack_resistance(packResistance);
}

/*
    decodes the data from ID = x102. 
    8B Pack amphours, populated cells, input supply voltage, average temp, internal temp, fanspeed
    - 
    data: the pointer to the data byte
    
*/
void CANDecoder::decode102(unsigned char *data) {

    float packAmphours = getValueFrom2Bytes(data[0], data[1]) * 0.1;
    set_pack_capacity(packAmphours);

    set_populated_cells(data[2]);

    int inputSupplyVoltage = getValueFrom2Bytes(data[3], data[4]) * 0.1;
    set_bms_input_voltage(inputSupplyVoltage);

    //average temp
    set_pack_temp(data[5]);
    
    //internal temp
    set_pack_internal_temp(data[6]);

    //fan speed
    set_fan_speed(data[7]);
}


/*
    Decode BMS messages
*/
void CANDecoder::decodeBMS(int messageID, SharedPtr<unsigned char> data, int length) {
    switch (messageID) {
        case 0x100: 
            CANDecoder::decode100(data.get());
            break;
        case 0x101:      
            CANDecoder::decode101(data.get());
            break;
        case 0x102:
            CANDecoder::decode102(data.get());
            break;
        default:
            break;
    }
}

void CANDecoder::decode200(unsigned char *data) {

}

/*
    Decode MCC messages (0x200 offset)
*/
void CANDecoder::decodeMCC(int messageID, SharedPtr<unsigned char> data, int length) {
    switch(messageID) {
        case 0x200:
            decode200(data.get());
            break;
        case 0x201:
            // Cruise mode. 0 for both off, 1 speed, 2 power
            set_crz_spd_mode(*data & 0x1);
            set_crz_pwr_mode(*data & 0x2);
            break;
        case 0x202:
            set_state(*data);
            break;
        case 0x203:
            set_accelerator(*(float*)data.get());
            break;
        case 0x204:
            //set_regen_braking(*(float*)data.get());
            break;
        case 0x205:
            set_crz_spd_setpt(*(float*)data.get());
            break;
        case 0x206:
            set_speed(*(float*)data.get());
            break;
        default:
            break;
    }
}


void CANDecoder::readHandler(int messageID, SharedPtr<unsigned char> data, int length) {
    // IDs are 11 bits, first 3 are used to ID the board, rest for message
    switch (messageID & BOARD_ID_MASK) {
        case 0x100:
            decodeBMS(messageID, data, length);
            break;
        case 0x200:
            decodeMCC(messageID, data, length);
            break;
        case 0x300:
            break;
        case 0x400:
            break;
        default:
            break;
    }
}

void CANDecoder::send_mainio_data() {
    // parking brakes
    bool parking_brake = digital_data.BRK_STATUS2;
    this->sendMessage(0x40, (void*)&parking_brake, 1, 1ms);
}
