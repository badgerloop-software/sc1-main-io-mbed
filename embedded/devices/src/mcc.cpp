#include "mcc.h"

#define POWER_BIT 0x1 << 0
#define DIRECTION_BIT 0x1 << 1
#define DIRECTION_OUT_BIT 0x1 << 2
#define BRAKE_BIT 0x1 << 3
#define ECO_BIT 0x1 << 4
#define CRZ_EN_BIT 0x1 << 5
#define CRZ_M_BIT 0x1 << 6  // 0 = Mode A, RPM; 1 = Mode B, Power
#define MC_STAT_BIT 0x1 << 7

/**
* MCC CAN device
*
* Authors: Khiem Vu and Jonathan Wang
*/
int MCC::callback(CANMessage &msg) {
  switch (msg.id) {
  case 0x200:
    curRPM = *((float*) msg.data);
    set_speed(((curRPM*2*(22.0/7.0)*0.2746375)/60.0)*2.23694); 
    //d = 21.625 inches, pi = 22/7, r = 0.2746375 m, m/s -> mph = 2.23694
    break;
    
  case 0x201:
    curGPIO = *((uint16_t*) msg.data);
    set_motor_power(curGPIO & POWER_BIT);
    set_fr_telem(curGPIO & DIRECTION_BIT);
    set_fr_out(curGPIO & DIRECTION_OUT_BIT);
    set_brake_status(curGPIO & BRAKE_BIT); // difference between this and case 0x203?
    set_eco(curGPIO & ECO_BIT);
    // set_crz_state(curGPIO & CRZ_EN_BIT);
    set_crz_spd_mode(!(curGPIO & CRZ_M_BIT)); // Mode A: speed/RPM
    set_crz_pwr_mode(curGPIO & CRZ_M_BIT); // Mode B: power
    set_mc_status(curGPIO & MC_STAT_BIT);
    break;

  case 0x202:
    curAcc = *((float*) msg.data);
    set_accelerator(curAcc);
    break;

  case 0x203:
    curBrk = *((float*) msg.data);
    set_brake_status(curBrk);
    break;

  default:
    return 1;
    break;

  }

  return 0;
}

float MCC::getCurRPM(void) { return curRPM; }
uint16_t MCC::getCurGPIO(void) { return curGPIO; }
float MCC::getCurAcc(void) { return curAcc; }
float MCC::getCurBrk(void) { return curBrk; }