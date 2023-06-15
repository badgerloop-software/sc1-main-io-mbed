#ifndef __uartApp__h__
#define __uartApp__h__

#include "mbed.h"
#include "tca6416.h"
#include "uart.h"
#pragma pack(push, 1)

/*!!AUTO-GENERATE HERE!!*/

bool get_restart_enable();

void cleardfdata();

int runUart(TCA6416* initTca, Mutex* initTcaMutex);

#pragma pack(pop)
#endif
