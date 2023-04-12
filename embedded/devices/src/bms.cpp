#include "bms.h"

/**
* BMS CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
int BMS::callback(CANMessage &msg) {
  switch (msg.id) {
  case 0x100:
    packStateOfCharge = (float) (*((int*) msg.data) & (0x1 << 7));
    set_soc(packStateOfCharge);
  case 0x101:
    packCurrent = (float) (*((int*) msg.data) & (0x3 << 6));
    packVoltage = (float) (*((int*) msg.data) & (0x3 << 4));
    set_pack_current(packCurrent);
    set_pack_voltage(packVoltage);

  case 0x102:
    packAmpHours = (float) (*((int*) msg.data) & (0x3 << 6));
    // set_tstamp_hr(packAmpHours);
//   case TODO:
//     failsafeStatuses = (bool) (*((int*) msg.data) & (0x3 << 6));
//     DTC1 = (float) (*((int*) msg.data) & (0x3 << 4));
//     DTC2 = (float) (*((int*) msg.data) & (0x3 << 2));
  case 0x103:
    packHealth = (float) (*((int*) msg.data) & (0x1 << 7));
    set_soh(packHealth);
//   case TODO:
//     powerInputVoltage = (float) (*((int*) msg.data) & (0x1 << 7));
  case 0x104:
    avgTemperature = (float) (*((int*) msg.data) & (0x1 << 7));
    internalTemperature = (float) (*((int*) msg.data) & (0x1 << 6));
    fanSpeed = (uint8_t) (*((int*) msg.data) & (0x1 << 5));
    set_pack_temp(avgTemperature);
    set_pack_internal_temp(internalTemperature);
    set_fan_speed(fanSpeed);
  case 0x105:
    packResistance = (float) (*((int*) msg.data) & (0x3 << 6));
    avgCellInternalResistance = (float) (*((int*) msg.data) & (0x3 << 4));
    set_pack_resistance(packResistance);
    // need avgCellInternalResistance

  case 0x106:
    adaptiveTotalCapacity = (float) (*((int*) msg.data) & (0x3 << 6));
    set_adaptive_total_capacity(adaptiveTotalCapacity);
  case 0x107:
    populatedCells = (float) (*((int*) msg.data) & (0x1 << 7));
    set_populated_cells(populatedCells);
  }

  return 0;
}

float BMS::getPackStateOfCharge() { return packStateOfCharge; }
float BMS::getPackCurrent() { return packCurrent; }
float BMS::getPackVoltage() { return packVoltage; }
float BMS::getPackAmpHours() { return packAmpHours; }
bool BMS::getFailsafeStatuses() { return failsafeStatuses; }
float BMS::getDTC1() { return DTC1; }
float BMS::getDTC2() { return DTC2; }
float BMS::getPackHealth() { return packHealth; }
float BMS::getPowerInputVoltage() { return powerInputVoltage; }
float BMS::getAvgTemperature() { return avgTemperature; }
float BMS::getInternalTemperature() { return internalTemperature; }
uint8_t BMS::getFanSpeed() { return fanSpeed; }
float BMS::getPackResistance() { return packResistance; }
float BMS::getAvgCellInternalResistance() { return avgCellInternalResistance; }
float BMS::getAdaptiveTotalCapacity() { return adaptiveTotalCapacity; }
float BMS::getPopulatedCells() { return populatedCells; }