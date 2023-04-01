#include "mbed.h"
#include "uartApp.h"
#include "mcc.h"
#include "mppt.h"
#include "bms.h"

CAN canBus(PD_0, PD_1);

#include "i2cutil.h"
#include "tca6416.h"

int main(void){
    puts("Program start");
    puts("Starting tests for TCA driver");
    puts("Creating I2C bus...");
    I2C*bus = new I2C(PF_0, PF_1);
    puts("Done");
    i2cdetect(bus);
    puts("Listed I2C Devices. Should appear as 40 and/or 41. Will test 40 for this test");
    puts("Real address 21, << 1 -> 42");
    puts("Initializing TCA...");
    TCA6416* tca = new TCA6416(bus, 0x21);
    puts("TCA initialized. Proceeding to begin");
    char testbuffer[1];
    readI2CWrapper(bus, 0x42, 0x06, testbuffer, 1);
    puts("done");
    printf("%d\n",testbuffer[0]);
    puts("The line above should be 255");
    puts("Completed raw read testing. Moving on to normal tests...");
    puts("Setting output and then reading it back");
    const uint8_t directions[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    tca->begin(directions);
    printf("%d %d\n", tca->get_dir(0, 0), tca->get_dir(0, 1));

    if(runUart()) {
        printf("UART application is not running\n");
        exit(1);
    } 

    Can c(&canBus);
    BMS bms(c);
    MCC mcc(c);
    MPPT mppt(c);


    for (;;) {
        printf("\e[1;1H\e[2J");
        printf("Charge: %f\n", bms.getPackStateOfCharge());
        printf("Voltage: %f\n", bms.getPackVoltage());
        printf("Current: %f\n", bms.getPackCurrent());
        printf("Avg Temp: %f\n", bms.getAvgTemperature());
        printf("Internal Temp:%f\n", bms.getInternalTemperature());
        printf("Fan Speed: %d\n", bms.getFanSpeed());
        wait_us(3000000);
    }
    
    printf("Hello, Mbed!\n");
    return 0;
}
