#include "mbed.h"
#include "digital.h"
#include <cstdio>

#define DIGITAL_INTERVAL 50ms

int main()
{
    // read brake pin inputs every ___ seconds
    initBrake(DIGITAL_INTERVAL);

    while (true) {
        wait_us(1000000);
    }
}