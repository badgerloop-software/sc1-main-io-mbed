#ifndef __DIGITAL_H__
#define __DIGITAL_H__

#include "mbed.h"
#include "dataFormat.h"

// automatically read brake pins at a set interval
void initDigital(std::chrono::milliseconds readSignalPeriod);

// control brake light
void setBrakeLED(int value);

#endif