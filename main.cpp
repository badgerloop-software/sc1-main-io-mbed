#include "mbed.h"
#include "analog.h"
#include "candecoder.h"
#include "dataFormat.h"
#include "digital.h"

#define SAMPLE_INTERVAL 50ms
#define DEBUG_PRINT 1

#define CAN_RX PD_0
#define CAN_TX PD_1

#if DEBUG_PRINT
void printDebug(char* boardSelect) {
    printf("\e[1;1H\e[2J");
    switch (boardSelect[0]) {
        case 'm':
            printf("Restart Enable: %s\n", get_restart_enable() ? "On" : "Off");
            printf("Brake 1: %s\n", get_park_brake() ? "On" : "Off");
            printf("Hazards: %s\n", get_hazards() ? "On" : "Off");
            printf("Headlights: %s\n", get_hazards() ? "On" : "Off");
            printf("Left Blink: %s\n", get_l_turn_led_en() ? "On" : "Off");
            printf("Right Blink: %s\n", get_r_turn_led_en() ? "On" : "Off");

            printf("Air Temp: %f\n", get_air_temp());
            printf("Brake Temp: %f\n", get_brake_temp());
            printf("DCDC Temp: %f\n", get_dcdc_temp());
            printf("MainIO Temp: %f\n", get_mainIO_temp());
            printf("MC Temp: %f\n", get_motor_controller_temp());
            printf("Motor Temp: %f\n", get_motor_temp());
            printf("Road Temp: %f\n", get_road_temp());

            printf("12V Rail: %f\n", get_main_12V_bus());
            printf("12V Current: %f\n", get_main_12V_current());
            printf("24V Rail: %f\n", get_main_24V_bus());
            printf("24V Current: %f\n", get_main_24V_current());
            printf("5V Rail: %f\n", get_main_5V_bus());
            printf("5V Current: %f\n", get_main_5V_current());
            break;
        
        case 'h':
            printf("BMS_CHRG_EN: %d\n", get_charge_enable());
            printf("CHRG_EN_Fdbck: %d\n", get_charge_enabled());
            printf("BMS_DSCHRG_EN: %d\n", get_discharge_enable());
            printf("DSCHRG_EN_Fdbck: %d\n", get_discharge_enabled());
            printf("BMS_MPO1: %d\n", get_bms_mpio1());
            printf("Inertia_Fdbck: %d\n", get_crash());
            printf("Driver_Estop_Fdbck: %d\n", get_driver_eStop());
            printf("Ext_Estop_Fdbck: %d\n", get_external_eStop());
            printf("Isolation_Fdbck: %d\n", get_isolation());
            printf("MCU_HV_EN: %d\n", get_mcu_hv_en());
            printf("LO_CONT_TELEM: %d\n", get_low_contactor());
            printf("MC_CONT_TELEM: %d\n", get_motor_controller_contactor());
            printf("MPPT_CONT_TELEM: %d\n", get_mppt_contactor());
            printf("MCU_Stat_Fdbck: %d\n", get_mcu_stat_fdbk());
            printf("USE_SUPP: %d\n", get_use_supp());
            printf("USE_DCDC: %d\n", get_use_dcdc());
            printf("\nAnalog CAN data from HV:\n");
            printf("DCDC_IS: %f\n", get_dcdc_current() * 22700 / 1200);
            printf("SUPP_IS: %f\n", get_supplemental_current() * 22700 / 1200);
            printf("SENSE_VSUPP: %f\n", get_supplemental_voltage());
            break;

        case 'c':
            printf("Motor Power: %s\n", get_main_telem() ? "On" : "Off");
            printf("MCC State: %i\n", get_mcc_state());
            printf("Direction: %s\n", get_fr_telem() ? "Reverse" : "Forward");
            printf("Eco: %s\n", get_eco() ? "On" : "Off");
            printf("Foot Brake: %s\n", get_foot_brake() ? "On" : "Off");
            printf("Cruise Speed Mode: %s\n", get_crz_spd_mode() ? "On" : "Off");
            printf("Cruise Speed Setpoint: %f\n", get_crz_spd_setpt());
            printf("Accelerator Pedal: %f\n", get_accelerator_pedal());
            printf("Regen Brake: %f\n", get_regen_brake());
            printf("Speed: %f\n", get_speed());
            break;

        case 'p':
            printf("Array 1\n");
            printf("Voltage: %f\n", get_string1_V_in());
            printf("Current: %f\n", get_string1_I_in());
            printf("Temperature: %f\n", get_string1_temp());
            printf("Array 2\n");
            printf("Voltage: %f\n", get_string2_V_in());
            printf("Current: %f\n", get_string2_I_in());
            printf("Temperature: %f\n", get_string2_temp());
            printf("Array 3\n");
            printf("Voltage: %f\n", get_string3_V_in());
            printf("Current: %f\n", get_string3_I_in());
            printf("Temperature: %f\n", get_string3_temp());
            break;

        case 'b':
            printf("Pack Current: %f\n", get_pack_current());
            printf("Pack Voltage: %f\n", get_pack_voltage());
            printf("SOC: %f\n", get_soc());
            printf("SOH: %f\n", get_soh());
            printf("Pack Resistance: %f\n", get_pack_resistance());
            printf("Pack Amphours: %f\n", get_pack_amphours());
            printf("Populated Cells: %i\n", get_populated_cells());
            printf("Input Voltage: %f\n", get_bms_input_voltage());
            printf("Pack Temp: %f\n", get_pack_temp());
            printf("Internal Temp: %f\n", get_pack_internal_temp());
            printf("Pack Current: %f\n", get_pack_current());
            printf("Fan Speed: %i\n", get_fan_speed());
            break;

        default:
            break;
    }
}
#endif

int main()
{
#if DEBUG_PRINT
    BufferedSerial serial(USBTX, USBRX, 115200);
    serial.set_blocking(false);
    char buf[1];
#endif

    // read brake pin inputs every SAMPLE_INTERVAL seconds
    //initDigital(SAMPLE_INTERVAL);
    //initAnalog(SAMPLE_INTERVAL);

    // Initialize bus
    CANDecoder canBus(CAN_RX, CAN_TX);

    while (true) {
#if DEBUG_PRINT
        printDebug(buf);
        printf("Commands:\n0/1 to set mcu_hv_en\nm: MainIO Printout\nh: HV Printout\nc: MCC Printout\np: MPPT Printout\nb: BMS Printout\n");
        if (serial.read(buf, 1) > 0) {
            if (buf[0] == '0') {
                set_restart_enable(0);
            } else if (buf[0] == '1') {
                set_restart_enable(1);
            }
        }
#endif
        // Process inbound messages 
        canBus.send_mainio_data();
        canBus.runQueue(1000ms);
    }
}