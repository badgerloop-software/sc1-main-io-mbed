#include "mbed.h"
#include "uartApp.h"
#include "mcc.h"

CAN canBus(PD_0, PD_1);

// main() runs in its own thread in the OS
int main()
{
    // if(runUart()) {
    //     printf("UART application is not running\n");
    //     exit(1);
    // } 
    canBus.frequency(20000);
    Can c(&canBus);
    
    MCC d(c);

    for (;;) {
        //printf("\e[1;1H\e[2J");
        printf("%f\n", d.getCurAcc());
        printf("%f\n", d.getCurBrk());
        printf("%i\n", d.getCurGPIO());
        printf("%f\n", d.getCurRPM());
        printf("\n");
        wait_us(3000000);
    }
    
    printf("Hello, Mbed!\n");
    return 0;
}

