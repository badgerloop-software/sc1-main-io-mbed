#ifndef __ANALOG_H__
#define __ANALOG_H__

#include "telemetry.h"
#include "mutexless_analog.h"
#include "thermistor.h"
#include "INA281.h"

// read all the analog inputs
void readAnalog();

// repeatedly call the function with the given parameter
void initAnalog(std::chrono::microseconds readSignalPeriod);

#endif