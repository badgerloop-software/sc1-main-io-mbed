#include "mbed.h"
#include "uartApp.h"
#include "mcc.h"
#include "mppt.h"
#include "bms.h"

CAN canBus(PD_0, PD_1);

// main() runs in its own thread in the OS
int main()
{
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

