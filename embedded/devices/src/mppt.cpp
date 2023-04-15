#include "mppt.h"
#define msgIdMaxCurrent 0x10

/**
* MPPT CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
int MPPT::callback(CANMessage &msg) {
    printf("callback entered\n");
	if (msg.id == msgIdMaxCurrent) {
        maxCurrent = *((float *)msg.data);
        // maxCurrent = msg.data[0] + (msg.data[1]<<1) + (msg.data[2]<<2) + (msg.data[3]<<3) + (msg.data[4]<<4) + (msg.data[5]<<5) + (msg.data[6]<<6) + (msg.data[7]<<7);
        set_mppt_current_out(maxCurrent);
        printf("modified, %f\n", maxCurrent);
        return 0;
    }

  return 1;
}

float MPPT::getMaxCurrent() { return maxCurrent; }