#ifndef __BMS_H__
#define __BMS_H__

#include "can.h"
#include "uartApp.h"
#include "stdio.h"
#include "mbed.h"
#include <cstdint>
#include "tca6416.h"
#include <chrono>

/**
* BMS CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
class BMS : Can::device {
private:
  // CAN signals, if not in format.json, assumed to be float type
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

  // GPIO Signals
  TCA6416* tca;
  LowPowerTicker readGPIO;
  bool mpi_1;
  bool mpi_2;
  bool mpo_2;
  bool chrg_en;
  bool dschrg_en;

public:
  BMS(Can &c, TCA6416* tca, std::chrono::milliseconds gpio_update_interval);

  int callback(CANMessage &msg);
  void updateGPIO();

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