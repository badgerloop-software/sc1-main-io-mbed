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

int main()
{
    Can c;
    DUT d(c);

    for (;;);
    
    printf("Hello, Mbed!\n");
    return 0;
}