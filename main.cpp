#include "mbed.h"
#include "analog.h"
#include "candecoder.h"
#include "digital.h"
#include "telemetry.h"

#define SAMPLE_INTERVAL 50ms
#define DEBUG_PRINT 0

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
#endif
        // Process inbound messages 
        canBus.send_mainio_data();
        canBus.runQueue(1000ms);
    }
}