#include "digital.h"
#include "dataFormat.h"

// Ticker to setup a recurring interrupt to repeatedly call a function at a
// specified rate
Ticker readDigitalDelay;

// Digital input pins
DigitalIn brake_status1(PF_0);
DigitalIn brake_status2(PF_1);

// Digital output pins
DigitalOut brake_led(PG_1);

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
  set_park_brake(brake_status1.read());

// NOTE: potentially don't have these signals
#ifndef LIGHTS_DISABLED
  set_hazards(hazard_signal.read());
  set_headlights_led_en(headlights.read());
  set_l_turn_led_en(left_turn_signal.read());
  set_r_turn_led_en(right_turn_signal.read());
#endif
}

// automatically read brake pins at a set interval
void initDigital(std::chrono::milliseconds readSignalPeriod) {
  readDigitalDelay.attach(readDigital, readSignalPeriod);
}

// control brake light
void setBrakeLED(int value) { brake_led.write(value); }