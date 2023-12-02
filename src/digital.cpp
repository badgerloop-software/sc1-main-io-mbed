#include "digital.h"

// Ticker to setup a recurring interrupt to repeatedly call a function at a specified rate
Ticker readDigitalDelay;

// assign digital input to correct brake pins
DigitalIn brake_1_input(PC_8);
DigitalIn brake_2_input(PC_9);

// other digital input pins
DigitalIn brake_light(PG_1);
DigitalIn brake_status1(PF_0);
DigitalIn brake_status2(PF_1);

// NOTE: potentially don't have these signals
#ifndef LIGHTS_DISABLED
DigitalIn hazard_signal(PE_2);
DigitalIn headlights(PD_11);
DigitalIn left_turn_signal(PD_13);
DigitalIn right_turn_signal(PD_12);
#endif

// storing every digital data inside a struct to reduce the memory
volatile struct Digital_Data digital_data = {};

// read input from the digital pins
void readDigital() {
    digital_data.brake1 = brake_1_input.read();
    digital_data.brake2 = brake_2_input.read();
    
    digital_data.BRK_LED_EN = brake_light.read();
    digital_data.BRK_STATUS = brake_status1.read();
    digital_data.BRK_STATUS2 = brake_status2.read();

    // NOTE: potentially don't have these signals
    #ifndef LIGHTS_DISABLED
    digital_data.HZRD_TELEM = hazard_signal.read();
    digital_data.HEADLIGHT_TELEM = headlights.read();
    digital_data.L_BLINK_TELEM = left_turn_signal.read();
    digital_data.R_BLINK_TELEM = right_turn_signal.read();
    #endif
}


// automatically read brake pins at a set interval
void initBrake(std::chrono::milliseconds readSignalPeriod) {
    readDigitalDelay.attach(readDigital, readSignalPeriod);
}