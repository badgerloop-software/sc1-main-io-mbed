#ifndef __BMS_H__
#define __BMS_H__

#include "can.h"
#include "uartApp.h"
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
  uint8_t packAmpHours;
  bool failsafeStatuses;
  bool DTC1;
  bool DTC2;
  float packHealth;
  float powerInputVoltage;
  float avgTemperature;
  float internalTemperature;
  uint8_t fanSpeed;
  float packResistance;
  float adaptiveTotalCapacity;
  uint16_t populatedCells;
  int canID;
  float batteryVoltage[31];

public:
  BMS(Can &c) : device(c) {}

  int callback(CANMessage &msg);

  float getPackStateOfCharge();
  float getPackCurrent();
  float getPackVoltage();
  uint8_t getPackAmpHours();
  bool getFailsafeStatuses();
  bool getDTC1();
  bool getDTC2();
  float getPackHealth();
  float getPowerInputVoltage();
  float getAvgTemperature();
  float getInternalTemperature();
  uint8_t getFanSpeed();
  float getPackResistance();
  float getAdaptiveTotalCapacity();
  uint16_t getPopulatedCells();
};

#endif