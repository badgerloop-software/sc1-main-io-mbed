#include "mbed.h"
#include "uartApp.h"
#include "bms.h"
#include "i2cdevice.h"
#include "tca6416.h"

CAN canBus(PD_0, PD_1);
I2C i2cBus(PF_0, PF_1);

int main(void){

    if(runUart()) {
        printf("UART application is not running\n");
        exit(1);
    } 
    

    Can c(&canBus);
    const uint8_t tca_dirs[16] = {1, 1, 1, 1, 1, 1, 1, 1, 
                                    1, 0, 1, 1, 1, 1, 1, 1};
    TCA6416 tca(&i2cBus, 0x21);
    tca.begin(tca_dirs);
    BMS bms(c, &tca, 10ms);

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
