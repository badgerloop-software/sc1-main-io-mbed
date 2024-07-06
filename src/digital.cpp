#include "digital.h"

DigitalIn hazard_signal(PE_3);
DigitalIn left_turn_signal(PD_5);
DigitalIn right_turn_signal(PD_7);


// read input from the digital pins
void readDigital() {
  set_hazards(hazard_signal.read());
  set_l_turn_led_en(left_turn_signal.read());
  set_r_turn_led_en(right_turn_signal.read());
}

