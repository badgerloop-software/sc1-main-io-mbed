#ifndef __MCC_H__
#define __MCC_H__

#include "can.h"
#include "uartApp.h"
#include "mbed.h"
#include "stdio.h"

/**
* MCC CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
class MCC : Can::device {
private:
  float curRPM;
  uint16_t curGPIO;
  float curAcc;
  float curBrk;

public:
  MCC(Can& c) : device(c) {}

  int callback(CANMessage &msg);

  float getCurRPM(void);
  uint16_t getCurGPIO(void);
  float getCurAcc(void);
  float getCurBrk(void);
};

#endif