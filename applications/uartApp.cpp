
        /*
         * This is an auto-generated file which is automatically generated whenever the target is built
         */


        
#include "uartApp.h"
#include "rtos.h"
#include <iostream>

Thread thread1;
Thread thread2;

data_format dfwrite;
data_format dfdata;
data_format emptyStruct;

Mutex uart_buffer;

bool restart_enable;

void clearDataFormatRead() { dfdata = emptyStruct; }

void send_message_thread() {
    while(true) {
        uart_buffer.lock();
        writeUart(&dfwrite, totalBytes);
        uart_buffer.unlock();
        wait_us(1000000);
    }
}

// TODO fix this method to how we want to read commands from DriverIO
void read_command_thread() {
    while(true) {
        uart_buffer.lock();
        restart_enable = 0;
        readUart(&restart_enable, numCommandBytes);
        uart_buffer.unlock();
        wait_us(1000000);
    }
}

int runUart() {
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

Mutex speed_mutex;
Mutex driver_eStop_mutex;
Mutex external_eStop_mutex;
Mutex battery_eStop_mutex;
Mutex crash_mutex;
Mutex door_mutex;
Mutex mcu_check_mutex;
Mutex imd_status_mutex;
Mutex state_mutex;
Mutex linear_accel_x_mutex;
Mutex linear_accel_y_mutex;
Mutex linear_accel_z_mutex;
Mutex angular_rate_pitch_mutex;
Mutex angular_rate_roll_mutex;
Mutex angular_rate_yaw_mutex;
Mutex motor_temp_mutex;
Mutex motor_controller_temp_mutex;
Mutex dcdc_temp_mutex;
Mutex driverIO_temp_mutex;
Mutex mainIO_temp_mutex;
Mutex cabin_temp_mutex;
Mutex road_temp_mutex;
Mutex brake_temp_mutex;
Mutex air_temp_mutex;
Mutex cruise_mutex;
Mutex left_turn_mutex;
Mutex right_turn_mutex;
Mutex hazards_mutex;
Mutex headlights_mutex;
Mutex mainIO_heartbeat_mutex;
Mutex accelerator_mutex;
Mutex bus_5V_mutex;
Mutex bus_12V_mutex;
Mutex mainIO_current_in_mutex;
Mutex driverIO_current_in_mutex;
Mutex power_critical_mutex;
Mutex power_warning_mutex;
Mutex power_tc_mutex;
Mutex tstamp_ms_mutex;
Mutex tstamp_sc_mutex;
Mutex tstamp_mn_mutex;
Mutex tstamp_hr_mutex;
Mutex mps_enable_mutex;
Mutex mppt_contactor_mutex;
Mutex motor_controller_contactor_mutex;
Mutex low_contactor_mutex;
Mutex dcdc_valid_mutex;
Mutex supplemental_valid_mutex;
Mutex mppt_mode_mutex;
Mutex mppt_current_out_mutex;
Mutex string1_temp_mutex;
Mutex string2_temp_mutex;
Mutex string3_temp_mutex;
Mutex pack_temp_mutex;
Mutex pack_current_mutex;
Mutex pack_voltage_mutex;
Mutex cell_group1_voltage_mutex;
Mutex cell_group2_voltage_mutex;
Mutex cell_group3_voltage_mutex;
Mutex cell_group4_voltage_mutex;
Mutex cell_group5_voltage_mutex;
Mutex cell_group6_voltage_mutex;
Mutex cell_group7_voltage_mutex;
Mutex cell_group8_voltage_mutex;
Mutex cell_group9_voltage_mutex;
Mutex cell_group10_voltage_mutex;
Mutex cell_group11_voltage_mutex;
Mutex cell_group12_voltage_mutex;
Mutex cell_group13_voltage_mutex;
Mutex cell_group14_voltage_mutex;
Mutex cell_group15_voltage_mutex;
Mutex cell_group16_voltage_mutex;
Mutex cell_group17_voltage_mutex;
Mutex cell_group18_voltage_mutex;
Mutex cell_group19_voltage_mutex;
Mutex cell_group20_voltage_mutex;
Mutex cell_group21_voltage_mutex;
Mutex cell_group22_voltage_mutex;
Mutex cell_group23_voltage_mutex;
Mutex cell_group24_voltage_mutex;
Mutex cell_group25_voltage_mutex;
Mutex cell_group26_voltage_mutex;
Mutex cell_group27_voltage_mutex;
Mutex cell_group28_voltage_mutex;
Mutex cell_group29_voltage_mutex;
Mutex cell_group30_voltage_mutex;
Mutex soc_mutex;
Mutex soh_mutex;
Mutex pack_capacity_mutex;
Mutex adaptive_total_capacity_mutex;
Mutex bps_fault_mutex;
Mutex fan_speed_mutex;
Mutex voltage_failsafe_mutex;
Mutex current_failsafe_mutex;
Mutex supply_power_failsafe_mutex;
Mutex memory_failsafe_mutex;
Mutex relay_failsafe_mutex;
Mutex bms_canbus_failure_mutex;
Mutex pack_resistance_mutex;
Mutex avg_cell_resistance_mutex;
Mutex bms_input_voltage_mutex;

void copyDataStructToWriteStruct(){
  dfwrite.speed = get_speed();
  dfwrite.driver_eStop = get_driver_eStop();
  dfwrite.external_eStop = get_external_eStop();
  dfwrite.battery_eStop = get_battery_eStop();
  dfwrite.crash = get_crash();
  dfwrite.door = get_door();
  dfwrite.mcu_check = get_mcu_check();
  dfwrite.imd_status = get_imd_status();
  dfwrite.state = get_state();
  dfwrite.linear_accel_x = get_linear_accel_x();
  dfwrite.linear_accel_y = get_linear_accel_y();
  dfwrite.linear_accel_z = get_linear_accel_z();
  dfwrite.angular_rate_pitch = get_angular_rate_pitch();
  dfwrite.angular_rate_roll = get_angular_rate_roll();
  dfwrite.angular_rate_yaw = get_angular_rate_yaw();
  dfwrite.motor_temp = get_motor_temp();
  dfwrite.motor_controller_temp = get_motor_controller_temp();
  dfwrite.dcdc_temp = get_dcdc_temp();
  dfwrite.driverIO_temp = get_driverIO_temp();
  dfwrite.mainIO_temp = get_mainIO_temp();
  dfwrite.cabin_temp = get_cabin_temp();
  dfwrite.road_temp = get_road_temp();
  dfwrite.brake_temp = get_brake_temp();
  dfwrite.air_temp = get_air_temp();
  dfwrite.cruise = get_cruise();
  dfwrite.left_turn = get_left_turn();
  dfwrite.right_turn = get_right_turn();
  dfwrite.hazards = get_hazards();
  dfwrite.headlights = get_headlights();
  dfwrite.mainIO_heartbeat = get_mainIO_heartbeat();
  dfwrite.accelerator = get_accelerator();
  dfwrite.bus_5V = get_bus_5V();
  dfwrite.bus_12V = get_bus_12V();
  dfwrite.mainIO_current_in = get_mainIO_current_in();
  dfwrite.driverIO_current_in = get_driverIO_current_in();
  dfwrite.power_critical = get_power_critical();
  dfwrite.power_warning = get_power_warning();
  dfwrite.power_tc = get_power_tc();
  dfwrite.tstamp_ms = get_tstamp_ms();
  dfwrite.tstamp_sc = get_tstamp_sc();
  dfwrite.tstamp_mn = get_tstamp_mn();
  dfwrite.tstamp_hr = get_tstamp_hr();
  dfwrite.mps_enable = get_mps_enable();
  dfwrite.mppt_contactor = get_mppt_contactor();
  dfwrite.motor_controller_contactor = get_motor_controller_contactor();
  dfwrite.low_contactor = get_low_contactor();
  dfwrite.dcdc_valid = get_dcdc_valid();
  dfwrite.supplemental_valid = get_supplemental_valid();
  dfwrite.mppt_mode = get_mppt_mode();
  dfwrite.mppt_current_out = get_mppt_current_out();
  dfwrite.string1_temp = get_string1_temp();
  dfwrite.string2_temp = get_string2_temp();
  dfwrite.string3_temp = get_string3_temp();
  dfwrite.pack_temp = get_pack_temp();
  dfwrite.pack_current = get_pack_current();
  dfwrite.pack_voltage = get_pack_voltage();
  dfwrite.cell_group1_voltage = get_cell_group1_voltage();
  dfwrite.cell_group2_voltage = get_cell_group2_voltage();
  dfwrite.cell_group3_voltage = get_cell_group3_voltage();
  dfwrite.cell_group4_voltage = get_cell_group4_voltage();
  dfwrite.cell_group5_voltage = get_cell_group5_voltage();
  dfwrite.cell_group6_voltage = get_cell_group6_voltage();
  dfwrite.cell_group7_voltage = get_cell_group7_voltage();
  dfwrite.cell_group8_voltage = get_cell_group8_voltage();
  dfwrite.cell_group9_voltage = get_cell_group9_voltage();
  dfwrite.cell_group10_voltage = get_cell_group10_voltage();
  dfwrite.cell_group11_voltage = get_cell_group11_voltage();
  dfwrite.cell_group12_voltage = get_cell_group12_voltage();
  dfwrite.cell_group13_voltage = get_cell_group13_voltage();
  dfwrite.cell_group14_voltage = get_cell_group14_voltage();
  dfwrite.cell_group15_voltage = get_cell_group15_voltage();
  dfwrite.cell_group16_voltage = get_cell_group16_voltage();
  dfwrite.cell_group17_voltage = get_cell_group17_voltage();
  dfwrite.cell_group18_voltage = get_cell_group18_voltage();
  dfwrite.cell_group19_voltage = get_cell_group19_voltage();
  dfwrite.cell_group20_voltage = get_cell_group20_voltage();
  dfwrite.cell_group21_voltage = get_cell_group21_voltage();
  dfwrite.cell_group22_voltage = get_cell_group22_voltage();
  dfwrite.cell_group23_voltage = get_cell_group23_voltage();
  dfwrite.cell_group24_voltage = get_cell_group24_voltage();
  dfwrite.cell_group25_voltage = get_cell_group25_voltage();
  dfwrite.cell_group26_voltage = get_cell_group26_voltage();
  dfwrite.cell_group27_voltage = get_cell_group27_voltage();
  dfwrite.cell_group28_voltage = get_cell_group28_voltage();
  dfwrite.cell_group29_voltage = get_cell_group29_voltage();
  dfwrite.cell_group30_voltage = get_cell_group30_voltage();
  dfwrite.soc = get_soc();
  dfwrite.soh = get_soh();
  dfwrite.pack_capacity = get_pack_capacity();
  dfwrite.adaptive_total_capacity = get_adaptive_total_capacity();
  dfwrite.bps_fault = get_bps_fault();
  dfwrite.fan_speed = get_fan_speed();
  dfwrite.voltage_failsafe = get_voltage_failsafe();
  dfwrite.current_failsafe = get_current_failsafe();
  dfwrite.supply_power_failsafe = get_supply_power_failsafe();
  dfwrite.memory_failsafe = get_memory_failsafe();
  dfwrite.relay_failsafe = get_relay_failsafe();
  dfwrite.bms_canbus_failure = get_bms_canbus_failure();
  dfwrite.pack_resistance = get_pack_resistance();
  dfwrite.avg_cell_resistance = get_avg_cell_resistance();
  dfwrite.bms_input_voltage = get_bms_input_voltage();
}

float get_speed() {
  speed_mutex.lock();
  float val = dfdata.speed;
  speed_mutex.unlock();
  return val;
}
void set_speed(float val) {
  speed_mutex.lock();
  dfdata.speed = val;
  speed_mutex.unlock();
}

bool get_driver_eStop() {
  driver_eStop_mutex.lock();
  bool val = dfdata.driver_eStop;
  driver_eStop_mutex.unlock();
  return val;
}
void set_driver_eStop(bool val) {
  driver_eStop_mutex.lock();
  dfdata.driver_eStop = val;
  driver_eStop_mutex.unlock();
}

bool get_external_eStop() {
  external_eStop_mutex.lock();
  bool val = dfdata.external_eStop;
  external_eStop_mutex.unlock();
  return val;
}
void set_external_eStop(bool val) {
  external_eStop_mutex.lock();
  dfdata.external_eStop = val;
  external_eStop_mutex.unlock();
}

bool get_battery_eStop() {
  battery_eStop_mutex.lock();
  bool val = dfdata.battery_eStop;
  battery_eStop_mutex.unlock();
  return val;
}
void set_battery_eStop(bool val) {
  battery_eStop_mutex.lock();
  dfdata.battery_eStop = val;
  battery_eStop_mutex.unlock();
}

bool get_crash() {
  crash_mutex.lock();
  bool val = dfdata.crash;
  crash_mutex.unlock();
  return val;
}
void set_crash(bool val) {
  crash_mutex.lock();
  dfdata.crash = val;
  crash_mutex.unlock();
}

bool get_door() {
  door_mutex.lock();
  bool val = dfdata.door;
  door_mutex.unlock();
  return val;
}
void set_door(bool val) {
  door_mutex.lock();
  dfdata.door = val;
  door_mutex.unlock();
}

bool get_mcu_check() {
  mcu_check_mutex.lock();
  bool val = dfdata.mcu_check;
  mcu_check_mutex.unlock();
  return val;
}
void set_mcu_check(bool val) {
  mcu_check_mutex.lock();
  dfdata.mcu_check = val;
  mcu_check_mutex.unlock();
}

bool get_imd_status() {
  imd_status_mutex.lock();
  bool val = dfdata.imd_status;
  imd_status_mutex.unlock();
  return val;
}
void set_imd_status(bool val) {
  imd_status_mutex.lock();
  dfdata.imd_status = val;
  imd_status_mutex.unlock();
}

char get_state() {
  state_mutex.lock();
  char val = dfdata.state;
  state_mutex.unlock();
  return val;
}
void set_state(char val) {
  state_mutex.lock();
  dfdata.state = val;
  state_mutex.unlock();
}

float get_linear_accel_x() {
  linear_accel_x_mutex.lock();
  float val = dfdata.linear_accel_x;
  linear_accel_x_mutex.unlock();
  return val;
}
void set_linear_accel_x(float val) {
  linear_accel_x_mutex.lock();
  dfdata.linear_accel_x = val;
  linear_accel_x_mutex.unlock();
}

float get_linear_accel_y() {
  linear_accel_y_mutex.lock();
  float val = dfdata.linear_accel_y;
  linear_accel_y_mutex.unlock();
  return val;
}
void set_linear_accel_y(float val) {
  linear_accel_y_mutex.lock();
  dfdata.linear_accel_y = val;
  linear_accel_y_mutex.unlock();
}

float get_linear_accel_z() {
  linear_accel_z_mutex.lock();
  float val = dfdata.linear_accel_z;
  linear_accel_z_mutex.unlock();
  return val;
}
void set_linear_accel_z(float val) {
  linear_accel_z_mutex.lock();
  dfdata.linear_accel_z = val;
  linear_accel_z_mutex.unlock();
}

float get_angular_rate_pitch() {
  angular_rate_pitch_mutex.lock();
  float val = dfdata.angular_rate_pitch;
  angular_rate_pitch_mutex.unlock();
  return val;
}
void set_angular_rate_pitch(float val) {
  angular_rate_pitch_mutex.lock();
  dfdata.angular_rate_pitch = val;
  angular_rate_pitch_mutex.unlock();
}

float get_angular_rate_roll() {
  angular_rate_roll_mutex.lock();
  float val = dfdata.angular_rate_roll;
  angular_rate_roll_mutex.unlock();
  return val;
}
void set_angular_rate_roll(float val) {
  angular_rate_roll_mutex.lock();
  dfdata.angular_rate_roll = val;
  angular_rate_roll_mutex.unlock();
}

float get_angular_rate_yaw() {
  angular_rate_yaw_mutex.lock();
  float val = dfdata.angular_rate_yaw;
  angular_rate_yaw_mutex.unlock();
  return val;
}
void set_angular_rate_yaw(float val) {
  angular_rate_yaw_mutex.lock();
  dfdata.angular_rate_yaw = val;
  angular_rate_yaw_mutex.unlock();
}

float get_motor_temp() {
  motor_temp_mutex.lock();
  float val = dfdata.motor_temp;
  motor_temp_mutex.unlock();
  return val;
}
void set_motor_temp(float val) {
  motor_temp_mutex.lock();
  dfdata.motor_temp = val;
  motor_temp_mutex.unlock();
}

float get_motor_controller_temp() {
  motor_controller_temp_mutex.lock();
  float val = dfdata.motor_controller_temp;
  motor_controller_temp_mutex.unlock();
  return val;
}
void set_motor_controller_temp(float val) {
  motor_controller_temp_mutex.lock();
  dfdata.motor_controller_temp = val;
  motor_controller_temp_mutex.unlock();
}

float get_dcdc_temp() {
  dcdc_temp_mutex.lock();
  float val = dfdata.dcdc_temp;
  dcdc_temp_mutex.unlock();
  return val;
}
void set_dcdc_temp(float val) {
  dcdc_temp_mutex.lock();
  dfdata.dcdc_temp = val;
  dcdc_temp_mutex.unlock();
}

float get_driverIO_temp() {
  driverIO_temp_mutex.lock();
  float val = dfdata.driverIO_temp;
  driverIO_temp_mutex.unlock();
  return val;
}
void set_driverIO_temp(float val) {
  driverIO_temp_mutex.lock();
  dfdata.driverIO_temp = val;
  driverIO_temp_mutex.unlock();
}

float get_mainIO_temp() {
  mainIO_temp_mutex.lock();
  float val = dfdata.mainIO_temp;
  mainIO_temp_mutex.unlock();
  return val;
}
void set_mainIO_temp(float val) {
  mainIO_temp_mutex.lock();
  dfdata.mainIO_temp = val;
  mainIO_temp_mutex.unlock();
}

float get_cabin_temp() {
  cabin_temp_mutex.lock();
  float val = dfdata.cabin_temp;
  cabin_temp_mutex.unlock();
  return val;
}
void set_cabin_temp(float val) {
  cabin_temp_mutex.lock();
  dfdata.cabin_temp = val;
  cabin_temp_mutex.unlock();
}

float get_road_temp() {
  road_temp_mutex.lock();
  float val = dfdata.road_temp;
  road_temp_mutex.unlock();
  return val;
}
void set_road_temp(float val) {
  road_temp_mutex.lock();
  dfdata.road_temp = val;
  road_temp_mutex.unlock();
}

float get_brake_temp() {
  brake_temp_mutex.lock();
  float val = dfdata.brake_temp;
  brake_temp_mutex.unlock();
  return val;
}
void set_brake_temp(float val) {
  brake_temp_mutex.lock();
  dfdata.brake_temp = val;
  brake_temp_mutex.unlock();
}

float get_air_temp() {
  air_temp_mutex.lock();
  float val = dfdata.air_temp;
  air_temp_mutex.unlock();
  return val;
}
void set_air_temp(float val) {
  air_temp_mutex.lock();
  dfdata.air_temp = val;
  air_temp_mutex.unlock();
}

bool get_cruise() {
  cruise_mutex.lock();
  bool val = dfdata.cruise;
  cruise_mutex.unlock();
  return val;
}
void set_cruise(bool val) {
  cruise_mutex.lock();
  dfdata.cruise = val;
  cruise_mutex.unlock();
}

bool get_left_turn() {
  left_turn_mutex.lock();
  bool val = dfdata.left_turn;
  left_turn_mutex.unlock();
  return val;
}
void set_left_turn(bool val) {
  left_turn_mutex.lock();
  dfdata.left_turn = val;
  left_turn_mutex.unlock();
}

bool get_right_turn() {
  right_turn_mutex.lock();
  bool val = dfdata.right_turn;
  right_turn_mutex.unlock();
  return val;
}
void set_right_turn(bool val) {
  right_turn_mutex.lock();
  dfdata.right_turn = val;
  right_turn_mutex.unlock();
}

bool get_hazards() {
  hazards_mutex.lock();
  bool val = dfdata.hazards;
  hazards_mutex.unlock();
  return val;
}
void set_hazards(bool val) {
  hazards_mutex.lock();
  dfdata.hazards = val;
  hazards_mutex.unlock();
}

bool get_headlights() {
  headlights_mutex.lock();
  bool val = dfdata.headlights;
  headlights_mutex.unlock();
  return val;
}
void set_headlights(bool val) {
  headlights_mutex.lock();
  dfdata.headlights = val;
  headlights_mutex.unlock();
}

bool get_mainIO_heartbeat() {
  mainIO_heartbeat_mutex.lock();
  bool val = dfdata.mainIO_heartbeat;
  mainIO_heartbeat_mutex.unlock();
  return val;
}
void set_mainIO_heartbeat(bool val) {
  mainIO_heartbeat_mutex.lock();
  dfdata.mainIO_heartbeat = val;
  mainIO_heartbeat_mutex.unlock();
}

float get_accelerator() {
  accelerator_mutex.lock();
  float val = dfdata.accelerator;
  accelerator_mutex.unlock();
  return val;
}
void set_accelerator(float val) {
  accelerator_mutex.lock();
  dfdata.accelerator = val;
  accelerator_mutex.unlock();
}

float get_bus_5V() {
  bus_5V_mutex.lock();
  float val = dfdata.bus_5V;
  bus_5V_mutex.unlock();
  return val;
}
void set_bus_5V(float val) {
  bus_5V_mutex.lock();
  dfdata.bus_5V = val;
  bus_5V_mutex.unlock();
}

float get_bus_12V() {
  bus_12V_mutex.lock();
  float val = dfdata.bus_12V;
  bus_12V_mutex.unlock();
  return val;
}
void set_bus_12V(float val) {
  bus_12V_mutex.lock();
  dfdata.bus_12V = val;
  bus_12V_mutex.unlock();
}

float get_mainIO_current_in() {
  mainIO_current_in_mutex.lock();
  float val = dfdata.mainIO_current_in;
  mainIO_current_in_mutex.unlock();
  return val;
}
void set_mainIO_current_in(float val) {
  mainIO_current_in_mutex.lock();
  dfdata.mainIO_current_in = val;
  mainIO_current_in_mutex.unlock();
}

float get_driverIO_current_in() {
  driverIO_current_in_mutex.lock();
  float val = dfdata.driverIO_current_in;
  driverIO_current_in_mutex.unlock();
  return val;
}
void set_driverIO_current_in(float val) {
  driverIO_current_in_mutex.lock();
  dfdata.driverIO_current_in = val;
  driverIO_current_in_mutex.unlock();
}

bool get_power_critical() {
  power_critical_mutex.lock();
  bool val = dfdata.power_critical;
  power_critical_mutex.unlock();
  return val;
}
void set_power_critical(bool val) {
  power_critical_mutex.lock();
  dfdata.power_critical = val;
  power_critical_mutex.unlock();
}

bool get_power_warning() {
  power_warning_mutex.lock();
  bool val = dfdata.power_warning;
  power_warning_mutex.unlock();
  return val;
}
void set_power_warning(bool val) {
  power_warning_mutex.lock();
  dfdata.power_warning = val;
  power_warning_mutex.unlock();
}

bool get_power_tc() {
  power_tc_mutex.lock();
  bool val = dfdata.power_tc;
  power_tc_mutex.unlock();
  return val;
}
void set_power_tc(bool val) {
  power_tc_mutex.lock();
  dfdata.power_tc = val;
  power_tc_mutex.unlock();
}

uint16_t get_tstamp_ms() {
  tstamp_ms_mutex.lock();
  uint16_t val = dfdata.tstamp_ms;
  tstamp_ms_mutex.unlock();
  return val;
}
void set_tstamp_ms(uint16_t val) {
  tstamp_ms_mutex.lock();
  dfdata.tstamp_ms = val;
  tstamp_ms_mutex.unlock();
}

uint8_t get_tstamp_sc() {
  tstamp_sc_mutex.lock();
  uint8_t val = dfdata.tstamp_sc;
  tstamp_sc_mutex.unlock();
  return val;
}
void set_tstamp_sc(uint8_t val) {
  tstamp_sc_mutex.lock();
  dfdata.tstamp_sc = val;
  tstamp_sc_mutex.unlock();
}

uint8_t get_tstamp_mn() {
  tstamp_mn_mutex.lock();
  uint8_t val = dfdata.tstamp_mn;
  tstamp_mn_mutex.unlock();
  return val;
}
void set_tstamp_mn(uint8_t val) {
  tstamp_mn_mutex.lock();
  dfdata.tstamp_mn = val;
  tstamp_mn_mutex.unlock();
}

uint8_t get_tstamp_hr() {
  tstamp_hr_mutex.lock();
  uint8_t val = dfdata.tstamp_hr;
  tstamp_hr_mutex.unlock();
  return val;
}
void set_tstamp_hr(uint8_t val) {
  tstamp_hr_mutex.lock();
  dfdata.tstamp_hr = val;
  tstamp_hr_mutex.unlock();
}

bool get_mps_enable() {
  mps_enable_mutex.lock();
  bool val = dfdata.mps_enable;
  mps_enable_mutex.unlock();
  return val;
}
void set_mps_enable(bool val) {
  mps_enable_mutex.lock();
  dfdata.mps_enable = val;
  mps_enable_mutex.unlock();
}

bool get_mppt_contactor() {
  mppt_contactor_mutex.lock();
  bool val = dfdata.mppt_contactor;
  mppt_contactor_mutex.unlock();
  return val;
}
void set_mppt_contactor(bool val) {
  mppt_contactor_mutex.lock();
  dfdata.mppt_contactor = val;
  mppt_contactor_mutex.unlock();
}

bool get_motor_controller_contactor() {
  motor_controller_contactor_mutex.lock();
  bool val = dfdata.motor_controller_contactor;
  motor_controller_contactor_mutex.unlock();
  return val;
}
void set_motor_controller_contactor(bool val) {
  motor_controller_contactor_mutex.lock();
  dfdata.motor_controller_contactor = val;
  motor_controller_contactor_mutex.unlock();
}

bool get_low_contactor() {
  low_contactor_mutex.lock();
  bool val = dfdata.low_contactor;
  low_contactor_mutex.unlock();
  return val;
}
void set_low_contactor(bool val) {
  low_contactor_mutex.lock();
  dfdata.low_contactor = val;
  low_contactor_mutex.unlock();
}

bool get_dcdc_valid() {
  dcdc_valid_mutex.lock();
  bool val = dfdata.dcdc_valid;
  dcdc_valid_mutex.unlock();
  return val;
}
void set_dcdc_valid(bool val) {
  dcdc_valid_mutex.lock();
  dfdata.dcdc_valid = val;
  dcdc_valid_mutex.unlock();
}

bool get_supplemental_valid() {
  supplemental_valid_mutex.lock();
  bool val = dfdata.supplemental_valid;
  supplemental_valid_mutex.unlock();
  return val;
}
void set_supplemental_valid(bool val) {
  supplemental_valid_mutex.lock();
  dfdata.supplemental_valid = val;
  supplemental_valid_mutex.unlock();
}

bool get_mppt_mode() {
  mppt_mode_mutex.lock();
  bool val = dfdata.mppt_mode;
  mppt_mode_mutex.unlock();
  return val;
}
void set_mppt_mode(bool val) {
  mppt_mode_mutex.lock();
  dfdata.mppt_mode = val;
  mppt_mode_mutex.unlock();
}

float get_mppt_current_out() {
  mppt_current_out_mutex.lock();
  float val = dfdata.mppt_current_out;
  mppt_current_out_mutex.unlock();
  return val;
}
void set_mppt_current_out(float val) {
  mppt_current_out_mutex.lock();
  dfdata.mppt_current_out = val;
  mppt_current_out_mutex.unlock();
}

float get_string1_temp() {
  string1_temp_mutex.lock();
  float val = dfdata.string1_temp;
  string1_temp_mutex.unlock();
  return val;
}
void set_string1_temp(float val) {
  string1_temp_mutex.lock();
  dfdata.string1_temp = val;
  string1_temp_mutex.unlock();
}

float get_string2_temp() {
  string2_temp_mutex.lock();
  float val = dfdata.string2_temp;
  string2_temp_mutex.unlock();
  return val;
}
void set_string2_temp(float val) {
  string2_temp_mutex.lock();
  dfdata.string2_temp = val;
  string2_temp_mutex.unlock();
}

float get_string3_temp() {
  string3_temp_mutex.lock();
  float val = dfdata.string3_temp;
  string3_temp_mutex.unlock();
  return val;
}
void set_string3_temp(float val) {
  string3_temp_mutex.lock();
  dfdata.string3_temp = val;
  string3_temp_mutex.unlock();
}

float get_pack_temp() {
  pack_temp_mutex.lock();
  float val = dfdata.pack_temp;
  pack_temp_mutex.unlock();
  return val;
}
void set_pack_temp(float val) {
  pack_temp_mutex.lock();
  dfdata.pack_temp = val;
  pack_temp_mutex.unlock();
}

float get_pack_current() {
  pack_current_mutex.lock();
  float val = dfdata.pack_current;
  pack_current_mutex.unlock();
  return val;
}
void set_pack_current(float val) {
  pack_current_mutex.lock();
  dfdata.pack_current = val;
  pack_current_mutex.unlock();
}

float get_pack_voltage() {
  pack_voltage_mutex.lock();
  float val = dfdata.pack_voltage;
  pack_voltage_mutex.unlock();
  return val;
}
void set_pack_voltage(float val) {
  pack_voltage_mutex.lock();
  dfdata.pack_voltage = val;
  pack_voltage_mutex.unlock();
}

float get_cell_group1_voltage() {
  cell_group1_voltage_mutex.lock();
  float val = dfdata.cell_group1_voltage;
  cell_group1_voltage_mutex.unlock();
  return val;
}
void set_cell_group1_voltage(float val) {
  cell_group1_voltage_mutex.lock();
  dfdata.cell_group1_voltage = val;
  cell_group1_voltage_mutex.unlock();
}

float get_cell_group2_voltage() {
  cell_group2_voltage_mutex.lock();
  float val = dfdata.cell_group2_voltage;
  cell_group2_voltage_mutex.unlock();
  return val;
}
void set_cell_group2_voltage(float val) {
  cell_group2_voltage_mutex.lock();
  dfdata.cell_group2_voltage = val;
  cell_group2_voltage_mutex.unlock();
}

float get_cell_group3_voltage() {
  cell_group3_voltage_mutex.lock();
  float val = dfdata.cell_group3_voltage;
  cell_group3_voltage_mutex.unlock();
  return val;
}
void set_cell_group3_voltage(float val) {
  cell_group3_voltage_mutex.lock();
  dfdata.cell_group3_voltage = val;
  cell_group3_voltage_mutex.unlock();
}

float get_cell_group4_voltage() {
  cell_group4_voltage_mutex.lock();
  float val = dfdata.cell_group4_voltage;
  cell_group4_voltage_mutex.unlock();
  return val;
}
void set_cell_group4_voltage(float val) {
  cell_group4_voltage_mutex.lock();
  dfdata.cell_group4_voltage = val;
  cell_group4_voltage_mutex.unlock();
}

float get_cell_group5_voltage() {
  cell_group5_voltage_mutex.lock();
  float val = dfdata.cell_group5_voltage;
  cell_group5_voltage_mutex.unlock();
  return val;
}
void set_cell_group5_voltage(float val) {
  cell_group5_voltage_mutex.lock();
  dfdata.cell_group5_voltage = val;
  cell_group5_voltage_mutex.unlock();
}

float get_cell_group6_voltage() {
  cell_group6_voltage_mutex.lock();
  float val = dfdata.cell_group6_voltage;
  cell_group6_voltage_mutex.unlock();
  return val;
}
void set_cell_group6_voltage(float val) {
  cell_group6_voltage_mutex.lock();
  dfdata.cell_group6_voltage = val;
  cell_group6_voltage_mutex.unlock();
}

float get_cell_group7_voltage() {
  cell_group7_voltage_mutex.lock();
  float val = dfdata.cell_group7_voltage;
  cell_group7_voltage_mutex.unlock();
  return val;
}
void set_cell_group7_voltage(float val) {
  cell_group7_voltage_mutex.lock();
  dfdata.cell_group7_voltage = val;
  cell_group7_voltage_mutex.unlock();
}

float get_cell_group8_voltage() {
  cell_group8_voltage_mutex.lock();
  float val = dfdata.cell_group8_voltage;
  cell_group8_voltage_mutex.unlock();
  return val;
}
void set_cell_group8_voltage(float val) {
  cell_group8_voltage_mutex.lock();
  dfdata.cell_group8_voltage = val;
  cell_group8_voltage_mutex.unlock();
}

float get_cell_group9_voltage() {
  cell_group9_voltage_mutex.lock();
  float val = dfdata.cell_group9_voltage;
  cell_group9_voltage_mutex.unlock();
  return val;
}
void set_cell_group9_voltage(float val) {
  cell_group9_voltage_mutex.lock();
  dfdata.cell_group9_voltage = val;
  cell_group9_voltage_mutex.unlock();
}

float get_cell_group10_voltage() {
  cell_group10_voltage_mutex.lock();
  float val = dfdata.cell_group10_voltage;
  cell_group10_voltage_mutex.unlock();
  return val;
}
void set_cell_group10_voltage(float val) {
  cell_group10_voltage_mutex.lock();
  dfdata.cell_group10_voltage = val;
  cell_group10_voltage_mutex.unlock();
}

float get_cell_group11_voltage() {
  cell_group11_voltage_mutex.lock();
  float val = dfdata.cell_group11_voltage;
  cell_group11_voltage_mutex.unlock();
  return val;
}
void set_cell_group11_voltage(float val) {
  cell_group11_voltage_mutex.lock();
  dfdata.cell_group11_voltage = val;
  cell_group11_voltage_mutex.unlock();
}

float get_cell_group12_voltage() {
  cell_group12_voltage_mutex.lock();
  float val = dfdata.cell_group12_voltage;
  cell_group12_voltage_mutex.unlock();
  return val;
}
void set_cell_group12_voltage(float val) {
  cell_group12_voltage_mutex.lock();
  dfdata.cell_group12_voltage = val;
  cell_group12_voltage_mutex.unlock();
}

float get_cell_group13_voltage() {
  cell_group13_voltage_mutex.lock();
  float val = dfdata.cell_group13_voltage;
  cell_group13_voltage_mutex.unlock();
  return val;
}
void set_cell_group13_voltage(float val) {
  cell_group13_voltage_mutex.lock();
  dfdata.cell_group13_voltage = val;
  cell_group13_voltage_mutex.unlock();
}

float get_cell_group14_voltage() {
  cell_group14_voltage_mutex.lock();
  float val = dfdata.cell_group14_voltage;
  cell_group14_voltage_mutex.unlock();
  return val;
}
void set_cell_group14_voltage(float val) {
  cell_group14_voltage_mutex.lock();
  dfdata.cell_group14_voltage = val;
  cell_group14_voltage_mutex.unlock();
}

float get_cell_group15_voltage() {
  cell_group15_voltage_mutex.lock();
  float val = dfdata.cell_group15_voltage;
  cell_group15_voltage_mutex.unlock();
  return val;
}
void set_cell_group15_voltage(float val) {
  cell_group15_voltage_mutex.lock();
  dfdata.cell_group15_voltage = val;
  cell_group15_voltage_mutex.unlock();
}

float get_cell_group16_voltage() {
  cell_group16_voltage_mutex.lock();
  float val = dfdata.cell_group16_voltage;
  cell_group16_voltage_mutex.unlock();
  return val;
}
void set_cell_group16_voltage(float val) {
  cell_group16_voltage_mutex.lock();
  dfdata.cell_group16_voltage = val;
  cell_group16_voltage_mutex.unlock();
}

float get_cell_group17_voltage() {
  cell_group17_voltage_mutex.lock();
  float val = dfdata.cell_group17_voltage;
  cell_group17_voltage_mutex.unlock();
  return val;
}
void set_cell_group17_voltage(float val) {
  cell_group17_voltage_mutex.lock();
  dfdata.cell_group17_voltage = val;
  cell_group17_voltage_mutex.unlock();
}

float get_cell_group18_voltage() {
  cell_group18_voltage_mutex.lock();
  float val = dfdata.cell_group18_voltage;
  cell_group18_voltage_mutex.unlock();
  return val;
}
void set_cell_group18_voltage(float val) {
  cell_group18_voltage_mutex.lock();
  dfdata.cell_group18_voltage = val;
  cell_group18_voltage_mutex.unlock();
}

float get_cell_group19_voltage() {
  cell_group19_voltage_mutex.lock();
  float val = dfdata.cell_group19_voltage;
  cell_group19_voltage_mutex.unlock();
  return val;
}
void set_cell_group19_voltage(float val) {
  cell_group19_voltage_mutex.lock();
  dfdata.cell_group19_voltage = val;
  cell_group19_voltage_mutex.unlock();
}

float get_cell_group20_voltage() {
  cell_group20_voltage_mutex.lock();
  float val = dfdata.cell_group20_voltage;
  cell_group20_voltage_mutex.unlock();
  return val;
}
void set_cell_group20_voltage(float val) {
  cell_group20_voltage_mutex.lock();
  dfdata.cell_group20_voltage = val;
  cell_group20_voltage_mutex.unlock();
}

float get_cell_group21_voltage() {
  cell_group21_voltage_mutex.lock();
  float val = dfdata.cell_group21_voltage;
  cell_group21_voltage_mutex.unlock();
  return val;
}
void set_cell_group21_voltage(float val) {
  cell_group21_voltage_mutex.lock();
  dfdata.cell_group21_voltage = val;
  cell_group21_voltage_mutex.unlock();
}

float get_cell_group22_voltage() {
  cell_group22_voltage_mutex.lock();
  float val = dfdata.cell_group22_voltage;
  cell_group22_voltage_mutex.unlock();
  return val;
}
void set_cell_group22_voltage(float val) {
  cell_group22_voltage_mutex.lock();
  dfdata.cell_group22_voltage = val;
  cell_group22_voltage_mutex.unlock();
}

float get_cell_group23_voltage() {
  cell_group23_voltage_mutex.lock();
  float val = dfdata.cell_group23_voltage;
  cell_group23_voltage_mutex.unlock();
  return val;
}
void set_cell_group23_voltage(float val) {
  cell_group23_voltage_mutex.lock();
  dfdata.cell_group23_voltage = val;
  cell_group23_voltage_mutex.unlock();
}

float get_cell_group24_voltage() {
  cell_group24_voltage_mutex.lock();
  float val = dfdata.cell_group24_voltage;
  cell_group24_voltage_mutex.unlock();
  return val;
}
void set_cell_group24_voltage(float val) {
  cell_group24_voltage_mutex.lock();
  dfdata.cell_group24_voltage = val;
  cell_group24_voltage_mutex.unlock();
}

float get_cell_group25_voltage() {
  cell_group25_voltage_mutex.lock();
  float val = dfdata.cell_group25_voltage;
  cell_group25_voltage_mutex.unlock();
  return val;
}
void set_cell_group25_voltage(float val) {
  cell_group25_voltage_mutex.lock();
  dfdata.cell_group25_voltage = val;
  cell_group25_voltage_mutex.unlock();
}

float get_cell_group26_voltage() {
  cell_group26_voltage_mutex.lock();
  float val = dfdata.cell_group26_voltage;
  cell_group26_voltage_mutex.unlock();
  return val;
}
void set_cell_group26_voltage(float val) {
  cell_group26_voltage_mutex.lock();
  dfdata.cell_group26_voltage = val;
  cell_group26_voltage_mutex.unlock();
}

float get_cell_group27_voltage() {
  cell_group27_voltage_mutex.lock();
  float val = dfdata.cell_group27_voltage;
  cell_group27_voltage_mutex.unlock();
  return val;
}
void set_cell_group27_voltage(float val) {
  cell_group27_voltage_mutex.lock();
  dfdata.cell_group27_voltage = val;
  cell_group27_voltage_mutex.unlock();
}

float get_cell_group28_voltage() {
  cell_group28_voltage_mutex.lock();
  float val = dfdata.cell_group28_voltage;
  cell_group28_voltage_mutex.unlock();
  return val;
}
void set_cell_group28_voltage(float val) {
  cell_group28_voltage_mutex.lock();
  dfdata.cell_group28_voltage = val;
  cell_group28_voltage_mutex.unlock();
}

float get_cell_group29_voltage() {
  cell_group29_voltage_mutex.lock();
  float val = dfdata.cell_group29_voltage;
  cell_group29_voltage_mutex.unlock();
  return val;
}
void set_cell_group29_voltage(float val) {
  cell_group29_voltage_mutex.lock();
  dfdata.cell_group29_voltage = val;
  cell_group29_voltage_mutex.unlock();
}

float get_cell_group30_voltage() {
  cell_group30_voltage_mutex.lock();
  float val = dfdata.cell_group30_voltage;
  cell_group30_voltage_mutex.unlock();
  return val;
}
void set_cell_group30_voltage(float val) {
  cell_group30_voltage_mutex.lock();
  dfdata.cell_group30_voltage = val;
  cell_group30_voltage_mutex.unlock();
}

float get_soc() {
  soc_mutex.lock();
  float val = dfdata.soc;
  soc_mutex.unlock();
  return val;
}
void set_soc(float val) {
  soc_mutex.lock();
  dfdata.soc = val;
  soc_mutex.unlock();
}

float get_soh() {
  soh_mutex.lock();
  float val = dfdata.soh;
  soh_mutex.unlock();
  return val;
}
void set_soh(float val) {
  soh_mutex.lock();
  dfdata.soh = val;
  soh_mutex.unlock();
}

float get_pack_capacity() {
  pack_capacity_mutex.lock();
  float val = dfdata.pack_capacity;
  pack_capacity_mutex.unlock();
  return val;
}
void set_pack_capacity(float val) {
  pack_capacity_mutex.lock();
  dfdata.pack_capacity = val;
  pack_capacity_mutex.unlock();
}

float get_adaptive_total_capacity() {
  adaptive_total_capacity_mutex.lock();
  float val = dfdata.adaptive_total_capacity;
  adaptive_total_capacity_mutex.unlock();
  return val;
}
void set_adaptive_total_capacity(float val) {
  adaptive_total_capacity_mutex.lock();
  dfdata.adaptive_total_capacity = val;
  adaptive_total_capacity_mutex.unlock();
}

bool get_bps_fault() {
  bps_fault_mutex.lock();
  bool val = dfdata.bps_fault;
  bps_fault_mutex.unlock();
  return val;
}
void set_bps_fault(bool val) {
  bps_fault_mutex.lock();
  dfdata.bps_fault = val;
  bps_fault_mutex.unlock();
}

uint8_t get_fan_speed() {
  fan_speed_mutex.lock();
  uint8_t val = dfdata.fan_speed;
  fan_speed_mutex.unlock();
  return val;
}
void set_fan_speed(uint8_t val) {
  fan_speed_mutex.lock();
  dfdata.fan_speed = val;
  fan_speed_mutex.unlock();
}

bool get_voltage_failsafe() {
  voltage_failsafe_mutex.lock();
  bool val = dfdata.voltage_failsafe;
  voltage_failsafe_mutex.unlock();
  return val;
}
void set_voltage_failsafe(bool val) {
  voltage_failsafe_mutex.lock();
  dfdata.voltage_failsafe = val;
  voltage_failsafe_mutex.unlock();
}

bool get_current_failsafe() {
  current_failsafe_mutex.lock();
  bool val = dfdata.current_failsafe;
  current_failsafe_mutex.unlock();
  return val;
}
void set_current_failsafe(bool val) {
  current_failsafe_mutex.lock();
  dfdata.current_failsafe = val;
  current_failsafe_mutex.unlock();
}

bool get_supply_power_failsafe() {
  supply_power_failsafe_mutex.lock();
  bool val = dfdata.supply_power_failsafe;
  supply_power_failsafe_mutex.unlock();
  return val;
}
void set_supply_power_failsafe(bool val) {
  supply_power_failsafe_mutex.lock();
  dfdata.supply_power_failsafe = val;
  supply_power_failsafe_mutex.unlock();
}

bool get_memory_failsafe() {
  memory_failsafe_mutex.lock();
  bool val = dfdata.memory_failsafe;
  memory_failsafe_mutex.unlock();
  return val;
}
void set_memory_failsafe(bool val) {
  memory_failsafe_mutex.lock();
  dfdata.memory_failsafe = val;
  memory_failsafe_mutex.unlock();
}

bool get_relay_failsafe() {
  relay_failsafe_mutex.lock();
  bool val = dfdata.relay_failsafe;
  relay_failsafe_mutex.unlock();
  return val;
}
void set_relay_failsafe(bool val) {
  relay_failsafe_mutex.lock();
  dfdata.relay_failsafe = val;
  relay_failsafe_mutex.unlock();
}

bool get_bms_canbus_failure() {
  bms_canbus_failure_mutex.lock();
  bool val = dfdata.bms_canbus_failure;
  bms_canbus_failure_mutex.unlock();
  return val;
}
void set_bms_canbus_failure(bool val) {
  bms_canbus_failure_mutex.lock();
  dfdata.bms_canbus_failure = val;
  bms_canbus_failure_mutex.unlock();
}

float get_pack_resistance() {
  pack_resistance_mutex.lock();
  float val = dfdata.pack_resistance;
  pack_resistance_mutex.unlock();
  return val;
}
void set_pack_resistance(float val) {
  pack_resistance_mutex.lock();
  dfdata.pack_resistance = val;
  pack_resistance_mutex.unlock();
}

float get_avg_cell_resistance() {
  avg_cell_resistance_mutex.lock();
  float val = dfdata.avg_cell_resistance;
  avg_cell_resistance_mutex.unlock();
  return val;
}
void set_avg_cell_resistance(float val) {
  avg_cell_resistance_mutex.lock();
  dfdata.avg_cell_resistance = val;
  avg_cell_resistance_mutex.unlock();
}

float get_bms_input_voltage() {
  bms_input_voltage_mutex.lock();
  float val = dfdata.bms_input_voltage;
  bms_input_voltage_mutex.unlock();
  return val;
}
void set_bms_input_voltage(float val) {
  bms_input_voltage_mutex.lock();
  dfdata.bms_input_voltage = val;
  bms_input_voltage_mutex.unlock();
}
 /* Autogenerated Code Ends */

