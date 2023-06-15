#include "mbed.h"
#include "uartApp.h"
#include "bms.h"
#include "i2cdevice.h"
#include "tca6416.h"

CAN canBus(PD_0, PD_1);
I2C i2cBus(PB_11, PB_10); // (sda, scl)

int main(void){
    Can c(&canBus);
	// TODO Check directions and set pins to read to 1 and pins to write to 0
    const uint8_t tca_dirs[16] = {1, 1, 1, 1, 1, 1, 1, 1, 
                                    1, 0, 1, 1, 1, 1, 1, 1};
    TCA6416 tca(&i2cBus, 0x20);
    tca.begin(tca_dirs);
	Mutex tcaMutex;

    BMS bms(c, &tca, 10ms);
    
    if(!runUart(&tca, &tcaMutex)) {
        printf("the UART application is running\n");
    } else {
        printf("NOT RUNNING\n");
        exit(1);
    }
    
    for (;;) {
        printf("\e[1;1H\e[2J");
        printf("Charge: %f\n", bms.getPackStateOfCharge());
        printf("Voltage: %f\n", bms.getPackVoltage());
        printf("Current: %f\n", bms.getPackCurrent());
        printf("Avg Temp: %f\n", bms.getAvgTemperature());
        printf("Internal Temp:%f\n", bms.getInternalTemperature());
        printf("Fan Speed: %d\n", bms.getFanSpeed());
        wait_us(3000000);
        // modify the byte array and put printouts here

        // this has to be set to 1 for the UART app to not get stuck at the fault screen. 
        // it will probably change in the future once software updates the
        // checkRestartEnable() method in DataUnpacker.cpp 
        set_door(1); 
    }
    
    printf("Hello, Mbed!\n");
    return 0;
}


