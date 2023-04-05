#ifndef __lsm6dsl__h__
#define __lsm6dsl__h__
#include "mbed.h"
#include "stdint.h"

//#define g_full_scale 0x0
// define xl_full_scale 0x0

#define RESET 0x01
#define DEVID 0x6A

#define SOFTWARE_RESET 0x12 // need to change this
#define WHO_AM_I 0x0F

#define CTRL1_XL 0x10  // 4 and 5 are two bits for XL full scale selection
#define CTRL2_G 0x11   // 4 and 5 are two bits for G full scale selection
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

class lsm6dsl {
 private:
 I2C* i2cBus;
 int address;
 uint8_t rangeXL;
 uint8_t rangeG;

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
  int16_t twos_complement (int16_t twos_complement_val, int full_scale_selection);
};

#endif