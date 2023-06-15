#include <iostream>

#include "rtos.h"
#include "uartApp.h"
#define NUM_COMMAND_BYTES 2
#define T_MESSAGE_US \
  1000000            // 1 second right now (should actually be 1/15 of a second)
#define HEARTBEAT 2  // error state if this # messages that aren't read

Thread thread1;
Thread thread2;
Mutex uart_buffer;
Mutex dfwrite_mutex;
static Mutex* tcaMutex;

static TCA6416* tca;

data_format dfwrite;
data_format dfdata;
data_format emptyStruct;

bool restart_enable;
bool parking_brake; 

void clearDataFormatRead() { dfdata = emptyStruct; }

void check_shutdown_errors();
void check_mcu_check();
void copyDataStructToWriteStruct();

void send_message_thread() {
  while (true) {
    check_mcu_check(); // set mcu_check based on other values
    check_shutdown_errors();  // check if mcu_hv_en needs to be set to 0

    copyDataStructToWriteStruct();
    uart_buffer.lock();
    writeUart(&dfwrite, TOTAL_BYTES);
    uart_buffer.unlock();
    wait_us(T_MESSAGE_US);
  }
}

void read_command_thread() {
  int messages_not_received =
      0;  // number of consecutive messages DriverIO fails to send
  bool restart_enable_error = 0;  // check if restart_enable has been 1
  int i = 0;
  while (true) {
    uart_buffer.lock();
    char read_array[NUM_COMMAND_BYTES]; 
    // set mcu_hv_en to 0 (error state) if HEARTBEAT consecutive messages aren't
    // read
    if (readUart(read_array, NUM_COMMAND_BYTES) == 0) {
      printf("message not received\n");
      if (++messages_not_received >= HEARTBEAT) {
        printf("heartbeat lost\n");
        set_mcu_hv_en(0);
        set_mainIO_heartbeat(0);
        // Write MCU_HV_EN = 0 to stop the car
        tcaMutex->lock();
        tca->set_state(0, 0, 0);
        tcaMutex->unlock();
      }
    } else {  // a message was read
      messages_not_received = 0;
      set_mainIO_heartbeat(1);

      // set restart_enable and parking_brake based on read_array
      restart_enable = read_array[0];
      parking_brake = read_array[1];
      // printout parking brake
      printf("parking brake: %d\n", parking_brake);

      // check that we've received at least one restart_enable == 1 before we
      // set mcu_hv_en high again
      if (restart_enable) {
        restart_enable_error = true;
      }
      if (restart_enable == 0 && get_mcu_hv_en() == 0 && restart_enable_error) {
        set_mcu_hv_en(1);
        // Write MCU_HV_EN = 1 to start the car
        tcaMutex->lock();
        tca->set_state(0, 0, 1);
        tcaMutex->unlock();
        restart_enable_error = false;
      }
      // print statement (delete if not needed)
      if (get_restart_enable()) {
          printf("restart enable signal received and is 1\n");
      }
      if (!get_mcu_hv_en()) {
          printf("mcu_hv_en is 0\n");
      }
      printf("loop %i======================================\n", i++);
    }
    uart_buffer.unlock();
    wait_us(T_MESSAGE_US);
  }
}

int runUart(TCA6416* initTca, Mutex* initTcaMutex) {
  tcaMutex = initTcaMutex;
  tca = initTca;
  initUart();
  thread1.start(read_command_thread);
  thread2.start(send_message_thread);
  return 0;
}

Mutex restart_enable_mutex;

bool get_restart_enable() {
  restart_enable_mutex.lock();
  bool val = restart_enable;
  restart_enable_mutex.unlock();
  return val;
}

/*!!AUTO-GENERATE HERE!!*/

// Checks shutdown error values
void check_shutdown_errors() {
  if (get_driver_eStop() || get_external_eStop() || get_crash() || get_door() || get_imd_status() || get_door_lim_out() || get_mcu_check()) {
    set_mcu_hv_en(0); // error state
    // Write MCU_HV_EN = 0 to stop the car
    tcaMutex->lock();
    tca->set_state(0, 0, 0);
    tcaMutex->unlock();
  }
}

void check_mcu_check() {
  // TODO figure out what signals are needed here
  // spreadsheet, MainIO row 13
  if (!get_mainIO_heartbeat() ||
      get_voltage_failsafe() || get_pack_voltage() < 77.5 || get_pack_voltage() > 111.6 // Pack voltage
      ) {
    set_mcu_check(1); // error state
  }
}
