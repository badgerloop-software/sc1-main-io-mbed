#ifndef __MPPT_H__
#define __MPPT_H__
#include "can.h"
#include "stdio.h"
#include "mbed.h"

/**
* MPPT CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
class MPPT : Can::device {
private:
  float maxCurrent;

public:
  MPPT(Can &c) : device(c) {}

  int callback(CANMessage &msg);

  float getMaxCurrent(void);
  
};



#endif