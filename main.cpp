
#include "mbed.h"
#include "analog.h"
#include "candecoder.h"
#include "digital.h"
#include "telemetry.h"

#define BIG_NUCLEO 1

#if BIG_NUCLEO

#define CAN_RX PD_0
#define CAN_TX PD_1

#else 

#define CAN_RX PA_11
#define CAN_TX PA_12

#endif

#define MSG_LEN 8

#define SAMPLE_INTERVAL 50ms
#define DEBUG_PRINT 0

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

    //code needed for both
    PinName can_rx = CAN_RX;
    PinName can_tx = CAN_TX;
    CANDecoder mainio_can(can_rx, can_tx, DEFAULT_CAN_FREQ);

    while (true) {
#if DEBUG_PRINT
        printDebug();
#endif

        //send stuff through the CAN pin
        mainio_can.send_mainio_data();
        mainio_can.runQueue(10ms);
    }
}