#ifndef __DIGITAL_H__
#define __DIGITAL_H__

#include "mbed.h"
#include "dataFormat.h"

// Uncomment below to disable lights
// #define LIGHTS_DISABLED

// Reads digital signals
void readDigital();

// automatically read brake pins at a set interval
void initDigital(std::chrono::milliseconds readSignalPeriod);

// control brake light
void setBrakeLED(int value);

#endif