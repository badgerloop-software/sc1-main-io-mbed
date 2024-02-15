#include "mbed.h"
#include "analog.h"
#include "candecoder.h"
#include "digital.h"

#define SAMPLE_INTERVAL 50ms
#define DEBUG_PRINT 0
#define SEND_MANUAL_STARTUP_SIGNAL 1


#define CAN_RX PD_0
#define CAN_TX PD_1

#if DEBUG_PRINT
void printDebug() {
    // Debug Printout
    printf("\e[1;1H\e[2J");
    printf("Brake 1: %s\n", digital_data.BRK_STATUS ? "On" : "Off");
    printf("Brake 2: %s\n", digital_data.BRK_STATUS2 ? "On" : "Off");
    printf("Hazards: %s\n", digital_data.HZRD_TELEM ? "On" : "Off");
    printf("Headlights: %s\n", digital_data.HEADLIGHT_TELEM ? "On" : "Off");
    printf("Left Blink: %s\n", digital_data.L_BLINK_TELEM ? "On" : "Off");
    printf("Right Blink: %s\n", digital_data.R_BLINK_TELEM ? "On" : "Off");

    printf("Air Temp: %f\n", air_temperature);
    printf("Brake Temp: %f\n", brake_temperature);
    printf("DCDC Temp: %f\n", dcdc_temperature);
    printf("MainIO Temp: %f\n", main_io_temperature);
    printf("MC Temp: %f\n", motor_controller_temperature);
    printf("Motor Temp: %f\n", motor_temperature);
    printf("Road Temp: %f\n", road_temperature);

    printf("12V Rail: %f\n", bus_12v);
    printf("12V Current: %f\n", input_current_12v);
    printf("24V Rail: %f\n", bus_24v);
    printf("24V Current: %f\n", output_current_24v);
    printf("5V Rail: %f\n", bus_5v);
    printf("5V Current: %f\n", output_current_5v);

    
    printf("\n\nDigital CAN data from HV:\n");
    printf("BMS_CHRG_EN: %d\n", get_charge_enable());
    printf("CHRG_EN_Fdbck: %d\n", get_charge_enabled());
    printf("BMS_DSCHRG_EN: %d\n", get_discharge_enable());
    printf("DSCHRG_EN_Fdbck: %d\n", get_discharge_enabled());
    printf("BMS_MPO1: %d\n", get_bms_mpio1());
    printf("Inertia_Fdbck: %d\n", get_crash());
    printf("Driver_Estop_Fdbck: %d\n", get_driver_eStop());
    printf("Ext_Estop_Fdbck: %d\n", get_external_eStop());
    printf("Isolation_Fdbck: %d\n", get_isolation());
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
}
#endif

int main()
{
    BufferedSerial term(USBTX, USBRX, 115200);

    // read brake pin inputs every SAMPLE_INTERVAL seconds
    initDigital(SAMPLE_INTERVAL);
    initAnalog(SAMPLE_INTERVAL);

    // Initialize bus
    CANDecoder canBus(CAN_RX, CAN_TX);

    while (true) {
#if DEBUG_PRINT
        debugPrint();
        printf("\e[1;1H\e[2J");
        printf("Current value: %i    ", get_startup_signal());
        printf("Press 0 to set to low, 1 to set to high");
        if (serial.read(buf, 1) > 0) {
            if (buf[0] == '0') {
                set_startup_signal(0);
            } else if (buf[0] == '1') {
                set_startup_signal(1);
            }
        }
#endif
        // Process inbound messages 
        canBus.send_mainio_data();
        canBus.runQueue(1000ms);
    }
}