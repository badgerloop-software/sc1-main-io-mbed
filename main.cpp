#include "mbed.h"
#include "uartApp.h"

// main() runs in its own thread in the OS
int main()
{
    if(runUart()) {
        printf("UART application is not running\n");
        exit(1);
    } 
    while (true) {

    }
}

