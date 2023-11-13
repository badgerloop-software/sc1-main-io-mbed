#ifndef __DIGITAL_H__
#define __DIGITAL_H__

#include "mbed.h"
#include <chrono>

// define brake pins
#define BRAKE_PIN PC_8
#define BRAKE_2_PIN PC_9

// struct to store data from the brake pins
struct brakeInputStore {
    bool brake1 : 1;
    bool brake2 : 1;
};

extern volatile struct brakeInputStore brakeInputs;

// read input from the brake pins
void readPins();

// automatically read brake pins at a set interval
void initBrake(std::chrono::milliseconds readSignalPeriod);

#endif