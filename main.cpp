/* mbed Microcontroller Library
 * Copyright (c) 2023 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "can.h"

class DUT : Can::device {
    public:
    DUT(Can &c) : device(c) {}
    int callback(CANMessage &msg) {
        printf("%d\n", msg.id);
        return 0;
    }
};

CAN canBus(PD_0, PD_1);

int main()
{
    Can c(&canBus);

    DUT d(c);

    for (;;) {
        wait_us(1000);
    }
    
    printf("Hello, Mbed!\n");
    return 0;
}


/*

#include "mbed.h"

#define CAN_RD PD_0
#define CAN_TD PD_1
#define CAN_RX_INT_FLAG (1UL << 0)

CAN canBus(CAN_RD, CAN_TD);
EventFlags eventFlags;


void isrCanRX() {
    eventFlags.set(CAN_RX_INT_FLAG);
}


void canThread() {
    CANMessage msg;
    while (true) {
        printf("Waiting for message\n");
        if (canBus.tderror() || canBus.rderror()) {
            canBus.reset();
            wait_us(1000);
            canBus.attach(isrCanRX, CAN::RxIrq);
            printf("Cleared an error\n");
        }
        eventFlags.wait_all(CAN_RX_INT_FLAG);
        if (canBus.read(msg)) {
            printf("ID: %x",msg.id);
            switch (msg.id) {
                case 0x123:
                    printf("  Unsigned Int: %ui", *(unsigned int*)msg.data);
                    break;
            }
            printf("\n");
        }
    }
}


int main() {
    canBus.frequency(115200);
    Thread t(osPriorityHigh);
    canBus.attach(isrCanRX, CAN::RxIrq);
    t.start(callback(canThread));
    t.join();
    return 0;
}

*/