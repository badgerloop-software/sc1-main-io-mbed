//#include "bms.h"
//#include "i2cdevice.h"
//#include "ina219.h"
#include "mbed.h"
#include "rtos.h"
//#include "tca6416.h"
//#include "uartApp.h"

#if defined(BLINK_RATE_250)
#define BLINKING_RATE     250ms
#elif defined(BLINK_RATE)
#define BLINKING_RATE     BLINK_RATE
#else
#define BLINKING_RATE     2000ms
#endif

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

    return 0;
}
