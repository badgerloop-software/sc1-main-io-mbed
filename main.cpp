#include "mbed.h"
#include "uartApp.h"
#include "mcc.h"
#include "mppt.h"
#include "bms.h"

CAN canBus(PD_0, PD_1);

// main() runs in its own thread in the OS
int main()
{
    // if(runUart()) {
    //     printf("UART application is not running\n");
    //     exit(1);
    // } 
    Can c(&canBus);
    
    MCC mcc(c);
    MPPT mppt(c);
    BMS bms(c);

    // int id = 0x200;
    // char data[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    // CANMessage msg = CANMessage(id, data);
    // mppt.callback(msg);
    // mcc.callback(msg);

    // for (;;) {
    //     //printf("\e[1;1H\e[2J");
    //     // printf("%f\n", mppt.getMaxCurrent());
    //     printf("%f\n", mcc.getCurRPM());
    //     printf("%hu\n", mcc.getCurGPIO());
    //     printf("%f\n", mcc.getCurAcc());
    //     printf("%f\n", mcc.getCurBrk());
    //     printf("\n");
    // BMS bms(c);

    for (;;) {
        //printf("\e[1;1H\e[2J");
        printf("BMS Voltage: %f\n", bms.getPackStateOfCharge());
        wait_us(3000000);
    }
    
    printf("Hello, Mbed!\n");
    return 0;
}

