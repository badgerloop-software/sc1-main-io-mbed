#include "can.h"
#include "mbed.h"

// main() runs in its own thread in the OS
int main() {
  class DUT : Can::device {
  public:
    DUT(Can &c) : device(c) {}
    virtual int callback(CANMessage &msg) {
      printf("Id: 0x%x", msg.id);
      switch (msg.len) {
      case 1:
        printf("Char? %c\n", *msg.data);
        break;
      case 4:
        printf("unsigned int? 0x%x\n", *(unsigned int *)msg.data);
        break;
      default:
        printf("string? %s\n", msg.data);
        break;
      }
      return 0;
    }
  };
  Can c;
  DUT d(c);
  while (true) {
    char data[8] = "hello!";
    c.send(0x69, data, sizeof(data));
    ThisThread::sleep_for(1s);
  }
}
