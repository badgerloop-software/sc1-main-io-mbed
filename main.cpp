#include "mbed.h"
#include "EthernetInterface.h"

// Network interface
EthernetInterface eth;

#define LOCALIP         "192.168.1.20"
#define REMOTEIP         "192.168.1.16"
#define MASK       "255.255.255.0"
#define GATEWAY    "192.168.1.255"


int main() {
    printf("ethernet test\n");
    SocketAddress gateway;
    // gateway.set_ip_address(GATEWAY);
    // gateway.set_port(4003);
    SocketAddress localip;
    localip.set_ip_address(LOCALIP);
    localip.set_port(4003);
    SocketAddress mask;
    mask.set_ip_address(MASK);
    //mask.set_port(4003);
    nsapi_error_t status = eth.set_network(localip,mask,gateway);
    switch(status) {
        case NSAPI_ERROR_OK:
            printf("NSAPI_ERROR_OK (it's working)\n");
            break;
        case NSAPI_ERROR_BUSY:
            printf("NSAPI_ERROR_BUSY\n");
            break;
        case NSAPI_ERROR_IS_CONNECTED:
            printf("NSAPI_ERROR_IS_CONNECTED\n");
            break;
        case NSAPI_ERROR_NO_CONNECTION:
            printf("NSAPI_ERROR_NO_CONNECTION\n");
            break;
        case NSAPI_ERROR_DHCP_FAILURE:
            printf("NSAPI_ERROR_DHCP_FAILURE\n");
            break;
        case NSAPI_ERROR_UNSUPPORTED:
            printf("NSAPI_ERROR_UNSUPPORTED\n");
            break;
        default: 
            printf("error\n");
    }
    
    status = eth.connect();
    switch(status) {
        case NSAPI_ERROR_OK:
            printf("NSAPI_ERROR_OK (it's working, eth connect)\n");
            break;
        case NSAPI_ERROR_BUSY:
            printf("NSAPI_ERROR_BUSY\n");
            break;
        case NSAPI_ERROR_IS_CONNECTED:
            printf("NSAPI_ERROR_IS_CONNECTED\n");
            break;
        case NSAPI_ERROR_NO_CONNECTION:
            printf("NSAPI_ERROR_NO_CONNECTION\n");
            break;
        case NSAPI_ERROR_DHCP_FAILURE:
            printf("NSAPI_ERROR_DHCP_FAILURE\n");
            break;
        default: 
            printf("error\n");
    }
    while (1) {
        printf("%d\n", eth.get_connection_status());
        wait_us(1000000);
    }
    // // Open a TCP socket
    // TCPSocket socket;
    // socket.set_blocking(false);
    // status = socket.open(&eth);
    // switch(status) {
    //     case NSAPI_ERROR_OK:
    //         printf("NSAPI_ERROR_OK (it's working socket)\n");
    //         break;
    //     case NSAPI_ERROR_BUSY:
    //         printf("NSAPI_ERROR_BUSY\n");
    //         break;
    //     case NSAPI_ERROR_IS_CONNECTED:
    //         printf("NSAPI_ERROR_IS_CONNECTED\n");
    //         break;
    //     case NSAPI_ERROR_NO_CONNECTION:
    //         printf("NSAPI_ERROR_NO_CONNECTION\n");
    //         break;
    //     case NSAPI_ERROR_DHCP_FAILURE:
    //         printf("NSAPI_ERROR_DHCP_FAILURE\n");
    //         break;
    //     case NSAPI_ERROR_UNSUPPORTED:
    //         printf("NSAPI_ERROR_UNSUPPORTED\n");
    //         break;
    //     case NSAPI_ERROR_PARAMETER: 
    //         printf("NSAPI_ERROR_PARAMETER\n");
    //         break;
    //     default: 
    //         printf("error\n");
    // }
    // SocketAddress ad;
    // ad.set_ip_address(REMOTEIP);
    // ad.set_port(4003);
    // status = socket.connect(ad);
    // switch(status) {
    //     case NSAPI_ERROR_OK:
    //         printf("NSAPI_ERROR_OK (it's working SocketAddress)\n");
    //         break;
    //     case NSAPI_ERROR_BUSY:
    //         printf("NSAPI_ERROR_BUSY\n");
    //         break;
    //     case NSAPI_ERROR_IS_CONNECTED:
    //         printf("NSAPI_ERROR_IS_CONNECTED\n");
    //         break;
    //     case NSAPI_ERROR_NO_CONNECTION:
    //         printf("NSAPI_ERROR_NO_CONNECTION\n");
    //         break;
    //     case NSAPI_ERROR_DHCP_FAILURE:
    //         printf("NSAPI_ERROR_DHCP_FAILURE\n");
    //         break;
    //     case NSAPI_ERROR_UNSUPPORTED:
    //         printf("NSAPI_ERROR_UNSUPPORTED\n");
    //         break;
    //     case NSAPI_ERROR_PARAMETER: 
    //         printf("NSAPI_ERROR_PARAMETER\n");
    //         break;
    //     default: 
    //         printf("error\n");
    // }
    // for(int i = 0; i < 30; i++) {
    //     // char data[10] = "message";
    //     // printf("send: %d\n", socket.send(&data, 10));
    //     char rbuffer[64];
    //     int rcount = socket.recv(rbuffer, sizeof rbuffer);
    //     // printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
    //     wait_us(1000000);
    // }
}

// // Socket demo
// int main()
// {
//     // Bring up the ethernet interface
//     printf("Ethernet socket example\n");    
//     net.set_network(IP,MASK,GATEWAY);

//     nsapi_error_t e = net.connect();
//     switch(e) {
//         case NSAPI_ERROR_OK:
//             printf("NSAPI_ERROR_OK\n");
//             break;
//         case NSAPI_ERROR_BUSY:
//             printf("NSAPI_ERROR_BUSY\n");
//             break;
//         case NSAPI_ERROR_IS_CONNECTED:
//             printf("NSAPI_ERROR_IS_CONNECTED\n");
//             break;
//         default: 
//             printf("error\n");
//     }

//     // Show the network address
//     SocketAddress a;
//     net.get_ip_address(&a);
//     printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

//     // Open a socket on the network interface, and create a TCP connection to mbed.org
//     TCPSocket socket;
//     socket.open(&net);

//     net.gethostbyname("ifconfig.io", &a);
//     a.set_port(80);
//     socket.connect(a);
//     // Send a simple http request
//     char sbuffer[] = "GET / HTTP/1.1\r\nHost: ifconfig.io\r\n\r\n";
//     int scount = socket.send(sbuffer, sizeof sbuffer);
//     printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);

//     // Recieve a simple http response and print out the response line
//     char rbuffer[64];
//     int rcount = socket.recv(rbuffer, sizeof rbuffer);
//     printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);

//     // Close the socket to return its memory and bring down the network interface
//     socket.close();

//     // Bring down the ethernet interface
//     net.disconnect();
//     printf("Done\n");
// }


// #include "bms.h"
// #include "i2cdevice.h"
// #include "ina219.h"
// #include "mbed.h"
// #include "rtos.h"
// #include "tca6416.h"
// #include "uartApp.h"

// CAN canBus(PD_0, PD_1, 500000);
// I2C i2cBus(PF_0, PF_1); // (sda, scl)
// DigitalOut pin(PA_7, 1); // this is for the small nucleo so that CAN works.
// DigitalOut GPIO1_RST(PG_0, 0);
// DigitalOut GPIO2_RST(PG_1, 0);
// Can c(&canBus);

// // bms gpio signals
// bool mpi_1;
// bool mpi_2;
// bool mpo_2;

// int main(void){
//     printf("hey\n");
//     // TODO Check directions and set pins to read to 1 and pins to write to 0
//     const uint8_t tca_dirs[16] = {0, 1, 1, 1, 1, 1, 1, 1, 
//                                     1, 1, 1, 0, 1, 1, 1, 1};
//     TCA6416 tca(&i2cBus, 0x20);
//     TCA6416 tca_bms(&i2cBus, 0x21);
//     tca.i2cdetect();
//     tca.begin(tca_dirs);

//     tca.set_state(1, 3, 0);
//     printf("MCU_Latch: %d\n", tca.get_state(1, 3));
//     wait_us(1000000);
//     tca.set_state(1, 3, 1);
//     printf("MCU_Latch: %d\n", tca.get_state(1, 3));
//     wait_us(1000000);
//     tca.set_state(1, 3, 0);
//     printf("MCU_Latch: %d\n", tca.get_state(1, 3));


//     // the following are the 3 INAs on MainIO. Only leave one uncommented when running
//     //INA219* ina = new INA219(&i2cBus, 0x40, 0.005, 2.0);
//     //INA219* ina = new INA219(&i2cBus, 0x44, 0.005, 2.0); 
//     //INA219* ina = new INA219(&i2cBus, 0x41, 0.005, 1.0);
//     //ina.begin();

//     BMS bms(c);
    
//     if(!runUart(&tca)) {
//         printf("the UART application is running\n");
//     } else {
//         printf("NOT RUNNING\n");
//         exit(1);
//     }
//     int toggle = 0;
//     for (;;) {
//         printf("\e[1;1H\e[2J");
//         printf("MCU_Stat_fdbk: %d\n", !tca.get_state(0, 1));
//         printf("mcu_hv_en (main): %d\n", get_mcu_hv_en());
//         printf("IMD_fdbk: %d\n", !tca.get_state(0, 2));
//         printf("MPO 2: %d\n", mpo_2);
//         printf("Lim_fdbk: %d\n", !tca.get_state(0, 3));
//         printf("Inertia_fdbk: %d\n", !tca.get_state(1, 7));
//         printf("Ext_Estop_fdbk: %d\n", !tca.get_state(1, 5));
//         printf("Driver_Estop_fdbk: %d\n", !tca.get_state(1, 4));
//         printf("Charge Enable: %d\n", tca_bms.get_state(1, 5));
//         printf("Discharge Enable: %d\n", tca_bms.get_state(1, 6));
//         if (toggle == 0) {
//             toggle = 1;
//         } else {
//             toggle = 0;
//         }
//         //tca.set_state(0, 0, toggle);
//         printf("Charge: %f\n", bms.getPackStateOfCharge());
//         printf("Voltage: %f\n", bms.getPackVoltage());
//         printf("Current (Main): %f\n", bms.getPackCurrent());
//         printf("Avg Temp: %f\n", bms.getAvgTemperature());
//         printf("Internal Temp:%f\n", bms.getInternalTemperature());
//         printf("Fan Speed: %d\n", bms.getFanSpeed());
//         //wait_us(1000000);
//         // modify the byte array and put printouts here

//         // this has to be set to 1 for the UART app to not get stuck at the fault screen. 
//         // it will probably change in the future once software updates the
//         // checkRestartEnable() method in DataUnpacker.cpp 
//         // TODO set_door(toggle);

//         // bms updateGPIO method
//         mpi_1 = tca_bms.get_state(1, 2); // BMS_MPI1
//         mpi_2 = tca_bms.get_state(1, 3); // BMS_MPI2
//         mpo_2 = tca_bms.get_state(1, 4); // BMS_MPO2
//         //set_imd_status(!tca.get_state(0, 2));
//         set_imd_status(mpo_2);
//         set_charge_enable(tca_bms.get_state(1, 5)); // BMS_CHRG_EN
//         set_discharge_enable(tca_bms.get_state(1, 6)); // BMS_DSCHRG_EN
//         // update external_eStop
//         set_external_eStop(!tca.get_state(1, 5)); // Ext_Estop_Fdbk
//         set_driver_eStop(!tca.get_state(1, 4));
//         set_crash(!tca.get_state(1, 7));
//         set_door(!tca.get_state(0, 3));
//         set_mcu_stat_fdbk(!tca.get_state(0, 1));

//         wait_us(1000000);
//     }
    
//     printf("Hello, Mbed!\n");
//     return 0;
// }
