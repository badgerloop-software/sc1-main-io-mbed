#ifndef __BMS_H__
#define __BMS_H__
#include "can.h"
#include "stdio.h"
#include "mbed.h"
#include <cstdint>

/**
* BMS CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
class BMS : Can::device {
private:
  // if not in format.json, assumed to be float type
  float packStateOfCharge;
  float packCurrent;
  float packVoltage;
  float maxPackVoltage;
  float packAmpHours;
  bool failsafeStatuses;
  float DTC1;
  float DTC2;
  float packHealth;
  float powerInputVoltage;
  float avgTemperature;
  float internalTemperature;
  uint8_t fanSpeed;
  float packResistance;
  float avgCellInternalResistance;
  float adaptiveTotalCapacity;
  float populatedCells;

public:
  BMS(Can &c) : device(c) {}

  int callback(CANMessage &msg);

  float getPackStateOfCharge();
  float getPackCurrent();
  float getPackVoltage();
  float getMaxPackVoltage();
  float getPackAmpHours();
  bool getFailsafeStatuses();
  float getDTC1();
  float getDTC2();
  float getPackHealth();
  float getPowerInputVoltage();
  float getAvgTemperature();
  float getInternalTemperature();
  uint8_t getFanSpeed();
  float getPackResistance();
  float getAvgCellInternalResistance();
  float getAdaptiveTotalCapacity();
  float getPopulatedCells();
};

#endif