#include "mppt.h"
#define msgIdMaxCurrent 0x10

/**
* MPPT CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
int MPPT::callback(CANMessage &msg) {
	if (msg.id == msgIdMaxCurrent) {
    maxCurrent = *((float *)msg.data);
  }

  return 0;
}

float MPPT::getMaxCurrent() { return maxCurrent; }