#include "bms.h"

/**
* BMS CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
int BMS::callback(CANMessage &msg) {
    printf("Processing %x\n", msg.id);
  switch (msg.id) {
  case 0x100:
    printf("Got it\n");
    // packStateOfCharge = (float) (*((int*) msg.data) & (0x1 << 7));
    packStateOfCharge = (float)(msg.data[1] | msg.data[0] << 8) / 10;
    //set_soc(packStateOfCharge);
    break;

  case 0x101:
    // packCurrent = (float) (*((int*) msg.data) & (0x3 << 6));
    // packVoltage = (float) (*((int*) msg.data) & (0x3 << 4));
    packCurrent = (msg.data[0] | msg.data[1] << 8) / 10.0; // default unit: 0.1 A
    packVoltage = (msg.data[2] | msg.data[3] << 8) / 10.0; // default unit: 0.1 V
    set_pack_current(packCurrent);
    set_pack_voltage(packVoltage);
    break;

  case 0x102:
    // packAmpHours = (float) (*((int*) msg.data) & (0x3 << 6));
    packAmpHours = (msg.data[0] | msg.data[1] << 8) / 10.0; // default unit: 0.1 Ahr
    set_tstamp_hr(packAmpHours);
    break;

//   case TODO: commented out only because case # not chosen
//     failsafeStatuses = (bool) (*((int*) msg.data) & (0x3 << 6));
    // failsafeStatuses = (msg.data[0] | msg.data[1] << 8);
    // set_voltage_failsafe(failsafeStatuses & 0x01);
    // set_current_failsafe(failsafeStatuses & 0x02);
    // set_relay_failsafe(failsafeStatuses & 0x04);
    // set_charge_interlock_failsafe(failsafeStatuses & 0x10);
    // set_input_power_supply_failsafe(failsafeStatuses & 0x40);
    // DTC1 = (bool) (*((int*) msg.data) & (0x3 << 4));
    // DTC1 = (msg.data[2] | msg.data[3] << 8);
    // set_discharge_limit_enforcement_fault(DTC1 & 0x01);
    // set_charger_safety_relay_fault(DTC1 & 0x02);
    // set_internal_hardware_fault(DTC1 & 0x04);
    // set_internal_heatsink_fault(DTC1 & 0x08);
    // set_internal_software_fault(DTC1 & 0x10);
    // set_highest_cell_voltage_too_high_fault(DTC1 & 0x20);
    // set_lowest_cell_voltage_too_low_fault(DTC1 & 0x40);
    // set_pack_too_hot_fault(DTC1 & 0x80);
//     DTC2 = (bool) (*((int*) msg.data) & (0x3 << 2));
    // DTC2 = (msg.data[4] | msg.data[5] << 8);
// set_internal_communication_fault(DTC1 & 0x0001);
// set_cell_balancing_stuck_off_fault(DTC1 & 0x0002);
// set_weak_cell_fault(DTC1 & 0x0004);
// set_low_cell_voltage_fault(DTC1 & 0x0008);
// set_open_wiring_fault(DTC1 & 0x0010);
// set_current_sensor_fault(DTC1 & 0x0020);
// set_highest_cell_voltage_over_5V_fault(DTC1 & 0x0040);
// set_cell_asic_fault(DTC1 & 0x0080);
// set_weak_pack_fault(DTC1 & 0x0100);
// set_fan_monitor_fault(DTC1 & 0x0200);
// set_thermistor_fault(DTC1 & 0x0400);
// set_external_communication_fault(DTC1 & 0x0800);
// set_redundant_power_supply_fault(DTC1 & 0x1000);
// set_high_voltage_isolation_fault(DTC1 & 0x2000);
// set_input_power_supply_fault(DTC1 & 0x4000);
// set_charge_limit_enforcement_fault(DTC1 & 0x8000);
    // break;

  case 0x103:
    // packHealth = (float) (*((int*) msg.data) & (0x1 << 7));
    packHealth = msg.data[0];
    set_soh(packHealth);
    break;

//   case TODO: commented out only because case # not chosen
//     powerInputVoltage = (float) (*((int*) msg.data) & (0x1 << 7));
    // powerInputVoltage = msg.data[0] / 10.0; // default unit: 0.1v
    // set_bms_input_voltage(powerInputVoltage);
    // break;

  case 0x104:
    // avgTemperature = (float) (*((int*) msg.data) & (0x1 << 7));
    // internalTemperature = (float) (*((int*) msg.data) & (0x1 << 6));
    // fanSpeed = (uint8_t) (*((int*) msg.data) & (0x1 << 5));
    avgTemperature = msg.data[0]; // default unit: 1 C
    internalTemperature = msg.data[1]; // default unit: 1 C
    fanSpeed = msg.data[2]; // default units: 0-6 speed
    set_pack_temp(avgTemperature);
    set_pack_internal_temp(internalTemperature);
    set_fan_speed(fanSpeed);
    break;

  case 0x105:
    // packResistance = (float) (*((int*) msg.data) & (0x3 << 6));
    packResistance = (msg.data[0] | msg.data[1] << 8) / 1000; // default unit: 1 mOhm
    set_pack_resistance(packResistance);
    break;

  case 0x106:
    // adaptiveTotalCapacity = (float) (*((int*) msg.data) & (0x3 << 6));
    adaptiveTotalCapacity = (msg.data[0] | msg.data[1] << 8) / 10.0; // default unit: 0.1 Amp-hours
    set_adaptive_total_capacity(adaptiveTotalCapacity);
    break;

  case 0x107:
    // populatedCells = (float) (*((int*) msg.data) & (0x1 << 7));
    populatedCells = msg.data[0];
    set_populated_cells(populatedCells);
    break;

  default:
    break;
    
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