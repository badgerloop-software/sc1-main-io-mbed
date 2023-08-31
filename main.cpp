#include "bms.h"
#include "i2cdevice.h"
#include "ina219.h"
#include "mbed.h"
#include "rtos.h"
#include "tca6416.h"
#include "uartApp.h"

/*CAN canBus(PD_0, PD_1, 500000);
I2C i2cBus(PF_0, PF_1); // (sda, scl)
DigitalOut pin(PA_7, 1); // this is for the small nucleo so that CAN works.
DigitalOut GPIO1_RST(PG_0, 0);
DigitalOut GPIO2_RST(PG_1, 0);
Can c(&canBus);

// bms gpio signals
bool mpi_1;
bool mpi_2;
bool mpo_2;

int main(void){
    printf("hey\n");
    // TODO Check directions and set pins to read to 1 and pins to write to 0
    const uint8_t tca_dirs[16] = {0, 1, 1, 1, 1, 1, 1, 1, 
                                    1, 1, 1, 0, 1, 1, 1, 1};
    TCA6416 tca(&i2cBus, 0x20);
    TCA6416 tca_bms(&i2cBus, 0x21);
    tca.i2cdetect();
    tca.begin(tca_dirs);

    tca.set_state(1, 3, 0);
    printf("MCU_Latch: %d\n", tca.get_state(1, 3));
    wait_us(1000000);
    tca.set_state(1, 3, 1);
    printf("MCU_Latch: %d\n", tca.get_state(1, 3));
    wait_us(1000000);
    tca.set_state(1, 3, 0);
    printf("MCU_Latch: %d\n", tca.get_state(1, 3));


    // the following are the 3 INAs on MainIO. Only leave one uncommented when running
    //INA219* ina = new INA219(&i2cBus, 0x40, 0.005, 2.0);
    //INA219* ina = new INA219(&i2cBus, 0x44, 0.005, 2.0); 
    //INA219* ina = new INA219(&i2cBus, 0x41, 0.005, 1.0);
    //ina.begin();

    BMS bms(c);
    
    if(!runUart(&tca)) {
        printf("the UART application is running\n");
    } else {
        printf("NOT RUNNING\n");
        exit(1);
    }
    int toggle = 0;
    for (;;) {
        printf("\e[1;1H\e[2J");
        printf("MCU_Stat_fdbk: %d\n", !tca.get_state(0, 1));
        printf("mcu_hv_en (main): %d\n", get_mcu_hv_en());
        printf("IMD_fdbk: %d\n", !tca.get_state(0, 2));
        printf("MPO 2: %d\n", mpo_2);
        printf("Lim_fdbk: %d\n", !tca.get_state(0, 3));
        printf("Inertia_fdbk: %d\n", !tca.get_state(1, 7));
        printf("Ext_Estop_fdbk: %d\n", !tca.get_state(1, 5));
        printf("Driver_Estop_fdbk: %d\n", !tca.get_state(1, 4));
        printf("Charge Enable: %d\n", tca_bms.get_state(1, 5));
        printf("Discharge Enable: %d\n", tca_bms.get_state(1, 6));
        if (toggle == 0) {
            toggle = 1;
        } else {
            toggle = 0;
        }
        //tca.set_state(0, 0, toggle);
        printf("Charge: %f\n", bms.getPackStateOfCharge());
        printf("Voltage: %f\n", bms.getPackVoltage());
        printf("Current (Main): %f\n", bms.getPackCurrent());
        printf("Avg Temp: %f\n", bms.getAvgTemperature());
        printf("Internal Temp:%f\n", bms.getInternalTemperature());
        printf("Fan Speed: %d\n", bms.getFanSpeed());
        //wait_us(1000000);
        // modify the byte array and put printouts here

        // this has to be set to 1 for the UART app to not get stuck at the fault screen. 
        // it will probably change in the future once software updates the
        // checkRestartEnable() method in DataUnpacker.cpp 
        // TODO set_door(toggle);

        // bms updateGPIO method
        mpi_1 = tca_bms.get_state(1, 2); // BMS_MPI1
        mpi_2 = tca_bms.get_state(1, 3); // BMS_MPI2
        mpo_2 = tca_bms.get_state(1, 4); // BMS_MPO2
        //set_imd_status(!tca.get_state(0, 2));
        set_imd_status(mpo_2);
        set_charge_enable(tca_bms.get_state(1, 5)); // BMS_CHRG_EN
        set_discharge_enable(tca_bms.get_state(1, 6)); // BMS_DSCHRG_EN
        // update external_eStop
        set_external_eStop(!tca.get_state(1, 5)); // Ext_Estop_Fdbk
        set_driver_eStop(!tca.get_state(1, 4));
        set_crash(!tca.get_state(1, 7));
        set_door(!tca.get_state(0, 3));
        set_mcu_stat_fdbk(!tca.get_state(0, 1));

        wait_us(1000000);
    }
    
    printf("Hello, Mbed!\n");
    return 0;
}*/

#define BLINKING_RATE     2000ms
// Main code. Should initialize devices and then transform into the CAN loop

int main()
{
    int iteration = 0;

#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

    while(1)
    {
        // LED blink
        led = !led;
        printf("Blink num %d\n", iteration);

        if(iteration >= 10)
            printf("Done\n");
        iteration ++;

        ThisThread::sleep_for(BLINKING_RATE);
    }

    printf("Hello, Mbed!\n");
    return 0;
}
