#include "digital.h"

// Ticker to setup a recurring interrupt to repeatedly call a function at a
// specified rate
Ticker readDigitalDelay;

DigitalIn hazard_signal(PE_3);
DigitalIn left_turn_signal(PD_5);
DigitalIn right_turn_signal(PD_7);


// read input from the digital pins
void readDigital() {
  set_hazards(hazard_signal.read());
  set_l_turn_led_en(left_turn_signal.read());
  set_r_turn_led_en(right_turn_signal.read());
}

// automatically read brake pins at a set interval
void initDigital(std::chrono::milliseconds readSignalPeriod) {
  readDigitalDelay.attach(readDigital, readSignalPeriod);
}
