#include "mbed.h"
#include "lsm6dsl.h"
#include <stdio.h>
#include <iostream>

// main() runs in its own thread in the OS
int main()
{
    I2C *i2cBus; 
    lsm6dsl dev(i2cBus, 0x6A);
    if(dev.begin() != 0) {
        return -1;
    } // instantiate device

    while(true) {

        std::cout << "Read Gyro X " << dev.getGX() << " degrees/s\n";
        std::cout << "Read Gyro Y " << dev.getGY() << " degrees/s\n";
        std::cout << "Read Gyro Z " << dev.getGZ() << " degrees/s\n\n";

        std::cout << "Read Accelerometer X " << dev.getXLX() << " m/s/s\n";
        std::cout << "Read Accelerometer Y " << dev.getXLY() << " m/s/s\n";
        std::cout << "Read Accelerometer Z " << dev.getXLZ() << " m/s/s\n";
    }
}

