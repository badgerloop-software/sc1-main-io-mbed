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
    prints all flags from a Byte with their message associated with them.
    - 
    flagsType: what type of byte these flags are. (Specified in BMS)
    flags:     the data that is inputted 
    
*/
void CANDecoder::printFlags(const char *const flagsType, unsigned char flags, const char *const flagMessages[]) {
    //for all flags in the Byte
    if (flagsType != NULL) 
        printf("%s: %d\n", flagsType, flags);
    
    for (int i = 0; i < 8; i++) {
        //if a flag message input is null, the flag must be reserved or unused
        if (flagMessages[i] == NULL)
            continue;
        
        printf("%s:", flagMessages[i]);

        int offset = flagTextPosition - strlen(flagMessages[i]);
        for (int j = 0; j < offset; j++) {
            printf(" ");
        }
        //TODO: check if all signals have 1 for on and 0 for off
        printf("%s\n", (((1 << i) & flags) != 0) ? "on" : "off");
    }
}

/*
    prints the data from ID = x100. 
    8B failsafe status, DTC1, DTC2, Adaptive total capacity
    - 
    data: the pointer to the data byte
    
*/
void CANDecoder::printDecodedx100(unsigned char *data) {
    // should read flags
    //2nd byte of failsafe status is reserved so only print out 1st
    const char *const failsafeStatusMessages[8] = {
        "Voltage failsafe active",           
        "Current failsafe active",           
        "Relay failsafe active",             
        "Cell balancing active",             
        "Charge interlock failsafe active",  
        "Thermistor B-value table invalid",  
        "Input power supply failsafe active",
        NULL
    };
    printFlags("Failsafe status", data[0], failsafeStatusMessages);
    // set flags in data format
    set_voltage_failsafe(data[0] & (1 << 0));
    set_current_failsafe(data[0] & (1 << 1));
    set_relay_failsafe(data[0] & (1 << 2));
    set_cell_balancing_active(data[0] & (1 << 3));
    set_charge_interlock_failsafe(data[0] & (1 << 4));
    set_thermistor_b_value_table_invalid(data[0] & (1 << 5));
    set_input_power_supply_failsafe(data[0] & (1 << 6));

    const char *const DTCStatus1Messages[8] = {
        "Discharge limit enforcement fault",  
        "Charger safety relay fault",         
        "Internal hardware fault",            
        "Internal heatsink thermistor fault", 
        "Internal software fault",            
        "Highest cell voltage too high fault",
        "Lowest cell voltage too low fault",  
        "Pack too hot fault",                 
    };
    printFlags("DTC status 1", data[2], DTCStatus1Messages);
    // set flags in data format
    set_discharge_limit_enforcement_fault(data[2] & (1 << 0));
    set_charger_safety_relay_fault(data[2] & (1 << 1));
    set_internal_hardware_fault(data[2] & (1 << 2));
    set_internal_heatsink_fault(data[2] & (1 << 3));
    set_internal_software_fault(data[2] & (1 << 4));
    set_highest_cell_voltage_too_high_fault(data[2] & (1 << 5));
    set_lowest_cell_voltage_too_low_fault(data[2] & (1 << 6));
    set_pack_too_hot_fault(data[2] & (1 << 7));

    //2nd half of DTC status 1 is reserved

    const char *const DTCStatus2FirstMessages[8] = {
        "Internal communication fault",     
        "Cell balancing stuck off fault",   
        "Weak cell fault",                  
        "Low cell voltage fault",         
        "Open Wiring Fault",      
        "Current Sensor Fault",      
        "Highest Cell Voltage Over 5V Fault",
        "Cell ASIC Fault",          
    };
    printFlags("DTCStatus2", data[4], DTCStatus2FirstMessages);
    // set flags in data format
    set_internal_communication_fault(data[4] & (1 << 0));
    set_cell_balancing_stuck_off_fault(data[4] & (1 << 1));
    set_weak_cell_fault(data[4] & (1 << 2));
    set_low_cell_voltage_fault(data[4] & (1 << 3));
    set_open_wiring_fault(data[4] & (1 << 4));
    set_current_sensor_fault(data[4] & (1 << 5));
    set_highest_cell_voltage_over_5V_fault(data[4] & (1 << 6));
    set_cell_asic_fault(data[4] & (1 << 7));

    const char *const DTCStatus2SecondMessages[8] = {
        "Weak Pack Fault",              
        "Fan Monitor Fault",            
        "Thermistor Fault",             
        "External Communication Fault", 
        "Redundant Power Supply Fault", 
        "High Voltage Isolation Fault", 
        "Input Power Supply Fault",     
        "Charge Limit Enforcement Fault"  
    };
    printFlags(NULL, data[5], DTCStatus2SecondMessages);
    // set flags in data format
    set_weak_pack_fault(data[5] & (1 << 0));
    set_fan_monitor_fault(data[5] & (1 << 1));
    set_thermistor_fault(data[5] & (1 << 2));
    set_external_communication_fault(data[5] & (1 << 3));
    set_redundant_power_supply_fault(data[5] & (1 << 4));
    set_high_voltage_isolation_fault(data[5] & (1 << 5));
    set_input_power_supply_fault(data[5] & (1 << 6));
    set_charge_limit_enforcement_fault(data[5] & (1 << 7));

    float adaptiveTotalCapacity = getValueFrom2Bytes(data[6], data[7]) * 0.1;
    printf("Adaptive total capacity: %f Ahr\n", adaptiveTotalCapacity);
    set_adaptive_total_capacity(adaptiveTotalCapacity);
}

/*
    prints the data from ID = x101. 
    8B Pack current, Pack open voltage, pack soc, pack health, pack resistance
    - 
    data: the pointer to the data byte
    
*/
void CANDecoder::printDecodedx101(unsigned char *data) {
    float packCurrent = getValueFrom2Bytes(data[0], data[1]) * 0.1;
    printf("Pack current: %f Amps\n", packCurrent);
    set_pack_current(packCurrent);

    float packOpenVoltage = getValueFrom2Bytes(data[2], data[3]) * 0.1;
    printf("Pack open voltage: %f Volts\n", packOpenVoltage);
    set_pack_voltage(packOpenVoltage);
    
    int packSOC = data[4] * 0.5;
    printf("PackSOC: %d %%\n", packSOC);
    set_soc(packSOC);

    int packSOH = data[5];
    printf("PackSOH: %d %%\n", packSOH);
    set_soh(packSOH);

    int packResistance = getValueFrom2Bytes(data[6], data[7]);
    printf("PackResistance: %d mOhm\n", packResistance);
    set_pack_resistance(packResistance);
}

/*
    prints the data from ID = x101. 
    8B Pack amphours, populated cells, input supply voltage, average temp, internal temp, fanspeed
    - 
    data: the pointer to the data byte
    
*/
void CANDecoder::printDecodedx102(unsigned char *data) {

    float packAmphours = getValueFrom2Bytes(data[0], data[1]) * 0.1;
    printf("PackAmphours: %f Ahr\n", packAmphours);
    set_pack_capacity(packAmphours);

    printf("Populated cells: %d\n", data[2]);
    set_populated_cells(data[2]);

    int inputSupplyVoltage = getValueFrom2Bytes(data[3], data[4]) * 0.1;
    printf("InputSupplyVoltage: %d\n", inputSupplyVoltage);    

    //average temp
    printf("average temperature: %d C*\n", data[5]);
    
    //internal temp
    printf("internal temperature: %d C*\n", data[6]);

    //fan speed
    printf("fanSpeed: %d (0-6)\n", data[7]);
}

void CANDecoder::readHandler(int messageID, SharedPtr<unsigned char> data, int length) {
    printf("recieved messageID %x\n", messageID);
    printf("---------------------------------------------------------------------------------\n");
    switch (messageID) {
        case 0x100: 
            CANDecoder::printDecodedx100(data.get());
            break;

        case 0x101:      
            CANDecoder::printDecodedx101(data.get());
            break;

        case 0x102:
            CANDecoder::printDecodedx102(data.get());
            break;
        
        default:
            printf("unknown message ID recieved\n");
            break;
    }
    printf("---------------------------------------------------------------------------------\n\n");
}

