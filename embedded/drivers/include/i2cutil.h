#ifndef I2CUTIL_H
#define I2CUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include "mbed.h"
#include "stdint.h"

void i2cdetect(I2C *bus);
int readI2CWrapper(I2C *i2cBus, int addr, uint8_t reg, char buffer[], int numBytes);
int writeI2CWrapper(I2C *i2cBus, int addr, uint8_t reg, char data[], int numBytes);

#endif