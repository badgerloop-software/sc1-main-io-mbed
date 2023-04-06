#include "mbed.h"
#include "uartApp.h"
#include "i2cdevice.h"
#include "tca6416.h"

int main(void){

    if(runUart()) {
        printf("UART application is not running\n");
        exit(1);
    } 
    
    while (1) {

    }
}
