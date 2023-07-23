#include "mbed.h"
#include "NetworkInterface.h"
 
#define BUFFSIZE 50
#define SERVERIP         "192.168.1.16"   //Here place your static IP of Mbed Server
 
//#define ROUTER // commented = Static IP uncomented = address assigned by router
#ifndef ROUTER
    #define IP          "192.168.1.15"   //Here place your static IP of Mbed
    #define GATEWAY     "0.0.0.0"
    #define MASK        "255.255.255.0"
#endif
#define PORT            4005
 
DigitalOut led(LED1);
 
NetworkInterface *net = NetworkInterface::get_default_instance();
TCPSocket client;
SocketAddress clientAddress;
 SocketAddress serverAddress(SERVERIP, PORT);
 
int main (void){
    printf("TCP Client starting...\n");
    int net_stat;
#ifndef ROUTER
    net->disconnect();
    net_stat = net->set_network((SocketAddress)IP,(SocketAddress)MASK,(SocketAddress)GATEWAY);
    printf("set IP status: %i\n",net_stat);
#endif
    net_stat = net->connect();
    printf("connect status: %i\n",net_stat);
 
    SocketAddress ip; 
    net->get_ip_address(&ip);
    const char *p_ip = ip.get_ip_address();
    printf("IP address: %s and Port: %d\n", p_ip ? p_ip : "None" , PORT );
    SocketAddress mask;
    net->get_netmask(&mask);
    const char *p_mask = mask.get_ip_address();
    printf("Netmask: %s\n", p_mask ? p_mask : "None");
    SocketAddress gateway;
    net->get_gateway(&gateway);
    const char *p_gateway = gateway.get_ip_address();
    printf("Gateway: %s\n", p_gateway ? p_gateway : "None");
    
    int scount = 0;
    int rcount = 0;
    int dummy = 0;
    char sbuffer[100];
    char rbuffer[100];
    
    while (1) {
        if(client.open(net)== NSAPI_ERROR_OK ){
            if (client.connect(serverAddress) < 0) {
                printf("Failed to connect with server\n\r");
    
            }else{
                printf("Connected to server\n");
                int n = sprintf(sbuffer,"Test String with a dummy number - %d", dummy++);
                scount = client.send(sbuffer, n);
                printf("sent [%s] - %d bytes\n", sbuffer, scount);
                rcount = client.recv(rbuffer, sizeof rbuffer);
                printf("recv [%s] - %d bytes\n", rbuffer, rcount);
                client.close();
            }
        }else{
            printf("No Server\n");
            net->disconnect();
            printf("Program end\n");
            break;
        }
        led = !led;
        thread_sleep_for(5000);
    }
}



/*#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPSocket.h"

// Network interface
EthernetInterface eth;

// TODO #define LOCALIP         "192.168.1.20"
#define LOCALIP         "192.168.1.15"
#define REMOTEIP        "192.168.1.16"
#define MASK       "255.255.255.0"
// TODO #define GATEWAY    "192.168.0.1"
#define GATEWAY    "0.0.0.0"


int main() {
    printf("ethernet test\n");
    SocketAddress gateway = SocketAddress(GATEWAY);
    // TODO sgateway.set_ip_address(GATEWAY);
    // gateway.set_port(4003);
    SocketAddress localip = SocketAddress(LOCALIP);
    // TODO localip.set_ip_address(LOCALIP);
    // TODO localip.set_port(4003);
    SocketAddress mask = SocketAddress(MASK);
    // TODO mask.set_ip_address(MASK);
    //mask.set_port(4003);
    nsapi_error_t status = eth.set_network(localip,mask,gateway);
    if (status != NSAPI_ERROR_OK)
        printf("Uh oh setting network: %d\n", status);
    else
        printf("Set network successfully\n");

    status = eth.connect();
    if (status != NSAPI_ERROR_OK)
        printf("Uh oh connecting ethernet: %d\n", status);
    else
        printf("Connected ethernet successfully\n");
    
    while (eth.get_connection_status() != 1) {
        printf("Connection status: %d\n", eth.get_connection_status());
        wait_us(1000000);
    }

    SocketAddress ip;
    status = eth.get_ip_address(&ip);
    if (status != NSAPI_ERROR_OK)
        printf("Uh oh getting local ip: %d\n", status);
    else
        printf("Got local IP successfully\n");
    printf("Local IP address %s\n", ip.get_ip_address() ? ip.get_ip_address() : "None");

    // Open a TCP socket
    TCPSocket socket;
    // TODO socket.set_blocking(false);
    status = socket.open(&eth);
    if (status != NSAPI_ERROR_OK)
        printf("Uh oh opening socket: %d\n", status);
    else
        printf("Opened socket successfully\n");
    

// TODO New stuff between here and hte next todo
    ip.set_port(4003);
    socket.bind(ip);

    status = socket.listen(1);
    if (status != NSAPI_ERROR_OK)
        printf("Uh oh listening: %d\n", status);
    else
        printf("Listening successfully\n");
    TCPSocket *endSocket = socket.accept();

    if(endSocket == NULL)
        printf("Uh oh accepting connection\n");
    else
        printf("Successfully accepted connection\n");

    const char *d = "hi";
    status = endSocket->send(d, 2);
    if (status != NSAPI_ERROR_OK)
        printf("Uh oh sending packet: %d\n", status);
    else
        printf("Sent packet successfully\n");
    
    endSocket->close();
    eth.disconnect();
    return 0;
// TODO Picked up down here



    SocketAddress ad;
    ad.set_ip_address(REMOTEIP);
    ad.set_port(4003);
    status = socket.connect(ad);
    if (status != NSAPI_ERROR_OK) {
        printf("Uh oh connecting socket: %d\n", status);
        socket.close();
        status = socket.open(&eth);
        if (status != NSAPI_ERROR_OK)
            printf("Uh oh opening socket: %d\n", status);
        else
            printf("Opened socket again successfully\n");
        
        //socket.bind(localip);
        socket.bind(4003);
        status = socket.connect(ad);
        if (status != NSAPI_ERROR_OK)
            printf("Uh oh connecting socket again: %d\n", status);

    }

    socket.close();
    eth.disconnect();
    
    // for(int i = 0; i < 30; i++) {
    //     // char data[10] = "message";
    //     // printf("send: %d\n", socket.send(&data, 10));
    //     char rbuffer[64];
    //     int rcount = socket.recv(rbuffer, sizeof rbuffer);
    //     // printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
    //     wait_us(1000000);
    // }
}*/

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
