#ifndef __TELEMETRY_H__
#define __TELEMETRY_H__

#include "mbed.h"

// uncomment below to disable lights
// #define LIGHTS_DISABLED

// Bit field to store digital IO
struct Digital_Data {
    bool BRK_LED_EN : 1;
    bool BRK_STATUS : 1;
    bool BRK_STATUS2 : 1;

    // NOTE: potentially don't have these signals
    #ifndef LIGHTS_DISABLED
    bool HZRD_TELEM : 1;
    bool HEADLIGHT_TELEM : 1;
    bool L_BLINK_TELEM : 1;
    bool R_BLINK_TELEM : 1;
    #endif
};

// thermistor temperatures. Found in analog.cpp
extern volatile float air_temperature;
extern volatile float brake_temperature;
extern volatile float dcdc_temperature;
extern volatile float main_io_temperature;
extern volatile float motor_controller_temperature;
extern volatile float motor_temperature;
extern volatile float road_temperature;

// bus voltages and currents Found in analog.cpp
extern volatile float bus_12v;
extern volatile float bus_24v;
extern volatile float bus_5v;
extern volatile float input_current_12v;
extern volatile float output_current_5v;
extern volatile float output_current_24v;

#endif