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
    }
}

