#ifndef __DIGITAL_H__
#define __DIGITAL_H__

#include "mbed.h"
#include "telemetry.h"
#include <chrono>

// read input from the digital pins
void readDigital();

// automatically read brake pins at a set interval
void initBrake(std::chrono::milliseconds readSignalPeriod);

#endif