#include "lsm6dsl.h"
#include "i2cWrapper.h"
#include <cmath>
#include <cstdint>
#include <stdint.h>
// pg 60 for control settings
// pg 72 for output registers
// pg 81 for timestamp data 

lsm6dsl :: lsm6dsl(I2C*bus, int addr) {
    i2cBus = bus;
    address = addr << 1;
}

// verifies that device is correct, resets device, sets range and power settings
// returns 0 on success, -1 on failure
int lsm6dsl :: begin() {
    char data[1] = {1}; 
    if(writeI2CWrapper(i2cBus, address, SOFTWARE_RESET, data, 1)) {
        return -1;
    }
    char buf[1];
    if(readI2CWrapper(i2cBus, address, WHO_AM_I, buf, 1)) {
        return -1;
    }
    // checks to make sure device ID is correct
    if(buf[0] != DEVID) {
        return -1;
    }
    rangeXL = FULL_SCALE_XL_DEFAULT;
    rangeG = FULL_SCALE_G_DEFAULT;
    return 0;
}

// gets Linear Acceleration in X Direction
// returns acceleration in terms of G's
double lsm6dsl :: getXLX() {
    uint16_t value;
    char valueHigh[1];
    if(readI2CWrapper(i2cBus, address, OUTX_H_XL, valueHigh, 1)) {
        return -1;
    }
    char valueLow[1];
    if(readI2CWrapper(i2cBus, address, OUTX_L_XL, valueLow, 1)) {
        return -1;
    }
    // reads high and low registers and combines them
    value = valueHigh[0] << 8 | valueLow[0];
    return twos_complement(value, rangeXL);
}

// gets Linear Acceleration in Y Direction
// returns acceleration in terms of G's
double lsm6dsl :: getXLY() {
    uint16_t value;
    char valueHigh[1];
    if(readI2CWrapper(i2cBus, address, OUTY_H_XL, valueHigh, 1)) {
        return -1;
    }
    char valueLow[1];
    if(readI2CWrapper(i2cBus, address, OUTY_L_XL, valueLow, 1)) {
        return -1;
    }
    value = valueHigh[0] << 8 | valueLow[0];
    return twos_complement(value, rangeXL);
}

// gets Linear Acceleration in Z Direction
// returns acceleration in terms of G's
double lsm6dsl :: getXLZ() {
    uint16_t value;
    char valueHigh[1];
    if(readI2CWrapper(i2cBus, address, OUTZ_H_XL, valueHigh, 1)) {
        return -1;
    }
    char valueLow[1];
    if(readI2CWrapper(i2cBus, address, OUTZ_L_XL, valueLow, 1)) {
        return -1;
    }
    value = valueHigh[0] << 8 | valueLow[0];
    return twos_complement(value, rangeXL);
}

// gets Angluar Velocity in X Direction
// returns acceleration in terms of dps
double lsm6dsl :: getGX() {
    uint16_t value;
    char valueHigh[1];
    if(readI2CWrapper(i2cBus, address, OUTX_H_G, valueHigh, 1)) {
        return -1;
    }
    char valueLow[1];
    if(readI2CWrapper(i2cBus, address, OUTX_L_G, valueLow, 1)) {
        return -1;
    }
    value = valueHigh[0] << 8 | valueLow[0];
    return twos_complement(value, rangeG);
    return 0;
}

// gets Angluar Velocity in Y Direction
// returns acceleration in terms of dps
double lsm6dsl :: getGY() {
    uint16_t value;
    char valueHigh[1];
    if(readI2CWrapper(i2cBus, address, OUTY_H_G, valueHigh, 1)) {
        return -1;
    }
    char valueLow[1];
    if(readI2CWrapper(i2cBus, address, OUTY_L_G, valueLow, 1)) {
        return -1;
    }
    value = valueHigh[0] << 8 | valueLow[0];
    return twos_complement(value, rangeG);
    return 0;
}

// gets Angluar Velocity in Z Direction
// returns acceleration in terms of dps
double lsm6dsl :: getGZ() {
    uint16_t value;
    char valueHigh[1];
    if(readI2CWrapper(i2cBus, address, OUTZ_H_G, valueHigh, 1)) {
        return -1;
    }
    char valueLow[1];
    if(readI2CWrapper(i2cBus, address, OUTZ_L_G, valueLow, 1)) {
        return -1;
    }
    value = valueHigh[0] << 8 | valueLow[0];
    return twos_complement(value, rangeG);
    return 0;
}

// sets power mode of Accelerometer
int lsm6dsl :: setPowerModeXL(uint8_t select) {
    char currentStatus [1];
    char data[1];
    if(readI2CWrapper(i2cBus, address, CTRL1_XL, currentStatus, 1)) {
        return -1;
    }
    data[0] = (currentStatus[0] & 0x0F) | (select << 4);
    if(writeI2CWrapper(i2cBus, address, CTRL1_XL, data, 1)) {
        return -1;
    }
    return 0;
}

int lsm6dsl :: setPowerModeG(uint8_t select) {
    char currentStatus [1];
    char data[1];
    if(readI2CWrapper(i2cBus, address, CTRL2_G, currentStatus, 1)) {
        return -1;
    }
    data[0] = (currentStatus[0] & 0x0F) | (select << 4);
    if(writeI2CWrapper(i2cBus, address, CTRL2_G, data, 1)) {
        return -1;
    }
    return 0;
}

int lsm6dsl :: setRangeXL(uint8_t select) {
    char currentStatus [1];
    char data[1];
    if(readI2CWrapper(i2cBus, address, CTRL1_XL, currentStatus, 1)) {
        return -1;
    }
    currentStatus[0] = currentStatus[0] & 0xF3;
    switch (select) {
        case 2:
        data[0] = currentStatus[0] | FULL_SCALE_XL_2G;
        case 4:
        data[0] = currentStatus[0] | FULL_SCALE_XL_4G;
        case 8:
        data[0] = currentStatus[0] | FULL_SCALE_XL_8G;
        case 16:
        data[0] = currentStatus[0] | FULL_SCALE_XL_16G;
    };
    if(writeI2CWrapper(i2cBus, address, CTRL1_XL, data, 1)) {
        return -1;
    }
    return 0;
}
int lsm6dsl :: setRangeG(uint8_t select) {
    char currentStatus [1];
    char data[1];
    if(readI2CWrapper(i2cBus, address, CTRL2_G, currentStatus, 1)) {
        return -1;
    }
    
    uint8_t fullScale125Value = currentStatus[0] & 0xF1;
    currentStatus[0] = currentStatus[0] & 0xF3;
    switch (select) {
        case 125:
        data[0] = fullScale125Value;
        case 250:
        data[0] = currentStatus[0] | FULL_SCALE_G_250;
        case 500:
        data[0] = currentStatus[0] | FULL_SCALE_G_500;
        case 1000:
        data[0] = currentStatus[0] | FULL_SCALE_G_1000;
        case 2000:
        data[0] = currentStatus[0] | FULL_SCALE_G_2000;
    };
    if(writeI2CWrapper(i2cBus, address, CTRL2_G, data, 1)) {
        return -1;
    }
    return 0;
}

double twos_complement(int16_t two_compliment_val, int full_scale_selection) {
  int16_t sign_mask = 0x8000;
  // if positive
  if ((two_compliment_val & sign_mask) == 0) {
      // returns adjusted value based on two's complement value 
      return ((full_scale_selection) / (pow(2, 15) - 1)) * two_compliment_val;
    //  if negative
  } else {
    // invert all bits, add one, and make negative. Adjusts value based on full-scale selection
    return ((full_scale_selection) / (pow(2, 15))) * -(~two_compliment_val + 1);
  }
}

double lsm6dsl :: getXLMagnitude() {
    double x = getXLX();
    double y = getXLY();
    double z = getXLZ();
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double lsm6dsl :: getGMagnitude() {
    double x = getGX();
    double y = getGY();
    double z = getGZ();
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

