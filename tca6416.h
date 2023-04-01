#ifndef TCA_H
#define TCA_H

#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "mbed.h"
#include "i2cutil.h"

#define TCA_CFG0_REG 0x0006
#define TCA_CFG1_REG 0x0007
#define TCA_OUT0_REG 0x02
#define TCA_OUT1_REG 0x03
#define TCA_IN0_REG 0x0
#define TCA_IN1_REG 0x1

#define TCA_NUM_PINS_PER_BANK 8

class TCA6416 {
 private:
  I2C* i2cBus;
  int address;


 public:

  TCA6416(I2C*  bus, int addr);
  int write(char buf[], int length);
  int read(uint8_t commandByte);
  uint8_t read_from_reg(uint8_t reg); // Helper
  void write_data(uint8_t reg, uint8_t val);
  int clear_settings();
  int begin(const uint8_t directions[]);
  int set_dir(bool bank, int pin, uint8_t dir);
  int get_dir(bool bank, int pin);
  int get_state(bool bank, int pin);
  int set_state(bool bank, int pin, uint8_t val);
  
};

#endif