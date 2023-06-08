#include "bms.h"
#include "i2cdevice.h"
#include "ina219.h"
#include "mbed.h"
#include "rtos.h"
#include "tca6416.h"
#include "uartApp.h"


//CAN canBus(PD_0, PD_1);
I2C i2cBus(PF_0, PF_1); // (sda, scl)
//DigitalOut pin(PA_7, 1); // this is for the small nucleo so that CAN works.

int main(void){
    printf("hey\n");
    //Can c(&canBus);
	// TODO Check directions and set pins to read to 1 and pins to write to 0
    const uint8_t tca_dirs[16] = {0, 1, 1, 1, 1, 1, 1, 1, 
                                    1, 1, 1, 1, 1, 1, 1, 1};
    TCA6416 tca(&i2cBus, 0x20);
    tca.i2cdetect();
    tca.begin(tca_dirs);
	//Mutex tcaMutex;

    // the following are the 3 INAs on MainIO. Only leave one uncommented when running
    INA219* ina = new INA219(&i2cBus, 0x40, 0.005, 2.0);
    //INA219* ina = new INA219(&i2cBus, 0x44, 0.005, 2.0); 
    //INA219* ina = new INA219(&i2cBus, 0x41, 0.005, 1.0);
    ina->begin();

    //BMS bms(c, &tca, 10ms);
    
    if(!runUart(&tca)) {
        printf("the UART application is running\n");
    } else {
        printf("NOT RUNNING\n");
        exit(1);
    }
    int toggle = 0;
    for (;;) {
        //printf("\e[1;1H\e[2J");
        lock_tca_mutex();
        printf("MCU_Stat_fdbk: %d\n", tca.get_state(0, 1));
        //printf("mcu_hv_en: %d\n", get_mcu_hv_en());
        // printf("IMD_fdbk: %d\n", tca.get_state(0, 2));
        // printf("Lim_fdbk: %d\n", tca.get_state(0, 3));
        // printf("Inertia_fdbk: %d\n", tca.get_state(1, 7));
        // printf("Ext_Estop_fdbk: %d\n", tca.get_state(1, 5));
        // printf("Driver_Estop_fdbk: %d\n", tca.get_state(1, 4));
        if (toggle == 0) {
            toggle = 1;
        } else {
            toggle = 0;
        }
        //tca.set_state(0, 0, toggle);
        unlock_tca_mutex();
        // printf("Charge: %f\n", bms.getPackStateOfCharge());
        // printf("Voltage: %f\n", bms.getPackVoltage());
        // printf("Current: %f\n", bms.getPackCurrent());
        // printf("Avg Temp: %f\n", bms.getAvgTemperature());
        // printf("Internal Temp:%f\n", bms.getInternalTemperature());
        // printf("Fan Speed: %d\n", bms.getFanSpeed());
        wait_us(9000000);
        // modify the byte array and put printouts here

        // this has to be set to 1 for the UART app to not get stuck at the fault screen. 
        // it will probably change in the future once software updates the
        // checkRestartEnable() method in DataUnpacker.cpp 
        set_door(toggle); 
    }
    
    printf("Hello, Mbed!\n");
    return 0;
}

