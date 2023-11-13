#include "digital.h"

// Ticker to setup a recurring interrupt to repeatedly call a function at a specified rate
Ticker readDigitalDelay;

// assign digital input to correct brake pins
DigitalIn brake_1_input(BRAKE_PIN);
DigitalIn brake_2_input(BRAKE_2_PIN);

volatile struct brakeInputStore brakeInputs;

// read input from the brake pins
void readPins() {
    brakeInputs.brake1 = brake_1_input.read();
    brakeInputs.brake2 = brake_2_input.read();
}

// automatically read brake pins at a set interval
void initBrake(std::chrono::milliseconds readSignalPeriod) {
    readDigitalDelay.attach(readPins, readSignalPeriod);
}