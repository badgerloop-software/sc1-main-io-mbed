#include "analog.h"

// initialize Ticker to setup a recurring interrupt to repeatedly call the function at a specified rate
Ticker readAnalogDelay;

// thermistor initializations
// TODO: put actual values in the initialization. These are currently dummy values. Also delete this comment when done.
// NOTE: the pins are correct.
Thermistor air_therm(NCP21XM472J03RA_Constants, PF_4, 4700, 3.3);
Thermistor brk_therm(NCP21XM472J03RA_Constants, PC_2, 4700, 3.3);
Thermistor dcdc_therm(NCP21XM472J03RA_Constants, PB_1, 4700, 3.3);
Thermistor main_therm(NCP21XM472J03RA_Constants, A0, 4700, 3.3);
Thermistor mc_therm(NCP21XM472J03RA_Constants, A3, 4700, 3.3);
Thermistor motor_therm(NCP21XM472J03RA_Constants, A5, 4700, 3.3);
Thermistor road_therm(NCP21XM472J03RA_Constants, A1, 4700, 3.3);

volatile float air_temperature = 0.0;
volatile float brake_temperature = 0.0;
volatile float dcdc_temperature = 0.0;
volatile float main_io_temperature = 0.0;
volatile float motor_controller_temperature = 0.0;
volatile float motor_temperature = 0.0;
volatile float road_temperature = 0.0;

// voltage rails
AnalogInMutexless LV_12V_TELEM(PF_6);
AnalogInMutexless LV_24V_TELEM(PC_3);
AnalogInMutexless LV_5V_TELEM(PC_2);

volatile float bus_12v = 0.0;
volatile float bus_24v = 0.0;
volatile float bus_5v = 0.0;

void read_temperatures() {
    air_temperature = air_therm.get_temperature();
    brake_temperature = brk_therm.get_temperature();
    dcdc_temperature = dcdc_therm.get_temperature();
    main_io_temperature = main_therm.get_temperature();
    motor_controller_temperature = mc_therm.get_temperature();
    motor_temperature = motor_therm.get_temperature();
    road_temperature = road_therm.get_temperature();
}

// reads bus voltages and scales them
void read_bus_voltages() {
    bus_12v = LV_12V_TELEM.read() * 3.3 *  35.1/5.1;
    bus_24v = LV_24V_TELEM.read() * 3.3 * 56.1/5.1;
    bus_5v = LV_5V_TELEM.read() * 3.3 * 15.1/5.1;
}

// read all analog input
void readAnalog() {
    read_temperatures();
    read_bus_voltages();
}

// Set up polling of analog IO at specified rate
void initAnalog(std::chrono::microseconds readSignalPeriod) {
    readAnalogDelay.attach(readAnalog, readSignalPeriod);
}