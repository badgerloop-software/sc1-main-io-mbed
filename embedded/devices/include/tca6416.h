#ifndef TCA_H
#define TCA_H

#include <stdio.h>
#include "stdint.h"
#include "mbed.h"
#include "i2cdevice.h"

#define TCA_CFG0_REG 0x06
#define TCA_CFG1_REG 0x07
#define TCA_OUT0_REG 0x02
#define TCA_OUT1_REG 0x03
#define TCA_IN0_REG 0x0
#define TCA_IN1_REG 0x1

#define TCA_NUM_PINS_PER_BANK 8

class TCA6416 : public I2CDevice {
 private:
  uint8_t read_from_reg(uint8_t reg);
  void write_data(uint8_t reg, uint8_t val);
  
 public:
  /// Address is either 0x20 or 0x21
  TCA6416(I2C* bus, uint8_t addr);
  int clear_settings();
  /// First 8 for pins 0-7 bank 0, second 8 for bank 1
  //  1 input, 0 output
  int begin(const uint8_t directions[16]);
  int set_dir(bool bank, int pin, uint8_t dir);
  int get_dir(bool bank, int pin);
  int get_state(bool bank, int pin);
  int set_state(bool bank, int pin, uint8_t val);
};

#endif