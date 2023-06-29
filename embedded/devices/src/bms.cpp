#include "bms.h"
#include "Callback.h"

#define BMS_BANK 1
#define MPI_1 2
#define MPI_2 3
#define MPO_2 4
#define BMS_CHRG_EN 5
#define BMS_DSCHRG_EN 6

// union CurrentUnion {
//     float f;
//     char c[4];
// };

/**
 * BMS CAN device
 *
 * Authors: Khiem Vu and Jonathan Wang
 */
BMS::BMS(Can &c) : device(c) {
}

int BMS::callback(CANMessage &msg) {
    // unsigned char c_temp[4];
  switch (msg.id) {
  case 0x100:
    failsafeStatuses = (msg.data[0] | msg.data[1] << 8);
    set_voltage_failsafe(failsafeStatuses & 0x01);
    set_current_failsafe(failsafeStatuses & 0x02);
    set_relay_failsafe(failsafeStatuses & 0x04);
    set_charge_interlock_failsafe(failsafeStatuses & 0x10);
    set_input_power_supply_failsafe(failsafeStatuses & 0x40);

    DTC1 = (msg.data[2] | msg.data[3] << 8);
    set_discharge_limit_enforcement_fault(DTC1 & 0x01);
    set_charger_safety_relay_fault(DTC1 & 0x02);
    set_internal_hardware_fault(DTC1 & 0x04);
    set_internal_heatsink_fault(DTC1 & 0x08);
    set_internal_software_fault(DTC1 & 0x10);
    set_highest_cell_voltage_too_high_fault(DTC1 & 0x20);
    set_lowest_cell_voltage_too_low_fault(DTC1 & 0x40);
    set_pack_too_hot_fault(DTC1 & 0x80);

    DTC2 = (msg.data[4] | msg.data[5] << 8);
    set_internal_communication_fault(DTC1 & 0x0001);
    set_cell_balancing_stuck_off_fault(DTC1 & 0x0002);
    set_weak_cell_fault(DTC1 & 0x0004);
    set_low_cell_voltage_fault(DTC1 & 0x0008);
    set_open_wiring_fault(DTC1 & 0x0010);
    set_current_sensor_fault(DTC1 & 0x0020);
    set_highest_cell_voltage_over_5V_fault(DTC1 & 0x0040);
    set_cell_asic_fault(DTC1 & 0x0080);
    set_weak_pack_fault(DTC1 & 0x0100);
    set_fan_monitor_fault(DTC1 & 0x0200);
    set_thermistor_fault(DTC1 & 0x0400);
    set_external_communication_fault(DTC1 & 0x0800);
    set_redundant_power_supply_fault(DTC1 & 0x1000);
    set_high_voltage_isolation_fault(DTC1 & 0x2000);
    set_input_power_supply_fault(DTC1 & 0x4000);
    set_charge_limit_enforcement_fault(DTC1 & 0x8000);
    break;

  case 0x101:
    // c_temp[0] = msg.data[0];
    // c_temp[1] = msg.data[1];
    // c_temp[2] = 0;
    // c_temp[3] = 0;
    // packCurrent = *((float*)c_temp) / 10;
    // CurrentUnion temp_union;
    // temp_union.c[0] = msg.data[0];
    // temp_union.c[1] = msg.data[1];
    // packCurrent = temp_union.f /10.0;
    //printf("Current msg.data[1]: %x | msg.data[0]: %x\n", msg.data[1], msg.data[0]);
    packCurrent = (msg.data[1] | msg.data[0] << 8) / 10.0;
    printf("Pack Current (BMS): %f\n", packCurrent);
    packVoltage =
        (msg.data[3] | msg.data[2] << 8) / 10.0; // default unit: 0.1 V
    set_pack_current(packCurrent);
    set_pack_voltage(packVoltage);

    packStateOfCharge = (float)msg.data[4] / 2;
    set_soc(packStateOfCharge);

    packHealth = msg.data[5];
    set_soh(packHealth);
    break;
  
  case 0x102: 
    packAmpHours =
        (msg.data[0] | msg.data[1] << 8) / 10.0; // default unit: 0.1 Ahr
    set_tstamp_hr(packAmpHours);

    populatedCells = msg.data[2];
    set_populated_cells(populatedCells);

    powerInputVoltage =
        (msg.data[3] | msg.data[4] << 8) / 10.0; // default unit: 0.1v
    set_bms_input_voltage(powerInputVoltage);
    break;
  
  case 0x103: 
    avgTemperature = msg.data[0];      // default unit: 1 C
    internalTemperature = msg.data[1]; // default unit: 1 C
    fanSpeed = msg.data[2];            // default units: 0-6 speed
    set_pack_temp(avgTemperature);
    set_pack_internal_temp(internalTemperature);
    set_fan_speed(fanSpeed);
    break;
  
  case 0x104: 
    packResistance =
        (float)(msg.data[0] | msg.data[1] << 8) / 1000; // default unit: 1 mOhm
    set_pack_resistance(packResistance);

    // TODO: average Cell internal resistnace byte 2 & byte 3

    adaptiveTotalCapacity =
        (msg.data[4] | msg.data[5] << 8) / 10.0; // default unit: 0.1 Amp-hours
    set_adaptive_total_capacity(adaptiveTotalCapacity);
    break;
  
  case 0x500: 
    canID = (int)msg.data[0];
    batteryVoltage[canID] = (msg.data[5] | msg.data[6] << 8);
    break;
  
  default: 
    return 1;
  }

  return 0;
}

float BMS::getPackStateOfCharge() { return packStateOfCharge; }
float BMS::getPackCurrent() { return packCurrent; }
float BMS::getPackVoltage() { return packVoltage; }
uint8_t BMS::getPackAmpHours() { return packAmpHours; }
bool BMS::getFailsafeStatuses() { return failsafeStatuses; }
bool BMS::getDTC1() { return DTC1; }
bool BMS::getDTC2() { return DTC2; }
float BMS::getPackHealth() { return packHealth; }
float BMS::getPowerInputVoltage() { return powerInputVoltage; }
float BMS::getAvgTemperature() { return avgTemperature; }
float BMS::getInternalTemperature() { return internalTemperature; }
uint8_t BMS::getFanSpeed() { return fanSpeed; }
float BMS::getPackResistance() { return packResistance; }
float BMS::getAdaptiveTotalCapacity() { return adaptiveTotalCapacity; }
uint16_t BMS::getPopulatedCells() { return populatedCells; }