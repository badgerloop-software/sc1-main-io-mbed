#ifndef __lsm6dsl__h__
#define __lsm6dsl__h__
#include "mbed.h"
#include "stdint.h"


#define RESET 0x01
#define DEVID 0x6A

#define SOFTWARE_RESET 0x12 // need to change this
#define WHO_AM_I 0x0F

#define CTRL1_XL 0x10
#define CTRL2_G 0x11  
#define OUTX_L_G 0x22
#define OUTX_H_G 0x23
#define OUTY_L_G 0x24
#define OUTY_H_G 0x25
#define OUTZ_L_G 0x26
#define OUTZ_H_G 0x27
#define OUTX_L_XL 0x28
#define OUTX_H_XL 0x29
#define OUTY_L_XL 0x2A
#define OUTY_H_XL 0x2B
#define OUTZ_L_XL 0x2C
#define OUTZ_H_XL 0x2D

#define POWER_MODE_G 0x01
#define POWER_MODE_XL 0x01
#define FULL_SCALE_XL_DEFAULT 2
#define FULL_SCALE_XL_2G 0x00
#define FULL_SCALE_XL_4G 0x08
#define FULL_SCALE_XL_8G 0x0C
#define FULL_SCALE_XL_16G 0x04
#define FULL_SCALE_G_DEFAULT 250
#define FULL_SCALE_G_250 0x00
#define FULL_SCALE_G_500 0x04
#define FULL_SCALE_G_1000 0x08
#define FULL_SCALE_G_2000 0x0C

// Valid Accelerometer Full-Scale Ranges:
// 2, 4, 8, 16 (Gs)

// Valid Gyroscope Full-Scale Ranges:
// 125, 250, 500, 1000, 2000 (dps)

// Valid Accelerometer Power Modes:
// Refer to page 60 in LSM6DSL Datasheet (CTRL1_XL), input desired ODR setting from XL_HM_MODE
// Ex. If wanting to choose 1.6Hz when XL_HM_MODE = 1, input 11 into setPowerModeXL()

// Valid Gyroscope Power Modes:
// Refer to page 61 in LSM6DSL Datasheet (CTRL2_G) 

class lsm6dsl {
 private:
 I2C* i2cBus;
 int address;
 uint8_t rangeXL;
 uint8_t rangeG;
 int16_t twos_complement (int16_t twos_complement_val, int full_scale_selection);

 public:
  lsm6dsl(I2C* bus, int addr);
  int begin();
  double getXLX();
  double getXLY();
  double getXLZ();
  double getGX();
  double getGY();
  double getGZ();
  int setPowerModeXL(uint8_t select);
  int setPowerModeG(uint8_t select);
  int setRangeXL(uint8_t select);
  int setRangeG(uint8_t select);
  double getXLMagnitude();
  double getGMagnitude();
  
};

#endif