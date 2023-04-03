#include "lsm6dsl.h"
#include "i2cWrapper.h"
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
int lsm6dsl :: begin() {
    char data[1] = {1};
    if(writeI2CWrapper(i2cBus, address, RESET, data, 1)) {
        return -1;
    }
    char buf[1];
    if(readI2CWrapper(i2cBus, address, WHO_AM_I, buf, 1)) {
        return -1;
    } else if(buf[0] != DEVID) {
        return -1;
    }
    setRangeG(0);
    setRangeXL(0);
    setPowerModeG(1);
    setPowerModeXL(1);
    return 0;
}
double lsm6dsl :: getXLX() {
    uint16_t value;
    char valueHigh[1];
    if(readI2CWrapper(i2cBus, address, OUTX_H_XL, valueHigh, 1)) {
        return -1;
    }
    char valueLow[1];
    if(readI2CWrapper(i2cBus, address, OUTX_H_XL, valueHigh, 1)) {
        return -1;
    }
    value = valueHigh[0] << 8;
    value |= valueLow[0];
    return 0;
}
double lsm6dsl :: getXLY() {
    return 0;
}
double lsm6dsl :: getXLZ() {
    return 0;
}
double lsm6dsl :: getGX() {
    return 0;
}
double lsm6dsl :: getGY() {
    return 0;
}
double lsm6dsl :: getGZ() {
    return 0;
}

int lsm6dsl :: setPowerModeXL(uint8_t select) {
    return 0;
}
int lsm6dsl :: setPowerModeG(uint8_t select) {
    return 0;
}
int lsm6dsl :: setRangeXL(uint8_t select) {
    return 0;
}
int lsm6dsl :: setRangeG(uint8_t select) {
    return 0;
}