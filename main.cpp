#include "mbed.h"
#include "analog.h"
#include "digital.h"

#define SAMPLE_INTERVAL 50ms

int main()
{
    // read brake pin inputs every ___ seconds
    initDigital(SAMPLE_INTERVAL);
    initAnalog(SAMPLE_INTERVAL);

    while (true) {
        wait_us(1000000);
    }
}