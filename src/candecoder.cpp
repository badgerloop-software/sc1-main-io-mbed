#include "candecoder.h"
#include "dataFormat.h"

Timer timerBMS;
Timer timerHV;
Timer timerMCC;
Timer timerMPPT;

/*
    gets value from 2 bytes.
    - 
    bigByte:       the byte that is at the front/shifted
    smallByte:     the data that is at the end
    
*/
int CANDecoder::getValueFrom2Bytes(unsigned char bigByte, unsigned char smallByte) {
    return (int16_t)((bigByte << 8) | smallByte);
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
    
    float packSOC = get_soc() + ((packCurrent * CAN_READ_INTERVAL / 3600) / MAX_CAPACITY_AH); 
    set_soc(packSOC);

    float packSOH = data[5];
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
    set_pack_amphours(packAmphours);

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
    setsCellVoltage using the setter function.
    - 
    index: index 0-31 of the cell group number
    value: float value of of that cell voltage
    
*/
void CANDecoder::setCellVoltage(int index, float value) {
    switch (index) {
        case 0:
            set_cell_group1_voltage(value);
            break;
        case 1:
            set_cell_group2_voltage(value);
            break;
        case 2:
            set_cell_group3_voltage(value);
            break;
        case 3:
            set_cell_group4_voltage(value);
            break;
        case 4:
            set_cell_group5_voltage(value);
            break;
        case 5:
            set_cell_group6_voltage(value);
            break;
        case 6:
            set_cell_group7_voltage(value);
            break;
        case 7:
            set_cell_group8_voltage(value);
            break;
        case 8:
            set_cell_group9_voltage(value);
            break;
        case 9:
            set_cell_group10_voltage(value);
            break;
        case 10:
            set_cell_group11_voltage(value);
            break;
        case 11:
            set_cell_group12_voltage(value);
            break;
        case 12:
            set_cell_group13_voltage(value);
            break;
        case 13:
            set_cell_group14_voltage(value);
            break;
        case 14:
            set_cell_group15_voltage(value);
            break;
        case 15:
            set_cell_group16_voltage(value);
            break;
        case 16:
            set_cell_group17_voltage(value);
            break;
        case 36:
            set_cell_group18_voltage(value);
            break;
        case 37:
            set_cell_group19_voltage(value);
            break;
        case 38:
            set_cell_group20_voltage(value);
            break;
        case 39:
            set_cell_group21_voltage(value);
            break;
        case 40:
            set_cell_group22_voltage(value);
            break;
        case 41:
            set_cell_group23_voltage(value);
            break;
        case 42:
            set_cell_group24_voltage(value);
            break;
        case 43:
            set_cell_group25_voltage(value);
            break;
        case 48:
            set_cell_group26_voltage(value);
            break;
        case 49:
            set_cell_group27_voltage(value);
            break;
        case 50:
            set_cell_group28_voltage(value);
            break;
        case 51:
            set_cell_group29_voltage(value);
            break;
        case 52:
            set_cell_group30_voltage(value);
            break;
        case 53:
            set_cell_group31_voltage(value);
            break;
        default:
            break;
    }    
}

//TODO: verify this
/*
    decodes the data from ID = x103. 
    8B cellId cellVoltages
    - 
    data: the pointer to the data byte
    
*/
void CANDecoder::decode103(unsigned char *data) {

    uint8_t cellId = data[0];
    float value = getValueFrom2Bytes(data[1], data[2]) * 0.0001;

    setCellVoltage(cellId, value);
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
        case 0x103:
            CANDecoder::decode103(data.get());
            break;
        default:
            break;
    }
}

void CANDecoder::decode200(unsigned char *data) {
    struct Digital_Data parsedData = *(Digital_Data*)data;

    set_main_telem(parsedData.motorPower);
    set_fr_telem(parsedData.forwardAndReverse);
    set_eco(parsedData.ecoMode);
    set_foot_brake(parsedData.brakeStatus);
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
            set_mcc_state(*data);
            break;
        case 0x203:
            set_accelerator_pedal(*(float*)data.get());
            break;
        case 0x204:
            set_regen_brake(*(float*)data.get());
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

//TODO: verify this
/*
    decodes the data from ID = x300. 
    15B struct from HV's values
    - 
    data: the pointer to the data byte
    
*/
void CANDecoder::decode300(unsigned char *data) {
    struct HV_Digital_Data *formattedData = (HV_Digital_Data*)data;
    //start decoding all the flags
    set_driver_eStop(!formattedData->driver_EStop);
    set_external_eStop(!formattedData->external_EStop);
    set_mcu_stat_fdbk(formattedData->start_shutdown_status);
    set_isolation(!formattedData->isolation_status);
    set_discharge_enabled(!formattedData->battery_discharge_enabled);
    set_discharge_enable(formattedData->battery_discharge_enable);
    set_charge_enabled(!formattedData->battery_charge_enabled);
    set_charge_enable(formattedData->battery_charge_enable);
    set_bms_mpio1(formattedData->BMS_MPO1);
    set_low_contactor(formattedData->lv_contactor);
    set_motor_controller_contactor(formattedData->mc_contactor);
    set_mppt_contactor(formattedData->mppt_contactor);
    set_crash(!formattedData->crash_sensor);
    set_use_supp(formattedData->use_supp);
    set_use_dcdc(formattedData->use_dcdc);
    set_mcu_hv_en(formattedData->mcu_hv_en);

    // Clear restart enable if any of the faults asserted (0)
    if (!formattedData->driver_EStop || 
        !formattedData->external_EStop || 
        !formattedData->crash_sensor || 
        !formattedData->battery_discharge_enabled || 
        !formattedData->battery_charge_enabled || 
        !formattedData->isolation_status) {
            set_restart_enable(false);
        }
}

/*
    Decode HV messages (0x300 offset)
*/
void CANDecoder::decodeHV(int messageID, SharedPtr<unsigned char> data, int length) {
    switch(messageID) {
        case 0x300:
            decode300(data.get());
            break;
        case 0x301:
            set_dcdc_current(*(float*)(data.get()));
            break;
        case 0x302:
            set_supplemental_current(*(float*)(data.get()));
            break;
        case 0x303:
            set_supplemental_voltage(VSUPP_MULTIPLIER * (*(float*)(data.get())));
            break;
        default:
            break;
    }
}

void CANDecoder::decodeMPPT(int messageID, SharedPtr<unsigned char> data, int length) {
    switch(messageID) {
        // array 1
        case 0x401: // array 1 voltage
            set_string1_V_in(*(float*)(data.get()));
            break;
        case 0x402: // array 1 current
            set_string1_I_in(*(float*)(data.get()));
            break;
        case 0x403: // array 1 temp
            set_string1_temp(*(float*)(data.get()));
            break;

        // array 2
        case 0x404: // array 2 voltage
            set_string2_V_in(*(float*)(data.get()));
            break;
        case 0x405: // array 2 current
            set_string2_I_in(*(float*)(data.get()));
            break;
        case 0x406: // array 2 temp
            set_string2_temp(*(float*)(data.get()));
            break;

        // array 3
        case 0x407: // array 3 voltage
            set_string3_V_in(*(float*)(data.get()));
            break;
        case 0x408: // array 3 current
            set_string3_I_in(*(float*)(data.get()));
            break;
        case 0x409: // array 3 temp
            set_string3_temp(*(float*)(data.get()));
            break;
            
        default:
            break;
    }
}

void CANDecoder::readHandler(int messageID, SharedPtr<unsigned char> data, int length) {
    // IDs are 11 bits, first 3 are used to ID the board, rest for message
    switch (messageID & BOARD_ID_MASK) {
        case 0x100:
            timerBMS.reset();
            set_bms_can_heartbeat(true);
            decodeBMS(messageID, data, length);
            break;
        case 0x200:
            timerMCC.reset();
            set_mcc_can_heartbeat(true);
            decodeMCC(messageID, data, length);
            break;
        case 0x300:
            timerHV.reset();
            set_hv_can_heartbeat(true);
            decodeHV(messageID, data, length);
            break;
        case 0x400:
            timerMPPT.reset();
            set_mppt_can_heartbeat(true);
            decodeMPPT(messageID, data, length);
            break;
        default:
            break;
    }
}

void CANDecoder::send_mainio_data() {
    bool startup_signal = get_restart_enable();

    // MCU_HV_EN from software
    this->sendMessage(0x025, (void*)&startup_signal, 1);
}
