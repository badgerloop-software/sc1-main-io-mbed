#include "mcc.h"

/**
* MCC CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
int MCC::callback(CANMessage &msg) {
  printf("callback entered\n");
  switch (msg.id) {
  case 0x200:
    curRPM = *((float*) msg.data);
  case 0x201:
    curGPIO = *((uint16_t*) msg.data);
  case 0x202:
    curAcc = *((float*) msg.data);
  case 0x203:
    curBrk = *((float*) msg.data);
  }

  return 0;
}

float MCC::getCurRPM(void) { return curRPM; }
uint16_t MCC::getCurGPIO(void) { return curGPIO; }
float MCC::getCurAcc(void) { return curAcc; }
float MCC::getCurBrk(void) { return curBrk; }