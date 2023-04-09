#include "mbed.h"
#include "uartApp.h"

// main() runs in its own thread in the OS
int main()
{
    if(!runUart()) {
        printf("the UART application is running\n");
    } else {
        printf("NOT RUNNING\n");
        exit(1);
    }
    while (true) {
        // modify the byte array and put printouts here

        // this has to be set to 1 for the UART app to not get stuck at the fault screen. 
        // it will probably change in the future once software updates the
        // checkRestartEnable() method in DataUnpacker.cpp 
        set_door(1); 
    }
}


