#include "analog.h"

// thermistor initializations
Thermistor air_therm(NCP21XM472J03RA_Constants, PF_4, 4700, 3.3);
Thermistor brk_therm(NCP21XM472J03RA_Constants, PC_2, 4700, 3.3);
Thermistor dcdc_therm(NCP21XM472J03RA_Constants, PB_1, 4700, 3.3);
Thermistor mc_therm(NCP21XM472J03RA_Constants, PF_3, 4700, 3.3);
Thermistor motor_therm(NCP21XM472J03RA_Constants, PF_10, 4700, 3.3);
Thermistor road_therm(NCP21XM472J03RA_Constants, PC_0, 4700, 3.3);


// rail voltages
AnalogInMutexless LV_12V_TELEM(PF_6);
AnalogInMutexless LV_24V_TELEM(PF_8);
AnalogInMutexless LV_5V_TELEM(PF_5);


// rail currents
INA281Driver I_OUT_5V(PF_7, 0.005);
INA281Driver I_IN_12V(PA_3, 0.005);
INA281Driver I_OUT_24V(PF_9, 0.005);


void read_temperatures() {
    set_air_temp(air_therm.get_temperature());
    set_brake_temp(brk_therm.get_temperature());
    set_dcdc_temp(dcdc_therm.get_temperature());
    set_motor_controller_temp(mc_therm.get_temperature());
    set_motor_temp(motor_therm.get_temperature());
    set_road_temp(road_therm.get_temperature());
}

// reads bus voltages and scales them
void read_bus_voltages() {
    set_main_12V_bus(LV_12V_TELEM.read() * 3.3 *  35.1/5.1);
    set_main_24V_bus(LV_24V_TELEM.read() * 3.3 * 51/5.1);
    set_main_5V_bus(LV_5V_TELEM.read() * 3.3 * 15.1/5.1);
}

// reads bus currents
void read_bus_currents() {
    set_main_12V_current(I_IN_12V.readCurrent());
    set_main_24V_current(I_OUT_24V.readCurrent());
    set_main_5V_current(I_OUT_5V.readCurrent());
}

// read all analog input
void readAnalog() {
    read_temperatures();
    read_bus_voltages();
    read_bus_currents();
}