#ifndef __TELEMETRY_H__
#define __TELEMETRY_H__

#include "mbed.h"

// ************************************************
// UNCOMMENT BELOW TO DISABLE LIGHTS
// ************************************************
// #define LIGHTS_DISABLED

// Bit field to store digital IO
struct Digital_Data {
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

extern volatile Digital_Data digital_data;

#endif