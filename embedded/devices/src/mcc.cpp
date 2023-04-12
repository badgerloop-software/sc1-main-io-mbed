#include "mcc.h"

#define POWER_BIT 0x1 << 0
#define DIRECTION_BIT 0x1 << 1
#define BRAKE_BIT 0x1 << 2
#define ECO_BIT 0x1 << 3
#define CRZ_EN_BIT 0x1 << 4
#define CRZ_M_BIT 0x1 << 5  // 0 = Mode A, RPM; 1 = Mode B, Power
#define MC_STAT_BIT 0x1 << 6

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
    // set_speed(curRPM*speed_convert);
  case 0x201:
    curGPIO = *((uint16_t*) msg.data);
    set_motor_power(curGPIO & POWER_BIT);
        // set_fr__?(curGPIO & DIRECTION_BIT);
    set_brake_status(curGPIO & BRAKE_BIT); // difference between this and case 0x203?
    set_eco(curGPIO & ECO_BIT);
    // set_crz_state(curGPIO & CRZ_EN_BIT);
    // set_crz_pwr_mode(curGPIO & CRZ_M_BIT);
    set_mc_status(curGPIO & MC_STAT_BIT);


  case 0x202:
    curAcc = *((float*) msg.data);
    set_accelerator(curAcc);
  case 0x203:
    curBrk = *((float*) msg.data);
    set_brake_status(curBrk);
    
  }

  return 0;
}

float MCC::getCurRPM(void) { return curRPM; }
uint16_t MCC::getCurGPIO(void) { return curGPIO; }
float MCC::getCurAcc(void) { return curAcc; }
float MCC::getCurBrk(void) { return curBrk; }